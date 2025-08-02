////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <b3/util/types.hpp>
#include <yq/container/Stack.hpp>

namespace yq::b3 {
    class PaintDevice;
    
    class Painter {
    public:

        const Brush&        brush() const { return m_state.brush; }
        PaintDevice&        device() { return m_paint; }
        const Font&         font() const { return m_state.font; }
        
        const Pen&          pen() const { return m_state.pen; }
    
        //! Restores to a prior state
        //! \note If stack is empty, will not restore to nothing
        void                restore();

        void                set_brush(const Brush&);
        void                set_pen(const Pen&);
        void                set_font(const Font&);

        //! Saves the current state
        void                stash();
        
        
    protected:
        struct State {
            Brush           brush;
            Font            font;
            Pen             pen;
        };

        Painter(PaintDevice&);
        ~Painter();

        PaintDevice&    m_paint;
        Stack<State>    m_states;
        State           m_state;
    };
}
