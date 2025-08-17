////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <artQt/canvas/CanvasQ.hpp>
#include <artQt/kit/EditorQ.hpp>
#include <artQt/kit/GraphicsQ.hpp>

namespace yq::art {
    class SceneQ;
    class ViewQ;
    class CanvasScene;
    class CanvasView;
}


using namespace yq;
using namespace yq::art;

class CanvasEditor : public GraphicsQ, public EditorQ {
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
    
    CanvasScene*        scene() { return m_scene; }
    const CanvasScene*  scene() const { return m_scene; }
    CanvasView*         view() { return m_view; }
    const CanvasView*   view() const { return m_view; }

private:
    Ref<CanvasQ>    m_canvas;
    CanvasScene*    m_scene = nullptr;
    CanvasView*     m_view  = nullptr;
};


