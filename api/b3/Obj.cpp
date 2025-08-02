////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Obj.hpp"
#include "Obj.hxx"

#include <b3/logging.hpp>
#include <b3/ObjMetaWriter.hpp>
#include <b3/annotate/Style.hpp>

#include <yq/container/Stack.hpp>
#include <yq/shape/AxBox2.hpp>
#include <yq/shape/AxBox3.hpp>
#include <yq/shape/AxCorners2.hpp>
#include <yq/shape/AxCorners3.hpp>
#include <yq/text/parse.hpp>

#include <yq/shape/AxBox2.hxx>
#include <yq/shape/AxBox3.hxx>

YQ_OBJECT_IMPLEMENT(yq::b3::Obj)

namespace yq::b3 {
    ObjMeta::ObjMeta(std::string_view zName, ObjectMeta& base, const std::source_location& sl) :
        ObjectMeta(zName, base, sl)
    {
    }

    ObjMeta::DelegateFN  ObjMeta::delegate(Meta::id_t id) const
    {
        auto k  = m_delegates.find(id);
        if(k == m_delegates.end())
            return nullptr;
        return k->second;
    }

    ObjMeta::DelegateCFN  ObjMeta::cDelegate(Meta::id_t id) const
    {
        auto k  = m_cDelegates.find(id);
        if(k == m_cDelegates.end())
            return nullptr;
        return k->second;
    }

    ////////////////////////////////////////////////////////////////////////////

    Obj::Obj(const Param& p) : m_frame(p.frame), m_name(p.name)
    {
        m_args  = p.args;
        if(p.attrs.boolean("$ter"))
            m_flags |= F::Terrain;
        if(p.attrs.boolean("$hide"))
            m_flags |= F::Hide;
        if(m_name.empty())
            m_name  = p.attrs.string("id");
        if(m_frame){
            m_doc   = m_frame -> document();
            if(!m_name.empty())
                m_frame -> m_byName[m_name]   = this;
            m_frame -> m_children << this;
            
            if(p.attrs.has("style")){
                std::string_view    sname = p.attrs.string("style");
                const Style*s = dynamic_cast<const Style*>(m_frame->find(sname));
                if(s){
                    m_attrs.attrs   = s->attrs().attrs;
                } else {
                    b3Warning << "Sorry, style '" << sname << "' not found";
                }
            }
        }
    
        // explicit merge (in case there's a style)
        merge(p.attrs, true);
    }
    
    Obj::~Obj()
    {
    }

    std::string_view    Obj::attr(const std::string&k, std::string_view def) const
    {
        for(const Obj *obj = this; obj; obj=obj->m_frame){
            if(obj->m_attrs.has(k))
                return obj->m_attrs.string(k);
        }
        return def;
    }

    void        Obj::attr(const std::string&k, set_k, std::string_view v)
    {
        m_attrs[k] = std::string(v);
    }

    void        Obj::collect_args(DoubleMap& vars, std::span<const std::string> args) const
    {
        if(m_frame)
            m_frame->collect_args(vars, args);
        for(const std::string&k : args){
            if(m_attrs.has(k)){
                auto x = to_double(m_attrs.string(k));
                if(!x)
                    continue;
                vars[k] = *x;
            }
        }
    }

    bool        Obj::delegate(Meta::id_t i, void* arg)
    {
        for(const ObjMeta* objm = &metaInfo(); objm; objm = dynamic_cast<const ObjMeta*>(objm -> base())){
            auto fn     = objm->delegate(i);
            if(fn)
                return fn(arg, this);

            auto cfn    = objm->cDelegate(i);
            if(cfn)
                return cfn(arg, this);
        }
        return false;
    }

    bool        Obj::delegate(Meta::id_t i, void* arg) const
    {
        for(const ObjMeta* objm = &metaInfo(); objm; objm = dynamic_cast<const ObjMeta*>(objm -> base())){
            auto cfn    = objm->cDelegate(i);
            if(cfn)
                return cfn(arg, this);
        }
        return false;
    }

    Obj*        Obj::find(std::string_view path)
    {
        if(m_frame && !path.empty())    
            return m_frame -> find(path);
        return nullptr;
    }
    
    const Obj*  Obj::find(std::string_view path) const
    {
        if(m_frame && !path.empty())    
            return m_frame -> find(path);
        return nullptr;
    }

    std::string Obj::full_name() const
    {
        if(m_name.empty())
            return {};
            
        if(!m_frame)    
            return m_name;
            
            //  TODO
            
        return {};
    }

    bool            Obj::has_local_attribute(const std::string& k) const
    {
        return m_attrs.attrs.has(k);
    }

    void            Obj::hide()
    {
        m_flags |= F::Hide;
    }

    bool            Obj::is_terrain() const
    {
        return m_flags(F::Terrain);
    }
    
    bool            Obj::is_hidden() const
    {
        return m_flags(F::Hide);
    }

    void         Obj::merge(const ArgMap&atts, bool overwrite)
    {
        m_attrs.attrs.merge_map(atts.attrs, overwrite);
    }

    AxCorners23D Obj::to_global(const AxBox2D&v) const
    {
        return {
            to_global(v.ll().z()),
            to_global(v.lh().z()),
            to_global(v.hl().z()),
            to_global(v.hh().z())
        };
    }
    
    AxCorners33D Obj::to_global(const AxBox3D&v) const
    {
        return {
            to_global(v.lll()),
            to_global(v.llh()),
            to_global(v.lhl()),
            to_global(v.lhh()),
            to_global(v.hll()),
            to_global(v.hlh()),
            to_global(v.hhl()),
            to_global(v.hhh())
        };
    }
    
    Vector3D    Obj::to_global(const Vector3D&v) const
    {
        Vector3D    p   = v;
        for(const Frame* f = m_frame; f; f = f->m_frame){
            p   = f->to_parent(p);
        }
        return p;
    }
    
    Vector3D    Obj::to_global_msl(const Vector2D&v, double z) const
    {
        //  TODO
        return to_global(Vector3D(v.x, v.y, z));
    }
    
    Vector3D    Obj::to_global_agl(const Vector2D& v, double z) const
    {
        //  TODO
        return to_global(Vector3D(v.x, v.y, z));
    }

    Vector3D    Obj::to_local(const Vector3D& v) const
    {
        Stack<const Frame*>    fstk;
        Vector3D   p   = v;
        for(const Frame* f = m_frame; f; f = f->m_frame)
            fstk << f;
        while(!fstk.empty()){
            p = fstk.pop() -> to_frame(p);
        }
        return p;
    }

    std::string_view Obj::type_name() const
    {
        return metaInfo().stem();
    }
}
