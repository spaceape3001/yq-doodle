////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "EditorQ.hpp"
#include "EditorQMetaWriter.hpp"
#include <QWidget>

YQ_EDITORQ_IMPLEMENT(yq::art::EditorQ)

namespace yq::art {
    struct EditorQ::Repo {
        Map<Meta::id_t, const EditorQMeta*>     doc2editor;
    };

////////////////////////////////////////////////////////////////////////////////

    EditorQMeta::EditorQMeta(std::string_view name, ObjectMeta& base, const std::source_location& sl) :
        ObjectMeta(name, base, sl)
    {
    }

    void EditorQMeta::reg_editor(const DocumentQMeta* doc)
    {
        if(doc && !m_docQ){
            m_docQ  = doc;
            EditorQ::repo().doc2editor[doc->id()]   = this;
        }
    }

////////////////////////////////////////////////////////////////////////////////

    const EditorQMeta* EditorQ::find(const DocumentQMeta& dm)
    {
        return repo().doc2editor.get(dm.id(), nullptr);
    }

    void EditorQ::init_meta()
    {
        auto w = writer<EditorQ>();
        w.description("Abstract Editor for DocumentQ's");
    }

    EditorQ::Repo& EditorQ::repo()
    {
        static Repo s_repo;
        return s_repo;
    }

////////////////////////////////////////////////////////////////////////////////
        
    EditorQ::EditorQ(DocumentQPtr doc) : m_doc(doc)
    {
    }
    
    EditorQ::~EditorQ()
    {
    }


    QWidget*    EditorQ::qWidget()
    {
        return dynamic_cast<QWidget*>(this);
    }
    
    const QWidget*    EditorQ::qWidget() const
    {
        return dynamic_cast<const QWidget*>(this);
    }
}
