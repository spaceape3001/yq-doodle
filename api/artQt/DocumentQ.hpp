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

class QTimer;

namespace yq::art {
    class DocumentQ;

    using DocumentQPtr   = Ref<DocumentQ>;

    class DocumentQ : public QObject, public gluon::RefQ {
        Q_OBJECT
    public:
    
        // will return NULL if file can't be loaded/parsed
        static DocumentQPtr  load(const QString&, QObject* parent=nullptr);

        DocumentQ(QObject*parent=nullptr);
        
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
        void        titleChanged(const QString&);
        void        fileChanged(const QString&);
        void        documentChanged();
        
    public slots:
        void        setTitle(const QString&);
        
        bool        saveAs(const QString&);
        bool        save();
    
    private slots:
        void        checkDocument();
        
    protected:
        virtual ~DocumentQ();
    
    private:
        
        DocumentQ(DocPtr, QObject*parent=nullptr);
    
        DocPtr      m_doc;
        QString     m_filename;
        QTimer*     m_checker       = nullptr;
        revision_t  m_checkPoint    = {};
        revision_t  m_savePoint     = {};
        unsigned    m_number        = 0;
        unsigned    m_editors       = 0;
    };
    
}

