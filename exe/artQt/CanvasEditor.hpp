////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <artQt/canvas/CanvasQ.hpp>
#include <artQt/EditorQ.hpp>
#include <QWidget>

namespace yq::art {
    class SceneQ;
    class ViewQ;
    class CanvasScene;
    class CanvasView;
}


using namespace yq;
using namespace yq::art;

class CanvasEditor : public QWidget, public EditorQ {
    Q_OBJECT
    YQ_EDITORQ_DECLARE(CanvasEditor, EditorQ)
public:

    using MyDocQ        = CanvasQ;
    
    static void init_meta();
    CanvasEditor(Ref<CanvasQ>, QWidget*parent=nullptr);
    ~CanvasEditor();
    
    CanvasQ*            canvas() { return m_canvas.ptr(); }
    const CanvasQ*      canvas() const { return m_canvas.ptr(); }
    
    virtual void        configure(gluon::MainWindow&) override;

private:
    Ref<CanvasQ>        m_canvas;
};


