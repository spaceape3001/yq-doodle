////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QWidget>
#include <variant>

class QHBoxLayout;
class QVBoxLayout;
class QLayout;

namespace yq::art {
    class SceneQ;
    class ToolBarQ;
    class ViewQ;
    
    class GraphicsQ : public QWidget {
        Q_OBJECT
    public:
    
        GraphicsQ(QWidget* parent=nullptr);
        GraphicsQ(SceneQ*, QWidget* parent=nullptr);
        GraphicsQ(ViewQ*, QWidget* parent=nullptr);
        ~GraphicsQ();
        
        //! Adds something left of the view
        void            addLeft(QWidget*);
        void            addLeft(QLayout*);
        
        //! Adds something above the view
        void            addTop(QWidget*);
        void            addTop(QLayout*);

        //! Adds something right of the view
        void            addRight(QWidget*);
        void            addRight(QLayout*);

        //! Adds something below the view
        void            addBottom(QWidget*);
        void            addBottom(QLayout*);
        
        SceneQ*         scene() { return m_scene; }
        const SceneQ*   scene() const { return m_scene; }
        
        ViewQ*          view() { return m_view; }
        const ViewQ*    view() const { return m_view; }
        
    signals:
        //! Called when widgets are added as a chance to bind in signals
        void            widgetAdded(QWidget*);

    private:
    
        void            _add(QWidget*);
        void            _add(QLayout*);
        
        QHBoxLayout*                m_layHorz   = nullptr;
        QVBoxLayout*                m_layVert   = nullptr;
        SceneQ*                     m_scene     = nullptr;
        std::vector<ToolBarQ*>      m_toolbars;
        ViewQ*                      m_view      = nullptr;
    };
}
