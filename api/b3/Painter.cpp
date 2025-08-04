////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Painter.hpp"

#include <b3/paint/PaintDevice.hpp>

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
        m_proj2 = ZERO;
        m_proj3 = ZERO;
    }
    
    Painter::~Painter()
    {
    }

    Vector2D  Painter::operator()(const Vector2D&v) const
    {
        return project(v);
    }

    Vector2D  Painter::operator()(const Vector3D&v) const
    {
        return project(v);
    }

    void    Painter::restore()
    {
        if(!m_states.empty())
            m_state = m_states.pop();
    }

    Vector2D  Painter::project(const Vector2D&v) const
    {
        return m_proj2 * Vector3D(v.x, v.y, 1.);
    }

    Vector2D  Painter::project(const Vector3D&v) const
    {
        return m_proj3 * Vector4D(v.x, v.y, v.z, 1.);
    }


    void    Painter::set_proj2(const AxBox2D& bounds, const Projection2DOpts& opts)
    {
        Size2D      sz  = m_paint.size();
        
        Tensor22D   T   = IDENTITY;
        Vector2D    ctr = ZERO;
        
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
        
        ctr             = T * ctr;
            
        m_proj2     = {
            T.xx, T.xy, -ctr.x,
            T.yx, T.yy, -ctr.y
        };

        if(opts.vertflip){
            m_proj2.yx    = -m_proj2.yx;
            m_proj2.yy    = -m_proj2.yy;
            m_proj2.yz    = -m_proj2.yz;
        }
        
        // For now until there's rotation, etc.... (likely in set 3D)
        m_proj3 = Tensor24D(
            m_proj2.xx, m_proj2.xy, 0., m_proj2.xz,
            m_proj2.yx, m_proj2.yy, 0., m_proj2.yz
        );
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
