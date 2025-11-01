////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "MapPainter.hpp"
#include <yq/b3/Doc.hpp>
#include <yq/b3/paint/PaintDevice.hpp>
#include <yq/b3/spatial/Point.hpp>
#include <yq/meta/UntypeMetaWriter.hpp>
#include <yq/shape/Circle2.hpp>
#include <yq/shape/Segment2.hpp>


#include <yq/shape/AxBox2.hxx>
#include <yq/shape/Size2.hxx>
#include <yq/tensor/Tensor24.hxx>
//#include <yq/vector/Spinor2.hxx>
#include <yq/vector/Vector2.hxx>
#include <yq/vector/Vector3.hxx>

YQ_UNTYPE_IMPLEMENT(yq::b3::MapPainter)

namespace yq::b3 {
    MapPainter::MapPainter(PaintDevice& paint, const Frame& frame, const AxBox2D& bounds, const MapPainterOptions& opts) : Painter(paint),
        m_doc(*frame.document()), m_frame(frame)
    {
        set_proj2(bounds, { .heading=opts.heading, .resizing=opts.resizing });
    }
    
    MapPainter::~MapPainter()
    {
    }
    
    void    MapPainter::draw_line(const vertex_t&a, const vertex_t&b) 
    {
        m_paint.line({map(a), map(b)}, {.pen = &m_state.pen });
    }

    void    MapPainter::draw_line(const vertex_t&a, const vertex_t&b, const Pen&p) 
    {
        m_paint.line({map(a), map(b)}, {.pen = &p });
    }

    void    MapPainter::draw_line(asis_k, const Vector2D&a, const Vector2D&b) 
    {
        m_paint.line({a,b}, {.pen = &m_state.pen });
    }
    
    void    MapPainter::draw_line(asis_k, const Vector2D&a, const Vector2D&b, const Pen& p) 
    {
        m_paint.line({a,b}, {.pen = &p });
    }

    void    MapPainter::draw_line(asis_k, const Segment2D&v)
    {
        m_paint.line(v, {.pen=&m_state.pen});
    }
    
    void    MapPainter::draw_line(asis_k, const Segment2D&v, const Pen&p)
    {
        m_paint.line(v, {.pen=&p});
    }

    Vector2D  MapPainter::mapper(const Vector3D&v) const 
    {
        return Painter::mapper(m_frame.to_frame(v));
    }
    
    //void    MapPainter::set_origin(const Vector3D&);
    //void    MapPainter::set_shift(const Vector3D&);
    //void    MapPainter::set_rotation(const Spinor2D&);
    //void    MapPainter::set_projection(const Tensor23&);
    
    
}
