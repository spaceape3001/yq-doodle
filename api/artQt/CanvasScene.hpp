////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <artQt/SceneQ.hpp>
#include <artQt/CanvasQ.hpp>

namespace yq::art {
    class CanvasScene : public SceneQ {
        Q_OBJECT
    public:
        CanvasScene(Ref<CanvasQ>, QObject*parent=nullptr);
        ~CanvasScene();
        
    private:
        Ref<CanvasQ>    m_canvas;
    };
}
