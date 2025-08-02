////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <b3/logging.hpp>
#include <b3/Doc.hpp>
#include <b3/paint/MapPainter.hpp>
#include <b3/paint/SvgGenerator.hpp>
#include <b3/paint/RasterGenerator.hpp>
#include <yq/shape/AxBox2.hxx>

using namespace yq;
using namespace yq::b3;

static bool     docMap(Doc&doc, PaintDevice& dev)
{
    b3Info  << "Bounds for the document are: " << doc.bounds();
    b3Info  << "Edges for the document are: " << doc.edges();
    b3Info  << "Point count for the document is: " << doc.points(COUNT);

    MapPainter  mapper(dev, doc);
    
    //  TODO... options for areas, details, etc.... (default to the image)....
    
    
    
    return false;
}

////////////////////////////////////////////////////////////////////////////////

static bool     docMapPng(Doc& doc)
{
    RasterGenerator         ras;
    std::filesystem::path   file    = doc.output_reextension(LAST, "png");

    if(!docMap(doc, ras)){
        b3Error << "Unable to save {file='" << file << "'}: document failed to export to map";
        if(!doc.attrs().boolean("ignore"))
            return false;
    }
    std::error_code ec  = ras.save_to(file);
    if(ec != std::error_code()){
        b3Error << "Unable to save {file='" << file << "'}: " << ec.message();
        return false;
    }
    return true;
}

YQ_B3_HANDLER("mappng", "Draws a map as a PNG file", docMapPng);

static bool     docMapSvg(Doc& doc)
{
    SvgGenerator    svg;
    std::filesystem::path   file    = doc.output_reextension(LAST, "svg");
    if(!docMap(doc, svg)){
        b3Error << "Unable to save {file='" << file << "'}: document failed to export to map";
        if(!doc.attrs().boolean("ignore"))
            return false;
    }
    std::error_code ec  = svg.save_to(file);
    if(ec != std::error_code()){
        b3Error << "Unable to save {file='" << file << "'}: " << ec.message();
        return false;
    }
    return true;
}

YQ_B3_HANDLER("mapsvg", "Draws a map as a SVG file", docMapSvg);

