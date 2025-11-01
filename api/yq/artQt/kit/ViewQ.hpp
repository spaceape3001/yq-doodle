////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/gluon/graphics/GraphicsView.hpp>

namespace yq::art {
    class SceneQ;
    
    class ViewQ : public gluon::GraphicsView {
        Q_OBJECT
    public:
        ViewQ(SceneQ*, QWidget* parent=nullptr);
        ~ViewQ();
        
        SceneQ*         scene() { return m_scene; }
        const SceneQ*   scene() const { return m_scene; }
        
    private:
        SceneQ*     m_scene;
    };
}
