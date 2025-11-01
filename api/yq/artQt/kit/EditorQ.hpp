////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/trait/no_hidden_warning.hpp>
#include <yq/core/Object.hpp>
#include <artQt/DocumentQ.hpp>
#include <yq/typedef/string_pairs.hpp>

namespace yq::gluon {
    class MainWindow;
}

namespace yq::art {

    class EditorQ;
    template <typename> class EditorQFixer;

    class EditorQMeta : public ObjectMeta {
    public:
        template <typename> class Writer;
        EditorQMeta(std::string_view, ObjectMeta& base, const std::source_location& sl=std::source_location::current());
        
        virtual EditorQ*    create(DocumentQPtr, QWidget* parent = nullptr) const = 0;

        const std::vector<string_pair_t>& menus() const { return m_menus; }

    private:
        template <typename> friend class EditorQFixer;
        void                    reg_editor(const DocumentQMeta*);
        const DocumentQMeta*        m_docQ  = nullptr;    
        std::vector<string_pair_t>  m_menus;
    };
    
    #define YQ_EDITORQ_DECLARE_ABSTRACT(cls, base)          \
        YQ_OBJECT_DECLARE(cls, base)                        \
        static constexpr const bool kAbstract   = true;
        
    #define YQ_EDITORQ_DECLARE(cls, base)                   \
        YQ_OBJECT_DECLARE(cls, base)                        \
        static constexpr const bool kAbstract   = false;

    //! Class for describing editors of documents
    //! \note This isn't a QObject/QWidget itself, meant to be flexible
    //! Intent here is to let the document type flex a bit on the menus, and of course, the
    //! Central widget
    class EditorQ : public Object {
        YQ_OBJECT_META(EditorQMeta)
        YQ_OBJECT_FIXER(EditorQFixer)
        YQ_EDITORQ_DECLARE_ABSTRACT(EditorQ, Object)
    public:
        
        static void init_meta();
        
        static const EditorQMeta* find(const DocumentQMeta&);
        
        using MyDocQ        = DocumentQ;
            
        EditorQ(DocumentQPtr doc);
        ~EditorQ();
        
        DocumentQ*          doc() { return m_doc.ptr(); }
        const DocumentQ*    doc() const { return m_doc.ptr(); }
        
        QWidget*            qWidget();
        const QWidget*      qWidget() const;

        virtual void        configure(gluon::MainWindow&){}

    protected:
        DocumentQPtr        m_doc;
        
    private:
        friend class EditorQMeta;
        struct Repo;
        static Repo& repo();
    };
}
