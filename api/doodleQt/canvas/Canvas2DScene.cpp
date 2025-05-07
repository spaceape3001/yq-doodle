////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Canvas2DScene.hpp"

namespace yq::doodle {
    Canvas2DScene::Canvas2DScene(ProjectQ& project, ID draw, QObject* parent) : 
        gluon::GraphicsScene(parent), m_project(project), m_canvas(draw)
    {
        setSceneRect(0,0,1000,1000);
    }
    
    Canvas2DScene::~Canvas2DScene()
    {
    }
}

#include "moc_Canvas2DScene.cpp"
