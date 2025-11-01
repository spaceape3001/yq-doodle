////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Linear.hpp"
#include <yq/b3/logging.hpp>
#include <yq/b3/Parser.hpp>
#include <yq/b3/ObjMetaWriter.hpp>
#include <yq/b3/spatial/Point.hpp>

#include <yq/tensor/Tensor33.hxx>
#include <yq/vector/Vector3.hxx>

YQ_OBJECT_IMPLEMENT(yq::b3::Linear)

namespace yq::b3 {
    Linear::Linear(const Param& p) : Frame(p)
    {
        const auto&  amap   = p.attrs;
        
        assert(p.frame);
        m_origin        = p.frame->point(amap.string("org"));
        if(!m_origin)
            m_origin    = p.frame->point(amap.string("pt"));

        if(!m_origin && (amap.has("x") || amap.has("y") || amap.has("z"))){
            ArgMap nmap    = amap;
            nmap.erase("id");
            m_origin   = new Point({ .attrs=std::move(nmap), .frame=p.frame});
        }
        
    }
    
    Linear::~Linear()
    {
    }
        
    void Linear::calc_points() 
    {
        double  sc  = attrs().real("scale", 1.);

        double  sx  = attrs().real("sx", 1.);
        double  sy  = attrs().real("sy", 1.);
        double  sz  = attrs().real("sz", 1.);

        double  su  = attrs().real("su", 1.);
        double  sv  = attrs().real("sv", 1.);
        double  sw  = attrs().real("sw", 1.);
        
        Tensor33D   xyz = diagonal(sc*sx,sc*sy,sc*sz);
        Tensor33D   uvw = diagonal(su,sv,sw);
        
        unit::Degree    hdg = attrs().angle("h");
        unit::Degree    pit = attrs().angle("p");
        unit::Degree    rll = attrs().angle("r");
        
        Tensor33D   R(HPR, hdg, pit, rll);
        
        m_matrix    = xyz * R * uvw;
        m_inverse   = ::yq::inverse(m_matrix);
        
        m_shift = ZERO;
        if(!is_nan(m_focus)) 
            m_shift     = m_focus;
        if(m_origin)
            m_shift     = frame()->to_local(m_origin->global());
            
        Frame::calc_points();
    }

    Vector3D    Linear::to_frame(const Vector3D&v) const 
    {
        return m_inverse * ( v - m_shift);
    }
    
    Vector3D    Linear::to_parent(const Vector3D&v) const 
    {
        return m_matrix * v + m_shift;
    }
    
    void    Linear::set_focus(const Vector3D&v)
    {
        m_focus = v;
    }
 }

