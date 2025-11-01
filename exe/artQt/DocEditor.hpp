////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/artQt/DocumentQ.hpp>
#include <yq/artQt/kit/EditorQ.hpp>
#include <QWidget>

using namespace yq;
using namespace yq::art;
using namespace yq::gluon;

class DocEditor : public QWidget, public EditorQ {
    Q_OBJECT
    
    YQ_EDITORQ_DECLARE(DocEditor, EditorQ);
public:

    static void init_meta();
    DocEditor(DocumentQPtr doc, QWidget* parent=nullptr);
    ~DocEditor();
    
};
