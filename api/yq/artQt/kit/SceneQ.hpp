////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/graphics/GraphicsScene.hpp>
#include <artQt/DocumentQ.hpp>

namespace yq::art {
    class SceneQ : public gluon::GraphicsScene {
        Q_OBJECT
    public:
        SceneQ(QObject*parent=nullptr);
        virtual ~SceneQ();
    private:
        // vector of documents?
    };
}
