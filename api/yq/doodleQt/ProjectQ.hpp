////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QObject>
#include <yq/doodle/Project.hpp>
#include <yq/core/Ref.hpp>
#include <yq/gluon/core/RefQ.hpp>

class QTimer;

namespace yq::doodle {
    class ProjectQ;

    using ProjectQPtr   = Ref<ProjectQ>;

    class ProjectQ : public QObject, public gluon::RefQ {
        Q_OBJECT
    public:
    
        static ProjectQPtr  load(const QString&);

        ProjectQ(QObject*parent=nullptr);
        virtual ~ProjectQ();
        
        QString         filename() const;
        bool            hasFilename() const;
        bool            isDirty() const;
        bool            isEmpty() const;
        Project&        project() { return m_project; }
        const Project&  project() const { return m_project; }
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
        void        projectChanged();
        
    public slots:
        void        setTitle(const QString&);
        
        bool        saveAs(const QString&);
        bool        save();
    
    private slots:
        void        checkProject();
    
    private:
        Project     m_project;
        QString     m_filename;
        QTimer*     m_checker       = nullptr;
        revision_t  m_checkPoint    = {};
        revision_t  m_savePoint     = {};
        unsigned    m_number        = 0;
        unsigned    m_editors       = 0;
    };
    
}

