////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QObject>
#include <art/forward.hpp>
#include <yq/core/Ref.hpp>
#include <gluon/core/RefQ.hpp>
#include <gluon/core/ObjectQ.hpp>
#include <art/Doc.hpp>

class QTimer;
class QWidget;

namespace yq::art {
    class DocumentQ;

    using DocumentQPtr   = Ref<DocumentQ>;
    
    template <typename> class DocumentQFixer;
    
    class DocumentQMeta : public gluon::ObjectQMeta {
    public:
        template <typename> class Writer;
        
        DocumentQMeta(std::string_view, gluon::ObjectQMeta& base, const std::source_location& sl=std::source_location::current());
        
        virtual DocumentQ* create(DocPtr, QObject*) const = 0;
        
    protected:
        const DocMeta*          m_doc   = nullptr;
        void                    reg_document();
    };

    class DocumentQ : public QObject, public gluon::ObjectQ, public gluon::RefQ {
        YQ_OBJECT_META(DocumentQMeta)
        YQ_OBJECT_FIXER(DocumentQFixer)
        YQ_OBJECTQ_DECLARE(DocumentQ, gluon::ObjectQ)
        Q_OBJECT
    public:
    
        using MyDocument        = Doc;
    
        static void init_meta();
    
        // will return NULL if file can't be loaded/parsed
        static DocumentQPtr  load(const QString&, QObject* parent=nullptr);

        DocumentQ(QObject*parent=nullptr);
        DocumentQ(DocPtr, QObject*parent=nullptr);
        
        QString         filename() const;
        bool            hasFilename() const;
        bool            isDirty() const;
        bool            isEmpty() const;
        Doc&            document() { return *m_doc; }
        const Doc&      document() const { return *m_doc; }
        bool            saveTo(const QString&) const;
        QString         title() const;
        
        ////////////////////////////
        //  For editor usage
        
        //! Editors get a number to distinguish the windows
        unsigned        takeANumber();
        
        //! Increment editor count
        void            incrementEditors();

        //! Decrement editor count
        void            decrementEditors();
        
        //! Count of editors left
        bool            editorsLeft() const { return m_editors; }

    signals:
        void            titleChanged(const QString&);
        void            fileChanged(const QString&);
        void            documentChanged();
        
    public slots:
        void            setTitle(const QString&);
        
        bool            saveAs(const QString&);
        bool            save();
    
        void            startAutoChecking();
        void            stopAutoChecking();
    
    private slots:
        void            checkDocument();
        
    protected:
        virtual ~DocumentQ();
    
    private:
        
        friend class DocumentQMeta;
        struct Repo;
        static Repo& repo();
        
        DocPtr      m_doc;
        QString     m_filename;
        QTimer*     m_checker       = nullptr;
        revision_t  m_checkPoint    = {};
        revision_t  m_savePoint     = {};
        unsigned    m_number        = 0;
        unsigned    m_editors       = 0;
    };
    
}

