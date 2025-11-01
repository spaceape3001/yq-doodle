////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/tachyon/ui/UIMenu.hpp>

namespace yq::art {
    class DocTypeMenuUI : public tachyon::UIMenu {
        YQ_OBJECT_DECLARE(DocTypeMenuUI, tachyon::UIMenu)
    public:
        static void init_meta();
        DocTypeMenuUI(std::string_view, tachyon::UIFlags flags={});
        DocTypeMenuUI(std::string_view, uint32_t, tachyon::UIFlags flags={});
        DocTypeMenuUI(const DocTypeMenuUI&);
        
        ~DocTypeMenuUI();
        
        virtual DocTypeMenuUI* clone() const override;
        void content() override;
    private:
        struct Item;
        std::vector<Item>   m_items;
        uint32_t            m_param;
        bool                m_init  = false;
        void                build_menu();
    };

}
