////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <yq/art/doc/Canvas.hpp>
#include <yq/artQt/DocumentQ.hpp>

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
        
        Canvas*         canvas() { return m_canvas.ptr(); }
        const Canvas*   canvas() const { return m_canvas.ptr(); }
        
    signals:
        void        boundsChanged();
        
    private:
        Ref<Canvas>     m_canvas;
    };
}
