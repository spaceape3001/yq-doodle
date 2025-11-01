////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "DocTypeMenuUI.hpp"
#include <art/doc/Doc.hpp>
#include <tachyon/MyImGui.hpp>
#include <tachyon/parameters.hpp>
#include <tachyon/api/Payload.hpp>
#include <tachyon/ui/UIElementMetaWriter.hpp>
#include <yq/text/match.hpp>
#include <algorithm>

YQ_OBJECT_IMPLEMENT(yq::art::DocTypeMenuUI)

namespace yq::art {
    struct DocTypeMenuUI::Item {
        std::string     title;
        const DocMeta*  meta    = nullptr;
    };
    
    void DocTypeMenuUI::init_meta()
    {
        auto w = writer<DocTypeMenuUI>();
        w.description("Document Type Menu");
    }
    
    DocTypeMenuUI::DocTypeMenuUI(std::string_view kMenuName, tachyon::UIFlags flags) : 
        DocTypeMenuUI(kMenuName, tachyon::kParam_CreateMeta, flags)
    {
    }
    
    DocTypeMenuUI::DocTypeMenuUI(std::string_view kMenuName, uint32_t param, tachyon::UIFlags flags) : 
        tachyon::UIMenu(kMenuName, flags), m_param(param)
    {
    }
    
    DocTypeMenuUI::DocTypeMenuUI(const DocTypeMenuUI& cp) : tachyon::UIMenu(cp), 
        m_items(cp.m_items), m_param(cp.m_param), m_init(false)
    {
    }
    
    DocTypeMenuUI::~DocTypeMenuUI()
    {
    }
    
    void    DocTypeMenuUI::build_menu()
    {
        for(const DocMeta* dm : DocMeta::all()){
            assert(dm);
            if(!dm) [[unlikely]]
                continue;
            if(dm->is_abstract())
                continue;
            m_items.push_back({.title=std::string(dm->stem()), .meta=dm });
        }

        std::stable_sort(m_items.begin(), m_items.end(), [](const Item& a, const Item& b) -> bool {
            return is_less_igCase(a.title, b.title);
        });
    }
    
    DocTypeMenuUI* DocTypeMenuUI::clone() const 
    {
        return new DocTypeMenuUI(*this);
    }
    
    void DocTypeMenuUI::content() 
    {
        if(!m_init){
            build_menu();
            m_init = true;
        }
        
        for(const Item& i : m_items){
            if(ImGui::MenuItem(i.title.c_str())){
                triggered(tachyon::Payload().append(m_param, i.meta));
            }
        }
    }
}
