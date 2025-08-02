////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <b3/keywords.hpp>
#include <b3/util/types.hpp>

#include <yq/units.hpp>
#include <yq/container/Stack.hpp>
#include <yq/meta/MetaBinder.hpp>
#include <yq/tensor/Tensor24.hpp>
#include <yq/typedef/circle2.hpp>
#include <yq/typedef/segment2.hpp>
#include <yq/vector/Vector2.hpp>
#include <yq/vector/Vector3.hpp>
#include <variant>

namespace yq::b3 {
    class Doc;
    class Frame;
    class Point;
    class PaintDevice;

    class MapPainter {
    public:
    
        using vertex_t  = std::variant<Vector2D, Vector3D, const Point*>;
        
        PaintDevice&        device() { return m_paint; }
        
        //! Saves the current state
        void                push();
        
        //! Restores to a prior state
        //! \note If stack is empty, will not restore to nothing
        void                pop();
        
        const Brush&        brush() const { return m_state.brush; }
        const Pen&          pen() const { return m_state.pen; }
        const Font&         font() const { return m_state.font; }
        
        const Doc&          doc() const { return m_doc; }
        const Frame&        frame() const { return m_frame; }
        
        Vector2D            map(const Point&) const;
        Vector2D            map(const Vector2D&) const;
        Vector2D            map(const Vector3D&) const;
        Vector2D            map(const vertex_t&) const;
        
        //! Draws a line using the current pen
        void                draw_line(const vertex_t&, const vertex_t&);
        
        //! Draws a line (allowing overrides)
        void                draw_line(const vertex_t&, const vertex_t&, const Pen&);
        
        //! Draws a line using the current pen
        void                draw_line(asis_k, const Vector2D&, const Vector2D&);
        void                draw_line(asis_k, const Vector2D&, const Vector2D&, const Pen&);

        void                draw_line(asis_k, const Segment2D&);
        void                draw_line(asis_k, const Segment2D&, const Pen&);

        void                set_brush(const Brush&);
        void                set_pen(const Pen&);
        void                set_font(const Font&);
        
        //void                set_origin(const Vector3D&);
        //void                set_shift(const Vector3D&);
        //void                set_rotation(const Spinor2D&);
        //void                set_projection(const Tensor23&);
        

        MapPainter(PaintDevice&, const Frame& frame);
        ~MapPainter();
        
    protected:
        
        const Doc&      m_doc;
        const Frame&    m_frame;
        PaintDevice&    m_paint;
        
    private:
    
        struct State {
            Brush           brush;
            Font            font;
            Pen             pen;
        };

        Stack<State>    m_states;
        State           m_state;
        Tensor24D       m_transform = IDENTITY; // composition TBD

        MapPainter(Frame&&) = delete;
        MapPainter(const MapPainter&) = delete;
        MapPainter(MapPainter&&) = delete;
        MapPainter& operator=(const MapPainter&) = delete;
        MapPainter& operator=(MapPainter&&) = delete;
    
    };
}

YQ_UNTYPE_DECLARE(yq::b3::MapPainter)
