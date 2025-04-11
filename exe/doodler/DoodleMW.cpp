////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "DoodleMW.hpp"
#include <doodle/Project.hpp>
#include <yt/ui/MyImGui.hpp>
#include <yt/ui/WidgetInfoWriter.hpp>
#include <yt/ui/UIWriters.hxx>
#include <yq/core/Logging.hpp>

void DoodleMW::init_info()
{
    auto w          = writer<DoodleMW>();
    
    auto app        = w.imgui(UI, APP);
    auto mmb        = app.menubar(MAIN);
    auto file       = mmb.menu("File");
    auto edit       = mmb.menu("Edit");
    auto view       = mmb.menu("View");
    auto window     = mmb.menu("Window");
    auto help       = mmb.menu("Help");

    auto open       = file.menuitem("Open", "Ctrl+O");
    auto save       = file.menuitem("Save", "Ctrl+S");

    edit.menuitem("Copy", "Ctrl+C");
    edit.menuitem("Paste", "Ctrl+V");
    
    auto toolbar    = app.toolbar(Vector2F{0.75,1.0}, "Generic ToolBar");
    toolbar.button("FOO");
    toolbar.button("BAR", &DoodleMW::bar);
    
    auto win        = app.window("Window");
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
