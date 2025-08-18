////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "ArtMW.hpp"
#include <art/doc/Canvas.hpp>
#include <artVk/DocTypeMenuUI.hpp>
#include <tachyon/MyImGui.hpp>
#include <tachyon/api/WidgetMetaWriter.hpp>
#include <tachyon/ui/UIWriters.hxx>
#include <art/logging.hpp>

void ArtMW::init_meta()
{
    auto w          = writer<ArtMW>();
    
    auto app        = w.imgui(UI, APP);
    auto mmb        = app.menubar(MAIN);
    auto file       = mmb.menu("File");
    auto edit       = mmb.menu("Edit");
    auto artM       = mmb.menu("Art");
    auto view       = mmb.menu("View");
    auto window     = mmb.menu("Window");
    auto help       = mmb.menu("Help");

    auto newW       = file << new DocTypeMenuUI("New");


    auto open       = file.menuitem("Open", "Ctrl+O");
    auto save       = file.menuitem("Save", "Ctrl+S");

    edit.menuitem("Copy", "Ctrl+C");
    edit.menuitem("Paste", "Ctrl+V");
    
    //artM.menuitem("New Drawing", "Ctrl+I").action(&ArtMW::new_drawing);
    
    
    auto buttonbar     = app.toolbar(Vector2F{0.75,1.0}, "Generic ToolBar");
    buttonbar.image("openicon/icons/png/32x32/actions/arrow-left-double.png", { 32, 32 }).action(&ArtMW::btn_left);
    buttonbar.spacer({ 16, 32});
    buttonbar.button("FOO");
    buttonbar.button("BAR").action(&ArtMW::bar);
    buttonbar.spacer({ 16, 32});
    buttonbar.image("openicon/icons/png/32x32/actions/arrow-right-double.png", { 32, 32 }).action(&ArtMW::btn_right);
    
    auto subbar         = app.toolbar(Vector2F{0.25, 1.0}, "Subbar");
    subbar.button("GENERIC").action(VISIBLE, buttonbar);
    
    auto win        = app.window("Window");
    win.label("Hello World!");
    
    help.checkbox(VISIBLE, win);
}

ArtMW::ArtMW() : ArtMW(new Canvas)
{
}

ArtMW::ArtMW(DocPtr p) : ArtDocPtr(p)
{
    assert(m_doc);
}

ArtMW::~ArtMW()
{
}
    
void ArtMW::imgui(ViContext& u) 
{
    Widget::imgui(UI,u);
}

void ArtMW::bar()
{
    artInfo << "BAR!";
}

void ArtMW::btn_left()
{
    artInfo << "LEFT!";
}

void ArtMW::btn_right()
{
    artInfo << "RIGHT!";
}

void ArtMW::new_drawing()
{
    artInfo << "New drawing requested";
}


YQ_TACHYON_IMPLEMENT(ArtMW)
