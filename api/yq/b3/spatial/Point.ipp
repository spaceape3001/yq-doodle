////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Point.hpp"
#include <b3/ObjMetaWriter.hpp>
#include <b3/Doc.hpp>

YQ_OBJECT_IMPLEMENT(yq::b3::Point)

namespace yq::b3 {

    static std::string_view     defPointType(double y, double z)
    {
        if(is_nan(y))
            return "1d";
        else if(is_nan(z))
            return "2d";
        else    
            return "3d";
    }

    bool    Point::_use()
    {
        auto& amap  = attrs();
    
        std::string     use = amap.string("use");
        if(use.empty())
            return false;
        Point* u    = frame()->point(use);
        if(!u)
            return false;
        m_type          = u->type();
        m_define        = u->define();
        if(amap.has("x"))
            m_define.x   = amap.length("x");
        if(amap.has("y"))
            m_define.y   = amap.length("y");
        if(amap.has("z"))
            m_define.z   = amap.length("z");
        if(amap.has("pm"))
            m_type    = decode_point_type(amap.string("pm"));
        return true;
    }

    bool    Point::_map()
    {
        auto& amap  = attrs();
        if(!(amap.has("x") || amap.has("y") || amap.has("z")))
            return false;
    
        m_define.x       = amap.length("x",0.);
        m_define.y       = amap.length("y",NAN);
        m_define.z       = amap.length("z",NAN);

        m_type          = decode_point_type(amap.string("pm", defPointType(m_define.y,m_define.z)));
        if(is_nan(m_define.y))
            m_define.y  = 0.;
        if(is_nan(m_define.z))
            m_define.z  = 0.;
        return true;
    }
    
    bool    Point::_list()
    {
        auto& alist  = args();
        switch(alist.size()){
        case 1:
            m_type      = PointType::D1;
            m_define.x  = alist.length(0, 0.);
            m_define.y  = 0.;
            m_define.z  = 0.;
            break;
        case 2:
            m_type      = PointType::D2;
            m_define.x  = alist.length(0, 0.);
            m_define.y  = alist.length(1, 0.);
            m_define.z  = 0.;
            break;
        case 3:
            m_type      = PointType::D3;
            m_define.x  = alist.length(0, 0.);
            m_define.y  = alist.length(1, 0.);
            m_define.z  = alist.length(2, 0.);
            break;
        case 4:
            m_type      = decode_point_type(alist.value(2));
            m_define.x  = alist.length(0, 0.);
            m_define.y  = alist.length(1, 0.);
            m_define.z  = alist.length(3, 0.);
            break;
        default:
            return false;
        }
        return true;
    }

    Point::Point(const Param& p) : Obj(p)
    {
        assert(p.frame);
        
        _use() || _map() || _list();
        if(doc())
            doc() -> m_points << this;
    }
    
    Point::Point(const Vector2D&v, const Param&p) : Obj(p), m_type(PointType::D2), m_define(v.x, v.y, 0.)
    {
        if(doc())
            doc() -> m_points << this;
    }
    
    Point::Point(const Vector3D&v, const Param&p) : Obj(p), m_type(PointType::D3), m_define(v)
    {
        if(doc())
            doc() -> m_points << this;
    }
    
    Point::~Point()
    {
    }
    
    void Point::calc_points() 
    {
        switch(m_type){
        case PointType::D2:
            m_global    = to_global_msl({ m_define.x, m_define.y }, 0. );
            break;
        case PointType::D3:
            m_global    = to_global(m_define);
            break;
        case PointType::AGL:
            m_global    = to_global_agl({m_define.x, m_define.y}, m_define.z );
            break;
        case PointType::MSL:
            m_global    = to_global_msl({m_define.x, m_define.y}, m_define.z );
            break;
        default:
            m_global    = ZERO;
        }
        Obj::calc_points();
    }
}

