////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <b3/logging.hpp>
#include <b3/Doc.hpp>
#include <b3/ObjMetaWriter.hpp>
#include <b3/map/MapPainter.hpp>
#include <b3/paint/PaintDevice.hpp>
#include <b3/spatial/Point.hpp>

#include <yq/core/DelayInit.hpp>
#include <yq/shape/Circle2.hpp>
#include <yq/vector/Vector2.hxx>

using namespace yq;
using namespace yq::b3;

namespace {
    void    drawPoint(MapPainter& map, const Point& pt)
    {
        Vector2D    v   = map(pt.global());
//    b3Info << "draw point at " << v;
    
    Pen black{.color={"black"}, .width=2};
    
        map.device().circle(Circle2D(v, 5.), {.pen=&black});
    }


    void    reg_points()
    {
        writer<Point>().delegate(drawPoint);
    }
    YQ_INVOKE(reg_points();)
}

