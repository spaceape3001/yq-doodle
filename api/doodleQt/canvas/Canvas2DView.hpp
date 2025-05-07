////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/widget/GraphicsView.hpp>

namespace yq::doodle {
    class Canvas2DScene;
    
    class Canvas2DView : public gluon::GraphicsView {
        Q_OBJECT
    public:
        Canvas2DView(Canvas2DScene*, QWidget* parent=nullptr);
        ~Canvas2DView();
        
        Canvas2DScene*          scene() { return m_scene; }
        const Canvas2DScene*    scene() const { return m_scene; }

    private:
        Canvas2DScene* const    m_scene;
    };
}
