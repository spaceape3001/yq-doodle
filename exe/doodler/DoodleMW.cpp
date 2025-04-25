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
    
    auto buttonbar     = app.buttonbar(Vector2F{0.75,1.0}, "Generic ToolBar");
    buttonbar.image("openicon/icons/png/32x32/actions/arrow-left-double.png", { 32, 32 }).action(&DoodleMW::btn_left);
    buttonbar.spacer({ 16, 32});
    buttonbar.button("FOO");
    buttonbar.button("BAR").action(&DoodleMW::bar);
    buttonbar.spacer({ 16, 32});
    buttonbar.image("openicon/icons/png/32x32/actions/arrow-right-double.png", { 32, 32 }).action(&DoodleMW::btn_right);
    
    auto subbar         = app.buttonbar(Vector2F{0.25, 1.0}, "Subbar");
    subbar.button("GENERIC").action(VISIBLE, buttonbar);
    
    auto win        = app.window("Window");
    win.label("Hello World!");
    
    help.checkbox(VISIBLE, win);
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

void DoodleMW::btn_left()
{
    yInfo() << "LEFT!";
}

void DoodleMW::btn_right()
{
    yInfo() << "RIGHT!";
}

YQ_TACHYON_IMPLEMENT(DoodleMW)
