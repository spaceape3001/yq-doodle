////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "ProjectQ.hpp"

#include <gluon/core/QtTypes.hpp>

namespace yq::doodle {
    ProjectQPtr  ProjectQ::load(const QString& fp)
    {
        using namespace yq::gluon;
        ProjectQPtr     qpp = new ProjectQ;
        if(qpp -> load_impl(yFilePath(fp)))
            return qpp;
        return {};
    }

    ProjectQ::ProjectQ(QObject*parent) : QObject(parent)
    {
    }
    
    ProjectQ::~ProjectQ()
    {
    }

    QString     ProjectQ::fileName() const
    {
        using namespace yq::gluon;
        return qFilePath(file());
    }

    void    ProjectQ::saveTo(const QString&s) const
    {
        using namespace yq::gluon;
        save_to(yFilePath(s));
    }
    
    void    ProjectQ::saveAs(const QString&s)
    {
        using namespace yq::gluon;
        if(save_as(yFilePath(s)) == std::error_code()){
            emit fileChanged(s);
        }
    }

    void    ProjectQ::setTitle(const QString&str)
    {
        using namespace yq::gluon;
        set_title(yString(str));
        emit titleChanged(str);
    }

    QString     ProjectQ::title() const
    {
        using namespace yq::gluon;
        return qString(Project::title());
    }
}


#include "moc_ProjectQ.cpp"

