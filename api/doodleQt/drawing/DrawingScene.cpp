////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "DrawingScene.hpp"

namespace yq::doodle {
    DrawingScene::DrawingScene(ProjectQ& project, ID draw, QObject* parent) : 
        QGraphicsScene(parent), m_project(project), m_drawing(draw)
    {
    }
    
    DrawingScene::~DrawingScene()
    {
    }
}

#include "moc_DrawingScene.cpp"
