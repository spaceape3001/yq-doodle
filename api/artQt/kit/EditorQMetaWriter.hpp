////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/meta/ObjectMetaWriter.hpp>
#include <artQt/kit/EditorQ.hpp>

#define YQ_EDITORQ_IMPLEMENT(...) YQ_OBJECT_IMPLEMENT(__VA_ARGS__)

namespace yq::art {

    template <typename C>
    class EditorQMeta::Writer : public ObjectMeta::Writer<C> {
    public:
        Writer(EditorQMeta* dInfo) : ObjectMeta::Writer<C>(dInfo), m_meta(dInfo)
        {
        }
        
        Writer(EditorQMeta& dInfo) : Writer(&dInfo)
        {
        }

        //! Declares a new/extra menu for the application
        Writer& menu(const std::string& key, const std::string& label)
        {
            if(m_meta && Meta::thread_safe_write()){
                m_meta -> m_menus.push_back({key, label});
            }
            return *this;
        }

    private:
        EditorQMeta*    m_meta;
    };

    template <typename D>
    class EditorQFixer : public ObjectFixer<D> {
    public:
        EditorQFixer(std::string_view szName, typename D::MyBase::MyMeta& myBase, const std::source_location& sl = std::source_location::current()) :
            ObjectFixer<D>(szName, myBase, sl)
        {
        }

        EditorQ* create(DocumentQPtr doc, QWidget* parent = nullptr) const override
        {
            if constexpr (!D::kAbstract && !std::is_abstract_v<D>) {
                if(ObjectMeta::is_abstract()){
                    return nullptr;
                }
                typename D::MyDocQ*  dd  = dynamic_cast<typename D::MyDocQ*>(doc.ptr());
                if(!dd)
                    return nullptr;
                return new D(dd, parent);
            } else {
                return nullptr;
            }
        }

    protected:
        void    sweep_impl() override
        {
            ObjectFixer<D>::sweep_impl();
            using DocQ = typename D::MyDocQ;
            if constexpr (std::is_base_of_v<DocumentQ,DocQ> && !std::is_same_v<DocumentQ,DocQ>){
                EditorQMeta::reg_editor(&meta<DocQ>());
            }
        }
    };
}
