////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "CanvasScene.hpp"

namespace yq::art {
    CanvasScene::CanvasScene(Ref<CanvasQ> ca, QObject*parent) : SceneQ(parent), m_canvas(ca)
    {
    }
    
    CanvasScene::~CanvasScene()
    {
    }
}

#include "moc_CanvasScene.cpp"

