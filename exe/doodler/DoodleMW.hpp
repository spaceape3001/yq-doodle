////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <tachyon/api/Widget.hpp>
#include <doodle/typedef/project.hpp>

using namespace yq;
using namespace yq::doodle;
using namespace yq::tachyon;

class DoodleMW : public Widget {
    YQ_TACHYON_DECLARE(DoodleMW, Widget)
public:
    DoodleMW();
    DoodleMW(ProjectSPtr);
    ~DoodleMW();
    
    static void init_info();
    
    void    imgui(ViContext&) override;
    
    void    bar();
    
    void    btn_left();
    void    btn_right();

    void    new_drawing();

private:
    ProjectSPtr     m_project;
};
