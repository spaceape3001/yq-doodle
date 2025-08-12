////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "CanvasView.hpp"
#include <artQt/CanvasScene.hpp>

namespace yq::art {
    CanvasView::CanvasView(CanvasScene*sc, QWidget* parent) : ViewQ(sc, parent)
    {
    }
    
    CanvasView::~CanvasView()
    {
    }
}

#include "moc_CanvasView.cpp"
