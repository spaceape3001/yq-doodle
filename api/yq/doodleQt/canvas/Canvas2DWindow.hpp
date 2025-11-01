////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/app/SubWindow.hpp>
#include <yq/core/Ref.hpp>
#include <doodle/bit/ID.hpp>

class QBrush;
class QPen;

namespace yq::doodle {
    class Canvas2DScene;
    class Canvas2DView;
    class ProjectQ;
        
    //! 2D Canvas (Which... we'll subclass for drawing/diagrams/etc)
    class Canvas2DWindow : public gluon::SubWindow {
        Q_OBJECT
    public:
    
        struct Config {
            // probably some panelling/layouts garnish around the edit
        };
    
        Canvas2DWindow(ProjectQ&, ID,  const Config& cfg={}, QWidget*parent=nullptr);
        Canvas2DWindow(Canvas2DScene*, const Config& cfg={}, QWidget*parent=nullptr);
        Canvas2DWindow(Canvas2DView*,  const Config& cfg={}, QWidget*parent=nullptr);
        ~Canvas2DWindow();
        
        ID                      canvas() const { return m_canvas; }
        ProjectQ&               projectQ() { return m_project; }
        const ProjectQ&         projectQ() const { return m_project; }

        void                    setEdgePen(QPen);
        void                    setPaperBrush(QBrush);
        void                    setBackgroundBrush(QBrush);

        Canvas2DScene*          scene() { return m_scene; }
        const Canvas2DScene*    scene() const { return m_scene; }
        
        Canvas2DView*           view() { return m_view; }
        const Canvas2DView*     view() const { return m_view; }
        
    protected:
        ProjectQ&               m_project;
        const ID                m_canvas;
        
    private:
        Canvas2DScene* const    m_scene;
        Canvas2DView* const     m_view;

        //  Eventually have a shapes panel, a toolbar, etc.... here
    };
}
