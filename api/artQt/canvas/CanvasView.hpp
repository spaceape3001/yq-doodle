////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <artQt/kit/ViewQ.hpp>

namespace yq::art {
    class CanvasScene;
    
    class CanvasView : public ViewQ {
        Q_OBJECT
    public:
        CanvasView(CanvasScene*, QWidget* parent=nullptr);
        ~CanvasView();
    };
}

