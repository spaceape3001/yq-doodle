////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <b3/keywords.hpp>
#include <b3/Painter.hpp>
#include <b3/util/types.hpp>

#include <yq/units.hpp>
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

    class MapPainter : public Painter {
    public:
    
        using vertex_t  = std::variant<Vector2D, Vector3D, const Point*>;

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

        //void                set_origin(const Vector3D&);
        //void                set_shift(const Vector3D&);
        //void                set_rotation(const Spinor2D&);
        //void                set_projection(const Tensor23&);
        

        MapPainter(PaintDevice&, const Frame& frame);
        ~MapPainter();
    
    protected:         
    
        const Doc&      m_doc;
        const Frame&    m_frame;

    private:
    
        Tensor24D       m_transform = IDENTITY; // composition TBD
    
    };
}

YQ_UNTYPE_DECLARE(yq::b3::MapPainter)
