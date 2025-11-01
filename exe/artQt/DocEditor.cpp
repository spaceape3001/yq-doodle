////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "DocEditor.hpp"
#include <yq/artQt/kit/EditorQMetaWriter.hpp>

YQ_EDITORQ_IMPLEMENT(DocEditor)

void DocEditor::init_meta()
{
}

DocEditor::DocEditor(DocumentQPtr doc, QWidget*parent) : QWidget(parent), EditorQ(doc)
{
}

DocEditor::~DocEditor()
{
}

#include "moc_DocEditor.cpp"
