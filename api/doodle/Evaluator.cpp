////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Evaluator.hpp"
#include "Project.hpp"
#include "DObject.hpp"
#include <doodle/typedef/revision.hpp>
#include <yq/errors.hpp>
#include <yq/core/Flags.hpp>
#include <yq/core/UniqueID.hpp>
#include <yq/text/format.hpp>
#include <yq/text/match.hpp>
#include <yq/userexpr/Context.hpp>
#include <yq/userexpr/UserExpr.hpp>
#include <doodle/logging.hpp>
#include "Project.hxx"

namespace yq::doodle {

    /*
        TODO ... make this use parent lineage for variable resolution too...
    */

    using UserExprCPtr = std::shared_ptr<const UserExpr>;

    bool Evaluator::StrIDLess::operator()(const StrIDKey& a, const StrIDKey& b)
    {
        switch(compare_igCase(a.first, b.first)){
        case Compare::LESSER:
            return true;
        case Compare::GREATER:
            return false;
        default:
            return a.second < b.second;
        }
    }

    struct Evaluator::Dep {
        std::u32string      var;                //!< Name of the variable (into our variable map)
        ID                  dib;                //!< DObject ID
        std::string         attr;               //!< Variable name
        bool                isGlobal = false;   //!< TRUE if this is referencing a global/override
        Ergo*               ergo    = nullptr;  //!< Ergo of dependency
        revision_t          revision;           //!< Revision of update
    };

    struct Evaluator::Ergo : public UniqueID, public expr::Context {
    
        enum class F {
            Parsed,
            Fetched,
            Missing,
            ParseFail,
            DepScanned
        };
    
        const std::string   name;           //!< Attribute name
        const ID            dib;            //!< Doodle Object ID (invalid if project)
        Any                 value;          //!< Last computed value
        std::string         definition;     //!< The current/old definition
        revision_t          revision;       //!< Revision of object/project
        UserExprCPtr        userexpr;       //!< User expression (if any)
        Flags<F>            flags;
        std::vector<Dep>    dependencies;
        
        Ergo(std::string_view k, ID i={}) : name(k), dib(i) {}
    };

    Evaluator::Evaluator(const Project& prj, const u32string_any_map_t& overrides) : m_project(prj), m_overrides(overrides)
    {
    }
    
    Evaluator::Evaluator(const Project& prj, const string_any_map_t& overrides) : m_project(prj)
    { 
        for(auto& i : overrides){
            m_overrides[to_u32string(i.first)] = i.second;
        }
    }

    Evaluator::~Evaluator()
    {
        for(auto& i : m_ergos)
            delete i.second;
        m_ergos.clear();
        m_prjAttrs.clear();
        m_objAttrs.clear();
    }

    Evaluator::Ergo*   Evaluator::ergo(ID id, const std::string& k)
    {
        if(id){
            if(!m_project.is_attribute(id, k))
                return nullptr;
            auto itr = m_objAttrs.find({k, id});
            if(itr != m_objAttrs.end())
                return itr->second;
            Ergo* e =  new Ergo(k, id);
            m_ergos[e->id()]    = e;
            m_objAttrs[{k,id}]  = e;
            return e;
        } else {
            if(!m_project.is_attribute(k))
                return nullptr;
            auto itr = m_prjAttrs.find(k);
            if(itr != m_prjAttrs.end())
                return itr->second;
            Ergo* e = new Ergo(k);
            m_ergos[e->id()]    = e;
            m_prjAttrs[k]   = e;
            return e;
        }
    }


    any_x   Evaluator::evaluate(ID i, const std::string& k)
    {
        Ergo* e = ergo(i, k);
        if(!e)
            return errors::bad_argument();
        update(*e);
        return e->value;
    }
    
    any_x   Evaluator::evaluate(const std::string&k)
    {
        Ergo* e = ergo({}, k);
        if(!e)
            return errors::bad_argument();
        update(*e);
        return e->value;
    }

    bool    Evaluator::needs_parsing(Ergo& e) const
    {
        if(!e.flags(Ergo::F::Parsed))
            return true;
        if(!e.userexpr) // always true first time
            return true;

        if(e.dib){
            const DObject* obj = m_project.object(e.dib);
            if(!obj){
                e.flags |= Ergo::F::Missing;
                return false;
            } 

            e.flags -= Ergo::F::Missing;
            if(e.revision == obj->revision(LOCAL))
                return false;
                
            if(obj->is_attribute(e.name)){
                std::string_view    attr    = obj->attribute(e.name);
                if(attr != e.definition){
                    e.definition    = attr;
                    e.flags        |= Ergo::F::Fetched;
                    e.revision      = obj->revision(LOCAL);
                    return true;
                }
            }

            return false;
        } else {
            if(e.revision == m_project.revision())
                return false;

            std::string_view    attr    = m_project.attribute(e.name);
            if(attr != e.definition){
                e.definition    = attr;
                e.flags |= Ergo::F::Fetched;
                e.revision  = m_project.revision();
                return true;
            }

            return false;
        }
    }
    
    //bool    Evaluator::fetch(Ergo&e) const
    //{
        //if(e.flags(Ergo::F::Fetched))
            //return true;
        
        //if(e.dib){
            //const DObject* obj = m_project.object(e.dib);
            //if(!obj){
                //e.flags |= Ergo::F::Missing;
                //return false;
            //}
            
