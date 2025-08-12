////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/graphics/GraphicsView.hpp>

namespace yq::art {
    class SceneQ;
    
    class ViewQ : public gluon::GraphicsView {
        Q_OBJECT
    public:
        ViewQ(SceneQ*, QWidget* parent=nullptr);
        ~ViewQ();
        
    private:
        SceneQ*     m_scene;
    };
}
