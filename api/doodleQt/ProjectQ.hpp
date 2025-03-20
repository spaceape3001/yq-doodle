////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QObject>
#include <doodle/typedef/project.hpp>
#include <yq/core/Ref.hpp>

namespace yq::doodle {
    class ProjectQ;

    using ProjectQPtr   = Ref<ProjectQ>;

    class ProjectQ : public QObject, public Project, public RefCount {
        Q_OBJECT
    public:
    
        ProjectQ(QObject*parent=nullptr);
        virtual ~ProjectQ();
        
        QString     fileName() const;
        QString     title() const;
        
        static ProjectQPtr  load(const QString&);
        
    signals:
        void        titleChanged(const QString&);
        void        fileChanged(const QString&);
        
    public slots:
        void        setTitle(const QString&);
        
        void        saveTo(const QString&) const;
        void        saveAs(const QString&);
        
    };
    
}

