////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "DocumentQ.hpp"
#include "DocumentQMetaWriter.hpp"

#include <yq/art/doc/Doc.hpp>
#include <yq/gluon/core/QtTypes.hpp>
#include <QTimer>

YQ_OBJECTQ_IMPLEMENT(yq::art::DocumentQ)

namespace yq::art {
    using namespace yq::gluon;

    struct DocumentQ::Repo {
        Map<Meta::id_t, const DocumentQMeta*>   doc2docQ;
    };

////////////////////////////////////////////////////////////////////////////////

    DocumentQMeta::DocumentQMeta(std::string_view name, ObjectQMeta& base, const std::source_location& sl) :
        ObjectQMeta(name, base, sl)
    {
    }

    void    DocumentQMeta::reg_document()
    {
        DocumentQ::repo().doc2docQ[m_doc->id()]    = this;
    }
 
////////////////////////////////////////////////////////////////////////////////

    void DocumentQ::init_meta()
    {
        auto w = writer<DocumentQ>();
        w.description("Art's QDocument");
    }

    DocumentQPtr  DocumentQ::load(const QString&s, QObject* parent)
    {
        auto doc    = Doc::load_xml(yFilePath(s));
        if(!doc)
            return {};
            
        DocumentQPtr ret;
        if(const DocumentQMeta* dm = repo().doc2docQ.get(doc->metaInfo().id(), nullptr)){
            ret = dm -> create(doc, parent);
        } 
        
        if(!ret)
            ret = new DocumentQ(doc, parent);
            
        ret -> m_filename   = s;
        return ret;
    }

    DocumentQ::Repo& DocumentQ::repo()
    {
        static Repo     s_repo;
        return s_repo;
    }

////////////////////////////////////////////////////////////////////////////////

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

    void DocumentQ::startAutoChecking()
    {
        m_checker -> start();
    }
    
    void DocumentQ::stopAutoChecking()
    {
        m_checker -> stop();
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
