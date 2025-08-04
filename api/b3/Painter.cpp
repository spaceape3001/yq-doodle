////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Painter.hpp"

#include <b3/logging.hpp>
#include <b3/paint/PaintDevice.hpp>
#include <b3/spatial/Point.hpp>

#include <yq/shape/AxBox2.hpp>
#include <yq/tensor/Tensor22.hpp>

#include <yq/shape/AxBox2.hxx>
#include <yq/shape/Size2.hxx>
#include <yq/tensor/Tensor22.hxx>
#include <yq/tensor/Tensor23.hxx>
#include <yq/tensor/Tensor24.hxx>

namespace yq::b3 {
    Painter::Painter(PaintDevice& paint) : 
        m_paint(paint)
    {
        m_proj3 = ZERO;
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
    


    //////////////////////
    /// PAINTING
    
    
    //////////////////////
    /// PROJECTIONS


    Vector2D  Painter::operator()(const Vector2D&v) const
    {
        return map(v);
    }
    
    Vector2D  Painter::operator()(const Vector3D&v) const
    {
        return map(v);
    }
    
    Vector2D  Painter::operator()(const Point&v) const
    {
        return map(v);
    }
    
    Vector2D  Painter::operator()(const vertex_t&v) const
    {
        return map(v);
    }

    Vector2D  Painter::map(const Point& p) const
    {
        return mapper(p.global());
    }

    Vector2D  Painter::map(const Vector2D&v) const
    {
        return mapper({v.x, v.y, 0.});
    }

    Vector2D  Painter::map(const Vector3D&v) const
    {
        return mapper(v);
    }

    Vector2D Painter::map(const vertex_t&v) const
    {
        if(auto p = std::get_if<Vector2D>(&v))
            return map(*p);
        if(auto p = std::get_if<Vector3D>(&v))
            return map(*p);
        if(auto p = std::get_if<const Point*>(&v))
            return map((*p)->global());
        return NAN;
    }
    
    Vector2D  Painter::mapper(const Vector3D&v) const
    {
        return m_proj3 * Vector4D(v.x, v.y, v.z, 1.);
    }

    void    Painter::set_proj2(const AxBox2D& bounds, const Projection2DOpts& opts)
    {
        Size2D      sz  = m_paint.size();
        
        Tensor22D   T       = IDENTITY;
        Vector2D    ctr     = ZERO;
        
        m_vertflip = m_distortion = false;
        
        if(!is_nan(sz) && (any(sz) != 0.)){ // need size to do anything
            if(is_nan(bounds) || (any(bounds.size()) == 0.)){
                //  no bounds, but a size, presume we want it centered
                ctr         = { 0.5*sz.x, 0.5*sz.y };
            } else {
                AxBox2D bb  = bounds.fixed();
                ctr         = bb.center();
                
                Size2D f   = sz.ediv(bb.size());

                switch(opts.resizing){
                case AspectRatioPolicy::Ignore:
                    break;
                case AspectRatioPolicy::Expand:
                    f   = Size2D(ALL, f.cmin());
                    break;
                case AspectRatioPolicy::Shrink:
                    f   = Size2D(ALL, f.cmax());
                    break;
                }
                
                m_distortion  = (f.x != f.y);
                
                T = Tensor22D(
                    f.x, 0.,
                    0., f.y
                );
            } 
        }

        if( !is_nan(opts.heading) && (opts.heading != 0._deg)){
            Tensor22D R( CLOCKWISE, opts.heading );
            T  = R * T; // might be wrong... TBD
        }
        
        if(opts.vertflip){
            T.yx    = -T.yx;
            T.yy    = -T.yy;
            m_vertflip  = true;
        }

        ctr         = inverse(T) * ctr;

        if(!is_nan(sz) && (any(sz) != 0.)){ // need size to do anything
            ctr -= 0.5 * (Vector2D) sz;
        }
            
        // For now until there's rotation, etc.... (likely in set 3D)
        m_proj3 = Tensor24D(
            T.xx, T.xy, 0., -ctr.x,
            T.yx, T.yy, 0., -ctr.y
        );
    }
}
