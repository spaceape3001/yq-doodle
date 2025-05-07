////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodleQt/canvas/Canvas2DWindow.hpp>

namespace yq::doodle {
    //! 2D Drawing
    class Drawing2DWindow : public Canvas2DWindow {
        Q_OBJECT
    public:
        Drawing2DWindow(ProjectQ&, ID, QWidget*parent=nullptr);
        ~Drawing2DWindow();
    };
}
