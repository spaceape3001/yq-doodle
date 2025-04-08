////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "DoodleMW.hpp"
#include <doodle/Project.hpp>
#include <yt/ui/MyImGui.hpp>
#include <yt/ui/WidgetInfoWriter.hpp>
#include <yt/ui/UIWriter.hxx>
#include <yq/core/Logging.hpp>

void DoodleMW::init_info()
{
    auto w = writer<DoodleMW>();
    w.imgui();
    
    auto mmb        = w.menubar(MAIN);
    auto file       = mmb.menu("File");
    auto edit       = mmb.menu("Edit");
    auto view       = mmb.menu("View");
    auto window     = mmb.menu("Window");
    auto help       = mmb.menu("Help");

    auto open       = file.menuitem("Open", "Ctrl+O");
    auto save       = file.menuitem("Save", "Ctrl+S");

    edit.menuitem("Copy", "Ctrl+C");
    edit.menuitem("Paste", "Ctrl+V");
    
    auto toolbar    = w.toolbar(UIBorder::NNW, "Generic ToolBar");
    toolbar.button("FOO");
    toolbar.button("BAR", &DoodleMW::bar);
    
    auto win        = w.window("Window");
    win.label("Hello World!");
}

DoodleMW::DoodleMW() : DoodleMW(std::make_shared<Project>())
{
}

DoodleMW::DoodleMW(ProjectSPtr p) : m_project(p)
{
    assert(m_project);
}

DoodleMW::~DoodleMW()
{
}
    
void DoodleMW::imgui(ViContext& u) 
{
    Widget::imgui(UI,u);
}

void DoodleMW::bar()
{
    yInfo() << "BAR!";
}

YQ_TACHYON_IMPLEMENT(DoodleMW)
