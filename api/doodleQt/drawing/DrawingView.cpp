////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "DrawingView.hpp"
#include "DrawingScene.hpp"
#include <QMouseEvent>

namespace yq::doodle {
    DrawingView::DrawingView(DrawingScene* scene, QWidget* parent) : QGraphicsView(scene, parent)
    {
        setMouseTracking(true);
    }
    
    DrawingView::~DrawingView()
    {
    }

    void    DrawingView::mouseMoveEvent(QMouseEvent* evt)
    {
        emit mouseAt(evt->position().x(), evt->position().y());
        QGraphicsView::mouseMoveEvent(evt);
    }
}


#include "moc_DrawingView.cpp"


