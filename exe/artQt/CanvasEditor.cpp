////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/art/logging.hpp>

#include "CanvasEditor.hpp"
#include <yq/artQt/canvas/CanvasScene.hpp>
#include <yq/artQt/canvas/CanvasView.hpp>
#include <yq/artQt/kit/EditorQMetaWriter.hpp>
#include <yq/artQt/kit/ToolBarQ.hpp>
#include <QHBoxLayout>
#include <QToolButton>

YQ_EDITORQ_IMPLEMENT(CanvasEditor)

void CanvasEditor::init_meta()
{   
    auto w = writer<CanvasEditor>();
    w.description("Canvas Editor");
    w.menu("canvas", "Canvas");
}

CanvasEditor::CanvasEditor(Ref<CanvasQ> doc, QWidget*parent) : 
    GraphicsQ(new CanvasView(new CanvasScene(doc)), parent),
    EditorQ(doc)
{
    m_scene     = dynamic_cast<CanvasScene*>(GraphicsQ::scene());
    m_view      = dynamic_cast<CanvasView*>(GraphicsQ::view());

    ToolBarQ*   tbar  = new ToolBarQ;
    QToolButton*tb      = new QToolButton;
    tb -> setText("Tools");
    tbar -> addWidget(tb);
    
    addTop(tbar);
}

CanvasEditor::~CanvasEditor()
{
}

void        CanvasEditor::configure(gluon::MainWindow&) 
{
    // TODO
    artInfo << "CanvasEditor::configure(...)";
}

#include "moc_CanvasEditor.cpp"


