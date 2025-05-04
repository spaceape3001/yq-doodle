////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "DrawingWindow.hpp"
#include "DrawingScene.hpp"
#include "DrawingView.hpp"
#include <gluon/layout/BorderLayout.hpp>
#include <gluon/model/StandardGridTickModel.hpp>
#include <gluon/widget/DrawRuler.hpp>

namespace yq::doodle {
    DrawingWindow::DrawingWindow(ProjectQ&prj, ID id, QWidget*parent) : gluon::SubWindow(parent), m_project(prj), m_id(id) 
    {
        m_scene         = new DrawingScene(prj, id, this);
        m_view          = new DrawingView(m_scene);
        
        connect(m_view, &DrawingView::mouseAt, this, &DrawingWindow::mouseAt);
        
        m_horz.ticks    = new gluon::StandardGridTickModel;
        m_horz.ruler    = new gluon::DrawRuler(Qt::Horizontal);
        m_horz.ruler -> setModel(m_horz.ticks);

        m_vert.ticks    = new gluon::StandardGridTickModel;
        m_vert.ruler    = new gluon::DrawRuler(Qt::Vertical);
        m_vert.ruler -> setModel(m_vert.ticks);
        
        //  toolbar panel (north)
        //  shape panel (west)
        
        gluon::BorderLayout*    layout = new gluon::BorderLayout;
        setLayout(layout);

        layout -> addWidget(m_view, gluon::BorderLayout::Center);
        layout -> addWidget(m_vert.ruler, gluon::BorderLayout::East);
        layout -> addWidget(m_horz.ruler, gluon::BorderLayout::South);
        
        setWindowTitle(tr("Some Drawing"));
    }
    
    DrawingWindow::~DrawingWindow()
    {
    }

    void            DrawingWindow::mouseAt(int x,int y)
    {
        m_horz.ruler -> setMouse(x);
        m_vert.ruler -> setMouse(y);
        
        //  status???
    }
}

#include "moc_DrawingWindow.cpp"
