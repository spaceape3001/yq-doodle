////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QObject>
#include <doodle/Project.hpp>
#include <yq/core/Ref.hpp>
#include <gluon/core/RefQ.hpp>

namespace yq::doodle {
    class ProjectQ;

    using ProjectQPtr   = Ref<ProjectQ>;

    class ProjectQ : public QObject, public gluon::RefQ {
        Q_OBJECT
    public:
    
        static ProjectQPtr  load(const QString&, SFormat sf=SFormat::AUTO);

        ProjectQ(QObject*parent=nullptr);
        virtual ~ProjectQ();
        
        QString         filename() const;
        bool            hasFilename() const;
        bool            isDirty() const;
        bool            isEmpty() const;
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
        
    public slots:
        void        setTitle(const QString&);
        
        bool        saveAs(const QString&);
        bool        save();
    
    private:
        Project     m_project;
        QString     m_filename;
        revision_t  m_savePoint = {};
        unsigned    m_number    = 0;
        unsigned    m_editors   = 0;
    };
    
}

