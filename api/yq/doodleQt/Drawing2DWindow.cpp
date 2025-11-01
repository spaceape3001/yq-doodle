////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Drawing2DWindow.hpp"

#include <QBrush>
#include <QColor>
#include <QPen>

#include <yq/color/colors.hpp>

namespace yq::doodle {
    Drawing2DWindow::Drawing2DWindow(ProjectQ&prj, ID id, QWidget*parent) : 
        Canvas2DWindow(prj, id, {}, parent)
    {
        setWindowTitle(tr("Some Drawing"));
        resize(1920, 1080);
        setEdgePen(QPen(QColor(color::Asparagus), 2));
        setPaperBrush(QColor(color::White));
        setBackgroundBrush(QColor(color::LightGray));
    }
    
    Drawing2DWindow::~Drawing2DWindow()
    {
    }
}

#include "moc_Drawing2DWindow.cpp"
