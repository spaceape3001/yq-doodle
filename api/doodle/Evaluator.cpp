////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Evaluator.hpp"
#include "Project.hpp"

namespace yq::doodle {

    struct Evaluator::Value {
        Any     value;
    };

    Evaluator::Evaluator(const Project& prj) : m_project(prj)
    {
    }
    
    Evaluator::~Evaluator()
    {
    }
}
