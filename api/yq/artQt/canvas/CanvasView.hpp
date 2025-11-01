////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <artQt/kit/ViewQ.hpp>
#include <artQt/canvas/CanvasQ.hpp>

namespace yq::art {
    class CanvasScene;
    
    class CanvasView : public ViewQ {
        Q_OBJECT
    public:
        CanvasView(CanvasScene*, QWidget* parent=nullptr);
        ~CanvasView();
        
        CanvasScene*        scene() { return m_scene; }
        const CanvasScene*  scene() const { return m_scene; }
        
    private:
        CanvasScene*    m_scene = nullptr;
    };
}

