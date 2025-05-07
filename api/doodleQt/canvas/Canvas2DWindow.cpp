////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Canvas2DWindow.hpp"
#include "Canvas2DScene.hpp"
#include "Canvas2DView.hpp"
#include "Canvas2DEdit.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>

#ifdef emit
    #define emitQt emit
    #undef emit
#endif

#include <doodle/logging.hpp>
#include <gluon/logging.hpp>

#ifdef emitQt
    #define emit emitQt
    #undef emitQt
#endif

namespace yq::doodle {
    Canvas2DWindow::Canvas2DWindow(ProjectQ&prj, ID id, const Config& cfg, QWidget*parent) : 
        Canvas2DWindow(new Canvas2DEdit(prj, id), cfg, parent)
    {
    }

    Canvas2DWindow::Canvas2DWindow(Canvas2DEdit*edit, const Config& cfg, QWidget*parent) : 
        gluon::SubWindow(parent), 
        m_edit(edit),
        m_project(edit->projectQ()),
        m_canvas(edit->canvas())
    {
        QVBoxLayout*    layout  = new QVBoxLayout;
        layout -> addWidget(m_edit);
        layout -> setContentsMargins(0,0,0,0);
        setLayout(layout);

        setWindowTitle(tr("Some Canvas"));
    }
    
    
    Canvas2DWindow::~Canvas2DWindow()
    {
    }
}

#include "moc_Canvas2DWindow.cpp"
