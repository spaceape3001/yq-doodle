////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "ProjectQ.hpp"

#include <yq/gluon/core/QtTypes.hpp>
#include <QTimer>

using namespace yq::gluon;

namespace yq::doodle {
    ProjectQPtr  ProjectQ::load(const QString& fp)
    {
        ProjectQPtr     qpp;
        if(!Project::load(yFilePath(fp), 
            [&]() -> Project* {
                qpp = new ProjectQ;
                return &(qpp->m_project);
            }
        )){
            return {};
        }
        qpp->m_filename     = fp;
        qpp->m_savePoint    = qpp->m_project.revision();
        qpp->m_checkPoint   = qpp->m_project.revision();
        return qpp;
    }

    ProjectQ::ProjectQ(QObject*parent) : QObject(parent)
    {
        m_checker   = new QTimer(this);
        m_checker->setTimerType(Qt::CoarseTimer);
        m_checker->setInterval(100);
        connect(m_checker, &QTimer::timeout, this, &ProjectQ::checkProject);
        m_checker -> start();
    }
    
    ProjectQ::~ProjectQ()
    {
    }

    void    ProjectQ::checkProject()
    {
        if(m_checkPoint != m_project.revision()){
            m_checkPoint    = m_project.revision();
            emit projectChanged();
        }
    }

    void    ProjectQ::decrementEditors()
    {
        --m_editors;
    }

    QString     ProjectQ::filename() const
    {
        return m_filename;
    }

    bool        ProjectQ::hasFilename() const
    {
        return !m_filename.isEmpty();
    }

    void    ProjectQ::incrementEditors()
    {
        ++m_editors;
    }

    bool    ProjectQ::isDirty() const
    {
        return m_project.revision() != m_savePoint;
    }

    bool    ProjectQ::isEmpty() const
    {
        return m_project.is_empty() && m_filename.isEmpty();
    }

    bool    ProjectQ::save()
    {
        if(!saveTo(m_filename))
            return false;
        m_savePoint = m_project.revision();
        return true;
    }

    bool    ProjectQ::saveTo(const QString&s) const
    {
        if(s.isEmpty())
            return false;
        return m_project.save(yFilePath(s));
    }
    
    bool    ProjectQ::saveAs(const QString&s)
    {
        if(!saveTo(s))
            return false;
        m_savePoint = m_project.revision();
        if(s != m_filename){
            m_filename  = s;
            emit fileChanged(s);
        }
        return true;
    }

    void    ProjectQ::setTitle(const QString&str)
    {
        std::string     s   = str.toStdString();
        if(s == m_project.title())
            return ;
        m_project.set_title(s);
        emit titleChanged(str);
    }

    unsigned    ProjectQ::takeANumber()
    {
        return ++m_number;
    }

    QString     ProjectQ::title() const
    {
        using namespace yq::gluon;
        return qString(m_project.title());
    }
}


#include "moc_ProjectQ.cpp"

