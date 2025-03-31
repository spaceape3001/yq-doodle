////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <ya/widgets/AppWidget.hpp>
#include <doodle/typedef/project.hpp>

using namespace yq;
using namespace yq::doodle;
using namespace yq::tachyon;

class DoodleMW : public AppWidget {
    YQ_TACHYON_DECLARE(DoodleMW, AppWidget)
public:
    DoodleMW();
    DoodleMW(ProjectSPtr);
    ~DoodleMW();
    
    static void init_info();
    
    bool    menubar(enabled_k) const override { return true; }
    void    menubar(ViContext&) override;
    
private:
    ProjectSPtr     m_project;
};
