////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/artQt/kit/SceneQ.hpp>
#include <yq/artQt/canvas/CanvasQ.hpp>

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
