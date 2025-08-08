////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "DocumentQ.hpp"

#include <art/Doc.hpp>
#include <gluon/core/QtTypes.hpp>
#include <QTimer>

namespace yq::art {
    using namespace yq::gluon;
 
    DocumentQPtr  DocumentQ::load(const QString&s, QObject* parent)
    {
        auto doc    = Doc::load_xml(yFilePath(s));
        if(!doc)
            return {};
        
        DocumentQPtr ret = new DocumentQ(doc, parent);
        ret -> m_filename   = s;
        return ret;
    }

    DocumentQ::DocumentQ(QObject*parent) : DocumentQ(new Doc, parent)
    {
    }

    DocumentQ::DocumentQ(DocPtr doc, QObject*parent) : QObject(parent), m_doc(doc)
    {
        assert(doc.valid());
        m_checker   = new QTimer(this);
        m_checker->setTimerType(Qt::CoarseTimer);
        m_checker->setInterval(100);
        connect(m_checker, &QTimer::timeout, this, &DocumentQ::checkDocument);
        m_checker -> start();
    }

    DocumentQ::~DocumentQ()
    {
    }

    void    DocumentQ::checkDocument()
    {
        if(m_checkPoint != m_doc->revision()){
            m_checkPoint    = m_doc->revision();
            emit documentChanged();
        }
    }

    void    DocumentQ::decrementEditors()
    {
        --m_editors;
    }

    QString     DocumentQ::filename() const
    {
        return m_filename;
    }

    bool        DocumentQ::hasFilename() const
    {
        return !m_filename.isEmpty();
    }

    void    DocumentQ::incrementEditors()
    {
        ++m_editors;
    }

    bool    DocumentQ::isDirty() const
    {
        return m_doc->revision() != m_savePoint;
    }

    bool    DocumentQ::isEmpty() const
    {
        return m_doc->is_empty() && m_filename.isEmpty();
    }

    bool    DocumentQ::save()
    {
        if(!saveTo(m_filename))
            return false;
        m_savePoint = m_doc->revision();
        return true;
    }

    bool    DocumentQ::saveTo(const QString&s) const
    {
        if(s.isEmpty())
            return false;
        return m_doc->save_xml(yFilePath(s));
    }
    
    bool    DocumentQ::saveAs(const QString&s)
    {
        if(!saveTo(s))
            return false;
        m_savePoint = m_doc->revision();
        if(s != m_filename){
            m_filename  = s;
            emit fileChanged(s);
        }
        return true;
    }

    void    DocumentQ::setTitle(const QString&str)
    {
        std::string     s   = str.toStdString();
        if(s == m_doc->title())
            return ;
        m_doc->set_title(s);
        emit titleChanged(str);
    }

    unsigned    DocumentQ::takeANumber()
    {
        return ++m_number;
    }

    QString     DocumentQ::title() const
    {
        using namespace yq::gluon;
        return qString(m_doc->title());
    }
}


#include "moc_DocumentQ.cpp"
