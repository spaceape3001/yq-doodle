////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/gluon/core/ObjectQMetaWriter.hpp>
#include <yq/artQt/DocumentQ.hpp>

namespace yq::art {
    template <typename C>
    class DocumentQMeta::Writer : public gluon::ObjectQMeta::Writer<C> {
    public:
        Writer(DocumentQMeta* dInfo) : gluon::ObjectQMeta::Writer<C>(dInfo), m_meta(dInfo)
        {
        }
        
        Writer(DocumentQMeta& dInfo) : Writer(&dInfo)
        {
        }

    private:
        DocumentQMeta*    m_meta;
    };
    
    template <typename D>
    class DocumentQFixer : public gluon::ObjectQFixer<D> {
    public:
        DocumentQFixer(std::string_view szName, typename D::MyBase::MyMeta& myBase, const std::source_location& sl = std::source_location::current()) :
            gluon::ObjectQFixer<D>(szName, myBase, sl)
        {
        }

        DocumentQ* create(DocPtr doc, QObject*parent) const override 
        {
            if constexpr (!D::kAbstract && !std::is_abstract_v<D>) {
                if(ObjectMeta::is_abstract()){
                    return nullptr;
                }
                typename D::MyDocument*  dd  = dynamic_cast<typename D::MyDocument*>(doc.ptr());
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
            gluon::ObjectQFixer<D>::sweep_impl();
            if constexpr (std::is_base_of_v<Doc,D> && !std::is_same_v<Doc,D>){
                if(!DocumentQMeta::m_doc){
                    DocumentQMeta::m_doc   = &meta<D>();
                    DocumentQMeta::reg_document();
                }
            }
        }
    };
}

