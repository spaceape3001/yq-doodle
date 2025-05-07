////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/app/SubWindow.hpp>
#include <yq/core/Ref.hpp>
#include <doodle/bit/ID.hpp>

class QLabel;

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
        
    private:
    
        Canvas2DEdit* const m_edit;
        ProjectQ&           m_project;
        const ID            m_canvas;
        
        //  Eventually have a shapes panel, a toolbar, etc.... here
    };
}
