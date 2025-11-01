////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/gluon/graphics/GraphicsScene.hpp>
#include <yq/doodle/bit/ID.hpp>
#include <yq/core/Ref.hpp>

namespace yq::doodle {
    class ProjectQ;

    class Canvas2DScene : public gluon::GraphicsScene {
        Q_OBJECT
    public:
        Canvas2DScene(ProjectQ&, ID, QObject* parent=nullptr);
        ~Canvas2DScene();
        
        ID                  canvas() const { return m_canvas; }
        ProjectQ&           projectQ() { return m_project; }
        const ProjectQ&     projectQ() const { return m_project; }
        
    protected:
        ProjectQ&   m_project;
        const ID    m_canvas;
    };
}

