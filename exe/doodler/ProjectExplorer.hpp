////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/tachyon/ui/UIWindow.hpp>

using namespace yq::tachyon;
using namespace yq::doodle;

class ProjectExplorer : public UIWindow {
    YQ_OBJECT_DECLARE(ProjectExplorer, UIWindow)
public:
    ProjectExplorer(UIFlags flags={});
    ~ProjectExplorer();
};
