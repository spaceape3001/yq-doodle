////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "map.hpp"

#include <b3/logging.hpp>
#include <b3/Doc.hpp>
#include <b3/map/MapPainter.hpp>
#include <b3/util/parse.hpp>
#include <b3/paint/PaintDevice.hpp>
#include <yq/shape/AxBox2.hxx>
#include <yq/shape/Size2.hxx>
#include <yq/text/match.hpp>

namespace yq::b3 {
    bool    is_paper(std::string_view k, Size2D& sz)
    {
        return false;
    }

    bool    render_map(Doc& doc, PaintDevice& dev, const MapParams& mp)
    {
        /*
            I'm sure the below can be commonized once a new output is necessary
        */
        AxBox2D     bb  = mp.bounds;
        if(is_nan(bb) || (any(bb.size()) == 0.))
            bb      = doc.bounds();
            
        Size2D size = dev.size();
        
        if(is_nan(size) || (any(size) == 0.))
            size        = bb.size();
            
        if(doc.attrs().has("paper")){
            std::string_view  paper   = doc.attr("paper");
            if(is_paper(paper, size)){
                //  check for orientation
            } else if(!paper.empty()){
                Vector2D    sz  = parse::vector2(paper);
                if(all(sz) != 0.)
                    size    = (Size2D) sz;
            }
        }
            
        
        if(doc.attrs().has("width"))
            size.x      = doc.attrs().real("width", 1024);
        if(doc.attrs().has("height"))
            size.y      = doc.attrs().real("height", 768);
        
        dev.set_size(size);

        unit::Degree        hdg         = mp.heading;
        AspectRatioPolicy   resizing    = AspectRatioPolicy::Ignore;
        
        if(is_nan(hdg))
            hdg             = doc.attrs().angle("heading", NAN);
    
        auto ap             = doc.attr("aspect");
        if(is_similar(ap, "ignore"))
            resizing        = AspectRatioPolicy::Ignore;
        if(is_similar(ap, "expand"))
            resizing        = AspectRatioPolicy::Expand;
        if(is_similar(ap, "shrink"))
            resizing        = AspectRatioPolicy::Shrink;
    
        
    
        b3Info  << "Bounds for the document are: " << doc.bounds();
        b3Info  << "Edges for the document are: " << doc.edges();
        b3Info  << "Point count for the document is: " << doc.points(COUNT);



        MapPainter  mapper(dev, doc, bb, { .heading=hdg, .resizing = resizing });
        
        //  TODO... options for areas, details, etc.... (default to the image)....
    
        return true;
    }
}

