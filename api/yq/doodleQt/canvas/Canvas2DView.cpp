////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Canvas2DView.hpp"
#include "Canvas2DScene.hpp"
#include <QMouseEvent>

namespace yq::doodle {
    Canvas2DView::Canvas2DView(Canvas2DScene* scene, QWidget* parent) : gluon::GraphicsView(scene, parent), m_scene(scene)
    {
    }
    
    Canvas2DView::~Canvas2DView()
    {
    }

#if 0
    void    Canvas2DView::mouseMoveEvent(QMouseEvent* evt)
    {
        emit mouseAt(evt->position().x(), evt->position().y());
        QGraphicsView::mouseMoveEvent(evt);
    }
#endif
}


#include "moc_Canvas2DView.cpp"


