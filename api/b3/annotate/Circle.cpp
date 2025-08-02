////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Circle.hpp"
#include <b3/ObjMetaWriter.hpp>

YQ_OBJECT_IMPLEMENT(yq::b3::Circle)

namespace yq::b3 {
    Circle::Circle(const Param& p) : Obj(p)
    {
        m_circle.center.x   = p.args.length(0);
        m_circle.center.y   = p.args.length(1);
        m_circle.radius     = p.args.length(2);
    }
    
    Circle::~Circle()
    {
    }
}


