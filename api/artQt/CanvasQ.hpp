////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <art/Canvas.hpp>
#include <artQt/DocumentQ.hpp>

namespace yq::art {
    class CanvasQ : public DocumentQ {
        YQ_OBJECTQ_DECLARE(CanvasQ, DocumentQ)
        Q_OBJECT
    public:
        using MyDocument        = Canvas;
        
        static void init_meta();
        CanvasQ(Ref<Canvas>, QObject*parent=nullptr);
        CanvasQ(QObject*parent=nullptr);
        ~CanvasQ();
        
    private:
        Ref<Canvas>     m_canvas;
    };
}
