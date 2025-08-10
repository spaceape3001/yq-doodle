////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <artQt/DocumentQ.hpp>
#include <gluon/core/WidgetQ.hpp>
#include <QWidget>

using namespace yq;
using namespace yq::art;
using namespace yq::gluon;

class DocEditorMeta : public WidgetQMeta {
public:
    template <typename> class Writer;
    DocEditorMeta(std::string_view, gluon::WidgetQMeta& base, const std::source_location& sl=std::source_location::current());
};

class DocEditor : public QWidget, public WidgetQ {
    Q_OBJECT
    
    YQ_OBJECT_META(DocEditorMeta)
    YQ_WIDGETQ_DECLARE(DocEditor, WidgetQ);
public:

    static void init_meta();
    DocEditor(DocumentQPtr doc, QWidget*parent);
    ~DocEditor();
    
protected:
    DocumentQPtr        m_doc;
};
