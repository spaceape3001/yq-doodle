////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "DoodleMW.hpp"
#include <ya/widgets/AppWidgetInfoWriter.hpp>
#include <doodle/Project.hpp>
#include <yt/ui/MyImGui.hpp>

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
    
void DoodleMW::menubar(ViContext&) 
{
    if(ImGui::BeginMenu("File")){
        ImGui::EndMenu();
    }
    if(ImGui::BeginMenu("Edit")){
        ImGui::EndMenu();
    }
    if(ImGui::BeginMenu("View")){
        ImGui::EndMenu();
    }
    if(ImGui::BeginMenu("Window")){
        ImGui::EndMenu();
    }
    if(ImGui::BeginMenu("Help")){
        ImGui::EndMenu();
    }
    if(ImGui::BeginMenu("Debug")){
        ImGui::EndMenu();
    }
    
    ImGui::SameLine();
    ImGui::Text("Hello There!");
}

void DoodleMW::init_info()
{
    auto w = writer<DoodleMW>();
    w.imgui();
    w.menubar();
}

YQ_TACHYON_IMPLEMENT(DoodleMW)
