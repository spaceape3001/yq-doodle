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
#include <yq/shape/AxBox2.hpp>
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
    
    #ifdef NAN
        #undef NAN
    #endif
    
    struct MapPainterOptions {
        //! Heading for the top edge
        unit::Degree        heading         = NAN;

        //! Resizing policy
        AspectRatioPolicy   resizing        = AspectRatioPolicy::Ignore;
    };

    class MapPainter : public Painter {
    public:

        const AxBox2D&      bounds() const { return m_bounds; }

        const Doc&          doc() const { return m_doc; }
        const Frame&        frame() const { return m_frame; }
        
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
        

        MapPainter(PaintDevice&, const Frame& frame, const AxBox2D&, const MapPainterOptions& options={});
        ~MapPainter();
    
    protected:         

        Vector2D  mapper(const Vector3D&v) const override;
    
        const Doc&      m_doc;
        const Frame&    m_frame;
        AxBox2D         m_bounds;
    };
}

YQ_UNTYPE_DECLARE(yq::b3::MapPainter)
