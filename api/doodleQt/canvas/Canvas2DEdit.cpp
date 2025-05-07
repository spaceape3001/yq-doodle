////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Canvas2DEdit.hpp"
#include "Canvas2DScene.hpp"
#include "Canvas2DView.hpp"

namespace yq::doodle {

    gluon::GraphicsWidget::Config   Canvas2DEdit::config(QObject*par, ProjectQ&prj, ID id)
    {
        Canvas2DScene*  scene   = new Canvas2DScene(prj, id, par);
        Canvas2DView*   view    = new Canvas2DView(scene);
        Config cfg;
        cfg.scene   = scene;
        cfg.view    = view;
        return cfg;
    }
 
    gluon::GraphicsWidget::Config   Canvas2DEdit::config(Canvas2DScene*sc)
    {
        Config cfg;
        cfg.scene   = sc;
        cfg.view    = new Canvas2DView(sc);
        return cfg;
    }
    
    gluon::GraphicsWidget::Config   Canvas2DEdit::config(Canvas2DView* v)
    {
        Config cfg;
        cfg.scene   = v->scene();
        cfg.view    = v;
        return cfg;
    }
   
    Canvas2DEdit::Canvas2DEdit(ProjectQ& prj, ID id, QWidget* parent) : 
        gluon::GraphicsWidget(config(parent, prj, id), parent), 
        m_project(prj), 
        m_canvas(id), 
        m_scene(dynamic_cast<Canvas2DScene*>(gluon::GraphicsWidget::scene())),
        m_view(dynamic_cast<Canvas2DView*>(gluon::GraphicsWidget::view()))
    {
    }
        
    Canvas2DEdit::Canvas2DEdit(Canvas2DScene*sc, QWidget* parent) : 
        gluon::GraphicsWidget(config(sc), parent), 
        m_project(sc->projectQ()), 
        m_canvas(sc->canvas()), 
        m_scene(dynamic_cast<Canvas2DScene*>(gluon::GraphicsWidget::scene())),
        m_view(dynamic_cast<Canvas2DView*>(gluon::GraphicsWidget::view()))
    {
    }
    
    Canvas2DEdit::Canvas2DEdit(Canvas2DView* view, QWidget* parent) : 
        gluon::GraphicsWidget(config(view), parent),
        m_project( view->scene()->projectQ()), 
        m_canvas(view->scene()->canvas()), 
        m_scene(view->scene()),
        m_view(view)
    {
    }
        
    Canvas2DEdit::~Canvas2DEdit()
    {
    }
}

#include "moc_Canvas2DEdit.cpp"

