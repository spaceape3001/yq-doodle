////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/typedef/string.hpp>
#include <yq/typedef/string_maps.hpp>
#include <yq/typedef/expected.hpp>
#include <doodle/typedef/revision.hpp>
#include <doodle/keywords.hpp>
#include <yq/text/IgCase.hpp>
#include <set>
#include <map>

namespace yq {
    struct IgCase;
}

namespace yq::doodle {
    class Project;
    class DObject;
    struct ID;
    
    /*! An evaluator of user expressions within the doodle project
    
    */
    class Evaluator {
    public:
        //! Warning, the project MUST exist the whole duration
        Evaluator(const Project&, const u32string_any_map_t& overrides={});
        Evaluator(const Project&, const string_any_map_t& overrides);
        ~Evaluator();
        
        any_x               evaluate(ID, const std::string&);
        any_x               evaluate(const std::string&);
        any_x               evaluate(uid_k, const std::string&, const std::string&);
        
        void                set_override(std::string_view, Any&&);
        void                set_override(std::u32string_view, Any&&);

        void                set_override(ID, std::string_view, Any&&);
        void                set_override(ID, std::u32string_view, Any&&);
        
        Any                 get_override(std::string_view) const;
        Any                 get_override(const std::u32string&) const;
        
        bool                is_override(std::string_view) const;
        bool                is_override(const std::u32string&) const;
        
    private:
        struct Dep;
        struct Ergo;
        
        
        using StrIDKey          = std::pair<std::string,ID>;
        using U32StrIDKey       = std::pair<std::u32string,ID>;
        
        struct StrIDLess {
            static bool operator()(const StrIDKey&, const StrIDKey&);
            static bool operator()(const U32StrIDKey&, const U32StrIDKey&);
        };
        
        using ProjectAttrMap    = std::map<std::string,Ergo*,IgCase>;
        using DObjectAttrMap    = std::map<StrIDKey,Ergo*,StrIDLess>;
        using DObjectVarMap     = std::map<U32StrIDKey,Any,StrIDLess>;
        
        const Project&              m_project;
        std::map<uint64_t,Ergo*>    m_ergos;        //!< Current ergos, all valid to destructor
        ProjectAttrMap              m_prjAttrs;
        DObjectAttrMap              m_objAttrs;
        u32string_any_map_t         m_overrides;    //! Full override...
        DObjectVarMap               m_objVars;      //! Object overrides
        
        Ergo*   ergo(ID, const std::string&);
        bool    update(Ergo&);  //!< Updates ergo, returns TRUE if there's a change
        bool    update(Ergo&,std::set<uint64_t>&); //!< Updates ergo, returns TRUE if there's a change
        bool    needs_parsing(Ergo&) const;
        bool    fetch(Ergo&) const;
        bool    parse(Ergo&) const;
        bool    redep(Ergo&);

        Evaluator(Project&&) = delete;  // if you foul here, its a temporary, which is illegal here
        Evaluator(const Evaluator&) = delete;
        Evaluator& operator=(const Evaluator&) = delete;
        Evaluator(Evaluator&&) = delete;
        Evaluator& operator=(Evaluator&&) = delete;
        
    };
    
    
    
}
