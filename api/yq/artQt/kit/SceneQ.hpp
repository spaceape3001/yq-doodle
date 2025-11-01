////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/gluon/graphics/GraphicsScene.hpp>
#include <yq/artQt/DocumentQ.hpp>

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
