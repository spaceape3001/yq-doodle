////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/ID.hpp>
#include <yq/typedef/string_maps.hpp>
#include <yq/typedef/expected.hpp>


namespace yq::doodle {
    class Project;
    class DObject;
    
    class Evaluator {
    public:
        //! Warning, the project MUST exist the whole duration
        Evaluator(const Project&);
        ~Evaluator();
        
        any_x               evaluate(std::string_view, const string_any_map_t& projVars) const;
        string_any_map_t    evaluate_all(const string_any_map_t& projVars) const;
        
    private:
        struct Obj;
        struct Dep;
        struct Value;
    
        using value_map_t        = std::map<std::string,Value,IgCase>;
    
        const Project&              m_project;
        value_map_t                 m_attributes;

        Evaluator(Project&&) = delete;  // if you foul here, its a temporary, which is illegal here
    };
    
    
    
}
