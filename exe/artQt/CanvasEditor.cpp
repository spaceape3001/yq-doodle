////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "CanvasEditor.hpp"
#include <artQt/EditorQMetaWriter.hpp>
#include <artQt/SceneQ.hpp>
#include <artQt/ViewQ.hpp>
#include <QHBoxLayout>
#include <QLabel>

YQ_EDITORQ_IMPLEMENT(CanvasEditor)

void CanvasEditor::init_meta()
{   
    auto w = writer<CanvasEditor>();
    w.description("Canvas Editor");
    w.menu("canvas", "Canvas");
}

CanvasEditor::CanvasEditor(Ref<CanvasQ> doc, QWidget*parent) : QWidget(parent), EditorQ(doc), m_canvas(doc)
{
    QHBoxLayout   *slay    = new QHBoxLayout;
    slay -> addWidget( new QLabel("Hello World!"));
    setLayout(slay);
}

CanvasEditor::~CanvasEditor()
{
}

void        CanvasEditor::configure(gluon::MainWindow&) 
{
    // TODO
}

#include "moc_CanvasEditor.cpp"


