////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "CanvasView.hpp"
#include <yq/artQt/canvas/CanvasScene.hpp>

namespace yq::art {
    CanvasView::CanvasView(CanvasScene*sc, QWidget* parent) : ViewQ(sc, parent), m_scene(sc)
    {
        assert(m_scene);
    }
    
    CanvasView::~CanvasView()
    {
    }
}

#include "moc_CanvasView.cpp"
