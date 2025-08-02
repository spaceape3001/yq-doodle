////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Painter.hpp"

namespace yq::b3 {
    Painter::Painter(PaintDevice& paint) : 
        m_paint(paint)
    {
    }
    
    Painter::~Painter()
    {
    }

    void    Painter::restore()
    {
        if(!m_states.empty())
            m_state = m_states.pop();
    }

    void    Painter::set_brush(const Brush&v)
    {
        m_state.brush   = v;
    }
    
    void    Painter::set_font(const Font&v)
    {
        m_state.font    = v;
    }
    
    void    Painter::set_pen(const Pen& v)
    {
        m_state.pen     = v;
    }
    
    void    Painter::stash()
    {
        m_states.push_back(m_state);
    }
}
