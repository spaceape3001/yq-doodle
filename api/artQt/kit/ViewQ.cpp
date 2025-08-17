////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "ViewQ.hpp"
#include <artQt/kit/SceneQ.hpp>

namespace yq::art {
    ViewQ::ViewQ(SceneQ*sc, QWidget* parent) : gluon::GraphicsView(sc, parent), m_scene(sc)
    {
        setScene(sc);
    }
    
    ViewQ::~ViewQ()
    {
    }
}

#include "moc_ViewQ.cpp"
