////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QGraphicsScene>
#include <doodle/bit/ID.hpp>

namespace yq::doodle {
    class ProjectQ;

    class DrawingScene : public QGraphicsScene {
        Q_OBJECT
    public:
        DrawingScene(ProjectQ&, ID, QObject* parent=nullptr);
        ~DrawingScene();
        
    private:
        ProjectQ&       m_project;
        ID              m_drawing;
    };
}

