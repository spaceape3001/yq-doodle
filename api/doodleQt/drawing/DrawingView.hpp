////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QGraphicsView>

namespace yq::doodle {
    class DrawingScene;
    
    class DrawingView : public QGraphicsView {
        Q_OBJECT
    public:
        DrawingView(DrawingScene*, QWidget* parent=nullptr);
        ~DrawingView();
        
    signals:
        void        mouseAt(int, int);
        
    protected:
        void    mouseMoveEvent(QMouseEvent*);
        
    private:
        DrawingScene*   m_scene;
    };
}
