////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/app/SubWindow.hpp>
#include <yq/core/Ref.hpp>
#include <doodle/bit/ID.hpp>

namespace yq::gluon {
    class DrawRuler;
    class StandardGridTickModel;
}

namespace yq::doodle {
    class DrawingScene;
    class DrawingView;
    class ProjectQ;
    
    class DrawingWindow : public gluon::SubWindow {
        Q_OBJECT
    public:
        DrawingWindow(ProjectQ&, ID, QWidget*parent=nullptr);
        ~DrawingWindow();
        
        
    private slots:
        void            mouseAt(int,int);
    private:
        using ticks_t   = gluon::StandardGridTickModel;
    
        ProjectQ&       m_project;
        ID              m_id;
        DrawingScene*   m_scene = nullptr;
        DrawingView*    m_view  = nullptr;
        
        struct {
            Ref<gluon::StandardGridTickModel>   ticks;
            gluon::DrawRuler*                   ruler = nullptr;
        } m_horz, m_vert;
    };
}
