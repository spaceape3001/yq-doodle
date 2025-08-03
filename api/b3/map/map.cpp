////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "map.hpp"

#include <b3/logging.hpp>
#include <b3/Doc.hpp>
#include <b3/map/MapPainter.hpp>
#include <yq/shape/AxBox2.hxx>

namespace yq::b3 {
    bool    render_map(Doc& doc, PaintDevice& dev, const MapParams& mp)
    {
        b3Info  << "Bounds for the document are: " << doc.bounds();
        b3Info  << "Edges for the document are: " << doc.edges();
        b3Info  << "Point count for the document is: " << doc.points(COUNT);

        MapPainter  mapper(dev, doc);
        
        //  TODO... options for areas, details, etc.... (default to the image)....
    
        return false;
    }
}

