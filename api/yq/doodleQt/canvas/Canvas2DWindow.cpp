////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Canvas2DWindow.hpp"
#include "Canvas2DScene.hpp"
#include "Canvas2DView.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>

#ifdef emit
    #define emitQt emit
    #undef emit
#endif

#include <yq/doodle/logging.hpp>
#include <yq/gluon/logging.hpp>

#ifdef emitQt
    #define emit emitQt
    #undef emitQt
#endif

namespace yq::doodle {
    Canvas2DWindow::Canvas2DWindow(ProjectQ&prj, ID id, const Config& cfg, QWidget*parent) : 
        Canvas2DWindow(new Canvas2DScene(prj, id), cfg, parent)
    {
        m_view -> featureEnable(gluon::GraphicsView::Feature_MouseWheelZoom);
        m_view -> featureEnable(gluon::GraphicsView::Feature_MouseWheelRotate);
        m_view -> setMouseWheelRotateModifiers(Qt::AltModifier);
    }

    Canvas2DWindow::Canvas2DWindow(Canvas2DScene* scene, const Config& cfg, QWidget*parent) : 
        Canvas2DWindow(new Canvas2DView(scene), cfg, parent)
    {
    }
    
    
    Canvas2DWindow::Canvas2DWindow(Canvas2DView* view, const Config& cfg, QWidget*parent) :
        gluon::SubWindow(parent),
        m_project(view->scene()->projectQ()),
        m_canvas(view->scene()->canvas()),
        m_scene(view->scene()),
        m_view(view)
    {
        QVBoxLayout*    layout  = new QVBoxLayout;
        layout -> addWidget(m_view);
        layout -> setContentsMargins(0,0,0,0);
        setLayout(layout);

        setWindowTitle(tr("Some Canvas"));
    }

    Canvas2DWindow::~Canvas2DWindow()
    {
    }

    void Canvas2DWindow::setEdgePen(QPen v)
    {
        m_scene -> autoDrawEnable(gluon::GraphicsScene::AutoDraw_SceneRect);
        m_scene -> setSceneRectPen(v);
    }
    
    void Canvas2DWindow::setPaperBrush(QBrush v)
    {
        m_scene -> autoDrawEnable(gluon::GraphicsScene::AutoDraw_SceneRect);
        m_scene -> setSceneRectBrush(v);
    }
    
    void Canvas2DWindow::setBackgroundBrush(QBrush v)
    {
        m_scene -> setBackgroundBrush(v);
    }
}

#include "moc_Canvas2DWindow.cpp"
