////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "ArtMW.hpp"
#include <art/doc/Doc.hpp>
#include <artVk/DocTypeMenuUI.hpp>
#include <tachyon/MyImGui.hpp>
#include <tachyon/parameters.hpp>
#include <tachyon/api/Payload.hpp>
#include <tachyon/api/WidgetMetaWriter.hpp>
#include <tachyon/app/Application.hpp>
#include <tachyon/command/ui/TitleCommand.hpp>
#include <tachyon/ui/UIWriters.hxx>
#include <art/logging.hpp>

#include <algorithm>
#include <ImGuiFileDialog.h>


std::atomic<int> ArtMW::s_counter{0};

void ArtMW::init_meta()
{
    auto w          = writer<ArtMW>();
    auto app        = w.imgui(UI, APP);
    auto mmb        = app.menubar(MAIN);

    /////////////////////////////////
    //  MENUS

    auto file       = mmb.menu("File");
    auto edit       = mmb.menu("Edit");
    auto view       = mmb.menu("View");
    auto artM       = mmb.menu("Art");
    auto help       = mmb.menu("Help");
    auto rhs        = mmb.right(ALIGN);
    
    rhs.callback(&ArtMW::edit_title);

    /////////////////////////////////
    //  FILE MENU

    (file << new DocTypeMenuUI("New")).action(&ArtMW::action_create_new);

    file.menuitem("Open...", "Ctrl+O").action(&ArtMW::cmd_open);
    file.menuitem("Save", "Ctrl+S").action(&ArtMW::cmd_save);
    file.menuitem("Save As...").action(&ArtMW::cmd_save_as);
    file.menuitem("Save Copy...").action(&ArtMW::cmd_save_copy);


    /////////////////////////////////
    //  EDIT MENU

    edit.menuitem("Cut", "Ctrl+X");
    edit.menuitem("Copy", "Ctrl+C");
    edit.menuitem("Paste", "Ctrl+V");
    edit.menuitem("Delete", "Del");

    /////////////////////////////////
    //  VIEW MENU

    /////////////////////////////////
    //  ART MENU

    /////////////////////////////////
    //  HELP MENU


    /////////////////////////////////
    //  MISC

    
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

ArtMW::ArtMW(DocPtr p) : ArtDocPtr(p), m_number(s_counter++)
{
    assert(m_doc);
    if(!m_doc){
        cmd_teardown();
        return;
    }
}

ArtMW::~ArtMW()
{
}
    
void ArtMW::_copy(const std::filesystem::path& pth)
{
    if(!m_doc->save_xml(pth)){
        artWarning << "Unable to save copy to " << pth;
    }
}

void ArtMW::_open(const std::filesystem::path& pth)
{
    Application*    app = Application::app();
    if(!app){
        artWarning << "Can't open with no application";
        return ;
    }
        
    //  We'll get fancy on "open" to auto-close/take creds to current if no good document....
    
    DocPtr  doc = Doc::load_xml(pth);
    if(!doc){
        artWarning << "Unable to load/open document " << pth;
        return;
    }
    
    app->create(VIEWER, new ArtMW(doc));
}


void ArtMW::_save(const std::filesystem::path& pth)
{
    if(!m_doc->save_xml(pth)){
        artWarning << "Unable to save to " << m_doc->file();
        return ;
    }
    
    if(pth != m_doc->file()){
        m_doc -> set_file(pth);
        _update(TITLE);
    }
}

void ArtMW::_update(title_k)
{
    if(!m_doc)
        return;
        
    std::string     newTitle;
    if(m_doc->file().empty()){
        newTitle        = "Art";
    } else {
        auto& fp        = m_doc->file();
        newTitle        = std::format("{} - {} - Art", fp.filename().string(), fp.parent_path().string());
    }
    send(new TitleCommand({.source=*this, .target=TypedID(viewer().id, Type::Viewer)}, newTitle));
}

void ArtMW::action_create_new(const tachyon::Payload& pay)
{
    Application*    app = Application::app();
    if(!app)
        return ;
        
    for(auto& itr : as_iterable(pay.m_metas.equal_range(kParam_CreateMeta))){
        const DocMeta*   meta    = dynamic_cast<const DocMeta*>(itr.second);
        if(!meta)
            continue;
            
        Object*     obj = meta->create();
        if(!obj)
            continue;
        
        DocPtr      doc = dynamic_cast<Doc*>(obj);
        if(!doc){
            delete obj;
            continue;
        }
        
        
        app->create(VIEWER, Tachyon::create<ArtMW>(doc));
    }
}


void ArtMW::cmd_open()
{
    IGFD::FileDialogConfig config;
    if(m_doc->file().empty()){
        config.path = ".";
    } else {
        config.path = m_doc->file().parent_path();
    }
    m_fileMode  = FileMode::Open;
    ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File to Open", ".art", config);        
}

void ArtMW::cmd_save()
{
    if(m_doc->file().empty()){
        cmd_save_as();
    } else {
        _save(m_doc->file());
    }
}

void ArtMW::cmd_save_as()
{
    IGFD::FileDialogConfig config;
    if(m_doc->file().empty()){
        config.path = ".";
    } else {
        config.path = m_doc->file().parent_path();
    }
    config.flags |= ImGuiFileDialogFlags_ConfirmOverwrite;
    m_fileMode  = FileMode::Save;
    ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File to Save As", ".art", config);        
}

void ArtMW::cmd_save_copy()
{
    IGFD::FileDialogConfig config;
    if(m_doc->file().empty()){
        config.path = ".";
    } else {
        config.path = m_doc->file().parent_path();
    }
    config.flags |= ImGuiFileDialogFlags_ConfirmOverwrite;
    m_fileMode  = FileMode::Copy;
    ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File to Save Copy", ".art", config);        
}

void ArtMW::edit_title()
{
    if(!m_doc)
        return;
        
    static constexpr const size_t   kMax    = 40;
    char    data[kMax+1];
    size_t          mx  =    std::min<size_t>(m_doc->title().size(), kMax);
    strncpy(data, m_doc->title().data(), mx);
    data[mx]  = '\0';
    
    if(ImGui::InputText("##Title", data, kMax, ImGuiInputTextFlags_EnterReturnsTrue)){
        data[kMax]  = '\0';
        if(data != m_doc->title()){
            m_doc -> set_title(data);
        }
    }
}

void ArtMW::imgui(ViContext& u) 
{
    Widget::imgui(UI,u);

    if(m_fileMode != FileMode::None){
        ImVec2  minSize = { (float)(0.5 * width()), (float)(0.5 * height()) };
        if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey", ImGuiWindowFlags_NoCollapse, minSize)) {
            if (ImGuiFileDialog::Instance()->IsOk()) { // action if OK
                std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
                std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
                
artNotice << "ArtMW::imgui file ... '" << filePathName << "'/'" << filePath << "'";
                
                switch(m_fileMode){
                case FileMode::None:
                    break;
                case FileMode::Open:
                    _open(filePathName);
                    break;
                case FileMode::Save:
                    _save(filePathName);
                    break;
                case FileMode::Copy:
                    _copy(filePathName);
                    break;
                }
            }
            ImGuiFileDialog::Instance()->Close();
        }
    }
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
