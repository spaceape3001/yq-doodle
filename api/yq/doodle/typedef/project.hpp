////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <memory>

namespace yq::doodle {
    class Project;
    using ProjectSPtr   = std::shared_ptr<Project>;
    using ProjectSCPtr  = std::shared_ptr<const Project>;
    using ProjectUPtr   = std::unique_ptr<Project>;
    using ProjectUCPtr  = std::unique_ptr<const Project>;
}