            //e.definition    = obj->attribute(e.name);
            //e.revision      = obj->revision(LOCAL);
        //} else {
            //e.definition    = m_project.attribute(e.name);
            //e.revision      = m_project.revision();
        //}
        
        //e.flags      |= Ergo::F::Fetched;
        //return true;
    //}

    bool    Evaluator::parse(Ergo&e) const
    {
        e.flags -= Ergo::F::Parsed;
        e.flags -= Ergo::F::ParseFail;
        
        if(!e.flags(Ergo::F::Fetched))
            return false;
        
        UserExprCPtr    ue  = std::make_shared<UserExpr>(e.definition);
        if(!ue->is_good()){
            e.flags |= Ergo::F::ParseFail;
            doodleFirstWarning(e.definition) << "Unable to parse the user expression '" << e.definition 
                << "' with complaint '" << ue->build_error().message() << "'";
            return false;
        }
        
        e.userexpr    = ue;
        e.flags |= Ergo::F::Parsed;
        return true;
    }

    bool    Evaluator::redep(Ergo& e) 
    {
        // redo dependencies
        e.flags -= Ergo::F::DepScanned;
        
        if(!e.userexpr)
            return false;
        
        std::vector<Dep>    depends;
        u32string_view_set_t    vars;
        e.userexpr -> get_variables_in_use(vars);
        
        if(vars.empty()){
            e.flags |= Ergo::F::DepScanned;
            e.dependencies.clear();
            e.variables.clear();
            return true;
        }
        
        for(auto& v32 : vars){
            std::string     var = to_string(v32);
            std::string     attr;
            const DObject*  obj = nullptr;
            
            auto n = var.find('.');
            if(n != std::string::npos){
                std::string uid     = var.substr(0,n);
                attr    = var.substr(n+1);
                obj     =  m_project.foreach(
                    UID, uid, [&](const DObject* obj2) -> const DObject* {
                    if(obj2->is_attribute(attr))
                        return obj2;
                    return nullptr;
                });
            } else if(e.dib){
                attr    = var;
                obj     = m_project.object(e.dib);
                if(!obj){
                    doodleFirstWarning(e.dib) << "Not an object, skipping variable dependencies";
                    continue;
                }
            } else
                attr    = var;
            
            if(obj && obj->is_attribute(attr)){
                Dep  d;
                d.var   = v32;
                d.dib   = obj -> id();
                d.attr  = attr;
                depends.push_back(d);
                continue;
            }
            
            if(m_project.is_attribute(var) || m_overrides.contains(std::u32string(v32))){
                Dep d;
                d.var   = v32;
                d.attr  = var;
                depends.push_back(d);
                continue;
            }
            
            doodleFirstWarning(e.dib, var) << "Unable to resolve variable " << var 
                << " on object " << e.dib;
        }
        
        e.dependencies  = depends;
        return true;
    }

    bool    Evaluator::update(Ergo&e)
    {
        std::set<uint64_t> seen;
        return update(e,seen);
    }
    
    bool    Evaluator::update(Ergo&e, std::set<uint64_t>&seen)
    {
        if(seen.insert(e.id()).second)  // break on cycle
            return false;
            
        bool    exec    = e.value.invalid() || !e.userexpr; // two guaranteed conditions for reevaluating
            
        if(needs_parsing(e)){
            //if(!fetch(e))
                //return true;
            if(!parse(e))
                return true;
            if(!redep(e))
                return true;
            exec        = true;
        }
        
        for(auto& d : e.dependencies){
            if(d.isGlobal){
                auto itr = m_overrides.find(d.var);
                if(itr != m_overrides.end()){
                    auto jtr = e.variables.find(d.var);
                    if((jtr == e.variables.end()) || (jtr->second != itr->second)){
                        e.variables[d.var]  = itr->second;
                        exec    = true;
                    }
                }
                continue;
            }
            
            if(!d.ergo){
                d.ergo  = ergo(d.dib, d.attr);
                if(!d.ergo)
                    continue;
                exec    = true;
            }
            
            if(update(*d.ergo, seen)){
                e.variables[d.var]  = d.ergo->value;
                exec    = true;
            } else {
                auto jtr = e.variables.find(d.var);
                if((jtr == e.variables.end()) || (jtr->second != d.ergo->value)){
                    e.variables[d.var]  = d.ergo->value;
                    exec    = true;
                }
            }
        }
        
        if(!exec)       // this is a fine exit, means nothing changed on us
            return false;
            
        any_x   val = e.userexpr -> evaluate(e);
        if(!val){       
            // evaluation failed, abort (old value, if any, is used)
            std::error_code ec  = val.error();
            doodleFirstWarning(e.dib, e.name) << "Failed to evaluate on object " << e.dib.id 
                << "." << e.name << " due to " << ec.message();
            return false;
        }
        
        if(*val != e.value){
            e.value = *val;
            return true;
        } else {
            return false;
        }
    }

    void    Evaluator::set_override(std::string_view k, Any&&val)
    {
        set_override(to_u32string(k), std::move(val));
    }
    
    void    Evaluator::set_override(std::u32string_view k, Any&& val)
    {
        m_overrides[std::u32string(k)] = std::move(val);
    }

}
