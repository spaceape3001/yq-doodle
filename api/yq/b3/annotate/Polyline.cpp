////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Polyline.hpp"
#include <yq/b3/ObjMetaWriter.hpp>

YQ_OBJECT_IMPLEMENT(yq::b3::Polyline)

namespace yq::b3 {
    Polyline::Polyline(const Param&p, bool cl) : 
        Frame(p), PointLine(p.frame, p.args), m_closed(cl)
    {
    }
    
    Polyline::~Polyline()
    {
    }
}
