////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "MapPainter.hpp"
#include <b3/Doc.hpp>
#include <b3/paint/PaintDevice.hpp>
#include <b3/spatial/Point.hpp>
#include <yq/meta/UntypeMetaWriter.hpp>
#include <yq/shape/Circle2.hpp>
#include <yq/shape/Segment2.hpp>


#include <yq/tensor/Tensor24.hxx>
//#include <yq/vector/Spinor2.hxx>
#include <yq/vector/Vector2.hxx>
#include <yq/vector/Vector3.hxx>

YQ_UNTYPE_IMPLEMENT(yq::b3::MapPainter)

namespace yq::b3 {
    MapPainter::MapPainter(PaintDevice& paint, const Frame& frame) : Painter(paint),
        m_doc(*frame.document()), m_frame(frame)
    {
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

    Vector2D MapPainter::map(const Point& p) const
    {
        return map(p.global());
    }
    
    Vector2D MapPainter::map(const Vector2D& v) const
    {
        return map(Vector3D(v.x, v.y, 0.));
    }
    
    Vector2D MapPainter::map(const Vector3D& v) const
    {
        Vector3D    f   = m_frame.to_frame(v);
        return m_transform * Vector4D(f.x,f.y,f.z,1.);
    }
    
    Vector2D MapPainter::map(const vertex_t&v) const
    {
        if(auto p = std::get_if<Vector2D>(&v))
            return map(*p);
        if(auto p = std::get_if<Vector3D>(&v))
            return map(*p);
        if(auto p = std::get_if<const Point*>(&v))
            return map((*p)->global());
        return NAN;
    }

    
    //void    MapPainter::set_origin(const Vector3D&);
    //void    MapPainter::set_shift(const Vector3D&);
    //void    MapPainter::set_rotation(const Spinor2D&);
    //void    MapPainter::set_projection(const Tensor23&);
    
    
}
