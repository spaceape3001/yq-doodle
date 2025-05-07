////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QWidget>
#include <gluon/widget/GraphicsWidget.hpp>
#include <doodle/bit/ID.hpp>

namespace yq::doodle {
    class Canvas2DScene;
    class Canvas2DView;
    class ProjectQ;
    
    //! Combined view/scene with scroll bars & rulers
    class Canvas2DEdit : public gluon::GraphicsWidget {
        Q_OBJECT
    public:
    
        Canvas2DEdit(ProjectQ&, ID, QWidget* parent=nullptr);
        Canvas2DEdit(Canvas2DScene*, QWidget* parent=nullptr);
        Canvas2DEdit(Canvas2DView*, QWidget* parent=nullptr);
        ~Canvas2DEdit();
        
        Canvas2DScene*          scene() { return m_scene; }
        const Canvas2DScene*    scene() const { return m_scene; }
        
        Canvas2DView*           view() { return m_view; }
        const Canvas2DView*     view() const { return m_view; }
        
        ID                      canvas() const { return m_canvas; }
        ProjectQ&               projectQ() { return m_project; }
        const ProjectQ&         projectQ() const { return m_project; }

    private:
        
        ProjectQ&               m_project;
        const ID                m_canvas;
        Canvas2DScene* const    m_scene;
        Canvas2DView* const     m_view;
        
        static Config   config(QObject*, ProjectQ&, ID);
        static Config   config(Canvas2DScene*);
        static Config   config(Canvas2DView*);
    };
}
