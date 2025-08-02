////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <b3/logging.hpp>
#include <b3/Doc.hpp>
#include <b3/MapPainter.hpp>
#include <b3/paint/SvgGenerator.hpp>

using namespace yq;
using namespace yq::b3;

static bool     docMap(Doc&doc, PaintDevice& dev)
{
    MapPainter  mapper(dev, doc);
    return false;
}

////////////////////////////////////////////////////////////////////////////////

static bool     docMapPng(Doc& doc)
{
    std::filesystem::path   file    = doc.output_reextension(LAST, "png");

    b3Critical << "Map PNG is not yet supported";
    return false;
}

YQ_B3_HANDLER("mappng", "Draws a map as a PNG file", docMapPng);

static bool     docMapSvg(Doc& doc)
{
    SvgGenerator    svg;
    std::filesystem::path   file    = doc.output_reextension(LAST, "svg");
    if(!docMap(doc, svg)){
        b3Error << "Unable to save {file='" << file << "'}: document failed to export to map";
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

