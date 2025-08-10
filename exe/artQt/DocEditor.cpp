////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "DocEditor.hpp"
#include <gluon/core/WidgetQMetaWriter.hpp>

YQ_WIDGETQ_IMPLEMENT(DocEditor)

void DocEditor::init_meta()
{
}

DocEditor::DocEditor(DocumentQPtr doc, QWidget*parent) : QWidget(parent), m_doc(doc)
{
}

DocEditor::~DocEditor()
{
}

#include "moc_DocEditor.cpp"
