////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GraphicsQ.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "SceneQ.hpp"
#include "ViewQ.hpp"
#include "ToolBarQ.hpp"

namespace yq::art {
    GraphicsQ::GraphicsQ(QWidget* parent) : GraphicsQ(new SceneQ(this), parent)
    {
    }
    
    GraphicsQ::GraphicsQ(SceneQ* sc, QWidget* parent) : GraphicsQ(new ViewQ(sc), parent)
    {
    }
    
    GraphicsQ::GraphicsQ(ViewQ* vi, QWidget* parent) : QWidget(parent), m_view(vi)
    {
        assert(m_view);
        if(m_view)
            m_scene = m_view -> scene();
        assert(m_scene);
        
        m_layVert = new QVBoxLayout;
        m_layVert -> setContentsMargins({});
        
        if(m_view)
            m_layVert -> addWidget(vi);
        
        m_layHorz   = new QHBoxLayout;
        m_layHorz -> setContentsMargins({});
        m_layHorz -> addLayout(m_layVert);

        setLayout(m_layHorz);
    }

    GraphicsQ::~GraphicsQ()
    {
    }

    void    GraphicsQ::_add(QLayout* layout)
    {
        for(int i=0;i<layout->count();++i){
            QLayoutItem*    item    = layout->itemAt(i);
            if(!item)
                continue;
            if(QWidget* wid = item->widget())
                _add(wid);
            if(QLayout* lay = item->layout())
                _add(lay);
        }
    }

    void    GraphicsQ::_add(QWidget*widget)
    {
        ToolBarQ*   tb  = dynamic_cast<ToolBarQ*>(widget);
        if(tb)
            m_toolbars.push_back(tb);
        widgetAdded(widget);
    }

    void    GraphicsQ::addBottom(QLayout* layout)
    {
        assert(layout);
        if(!layout)
            return;
        m_layVert -> addLayout(layout);
        _add(layout);
    }

    void    GraphicsQ::addBottom(QWidget* widget)
    {
        assert(widget);
        if(!widget)
            return ;
        m_layHorz -> insertWidget(0, widget);
        _add(widget);
    }
    
    void    GraphicsQ::addLeft(QLayout*layout)
    {
        assert(layout);
        if(!layout)
            return ;
        m_layHorz -> insertLayout(0, layout);
        _add(layout);
    }
    
    void    GraphicsQ::addLeft(QWidget*widget)
    {
        assert(widget);
        if(!widget)
            return ;
        m_layHorz -> insertWidget(0, widget);
        _add(widget);
    }

    void    GraphicsQ::addRight(QLayout* layout)
    {
        assert(layout);
        if(!layout)
            return;
        m_layHorz -> addLayout(layout);
        _add(layout);
    }

    void    GraphicsQ::addRight(QWidget* widget)
    {
        assert(widget);
        if(!widget)
            return ;
        m_layHorz -> addWidget(widget);
        _add(widget);
    }
    
    void    GraphicsQ::addTop(QLayout* layout)
    {
        assert(layout);
        if(!layout)
            return ;
        m_layVert -> insertLayout(0, layout);
        _add(layout);
    }
    
    void    GraphicsQ::addTop(QWidget* widget)
    {
        assert(widget);
        if(!widget)
            return ;
        m_layVert -> insertWidget(0, widget);
        _add(widget);
    }
}


#include "moc_GraphicsQ.cpp"

