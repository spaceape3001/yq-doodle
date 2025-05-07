////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Drawing2DWindow.hpp"

namespace yq::doodle {
    Drawing2DWindow::Drawing2DWindow(ProjectQ&prj, ID id, QWidget*parent) : 
        Canvas2DWindow(prj, id, {}, parent)
    {
        setWindowTitle(tr("Some Drawing"));
        resize(1920, 1080);
    }
    
    Drawing2DWindow::~Drawing2DWindow()
    {
    }
}

#include "moc_Drawing2DWindow.cpp"
