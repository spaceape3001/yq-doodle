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
    class Canvas2DEdit;
    class ProjectQ;
    
    
    //! 2D Canvas (Which... we'll subclass for drawing/diagrams/etc)
    class Canvas2DWindow : public gluon::SubWindow {
        Q_OBJECT
    public:
    
        struct Config {
            // probably some panelling/layouts garnish around the edit
        };
    
        Canvas2DWindow(ProjectQ&, ID, const Config& cfg={}, QWidget*parent=nullptr);
        Canvas2DWindow(Canvas2DEdit*, const Config& cfg={}, QWidget*parent=nullptr);
        ~Canvas2DWindow();
        
        Canvas2DEdit*           edit() { return m_edit; }
        const Canvas2DEdit*     edit() const { return m_edit; }
        
        ID                      canvas() const { return m_canvas; }
        ProjectQ&               projectQ() { return m_project; }
        const ProjectQ&         projectQ() const { return m_project; }

        void                    setEdgePen(QPen);
        void                    setPaperBrush(QBrush);
        void                    setBackgroundBrush(QBrush);

    protected:
        ProjectQ&           m_project;
        const ID            m_canvas;
        
    private:
        Canvas2DEdit* const m_edit;
        
        //  Eventually have a shapes panel, a toolbar, etc.... here
    };
}
