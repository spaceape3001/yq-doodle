////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "b3.hpp"

#include <b3/map/map.hpp>
#include <b3/paint/SvgGenerator.hpp>
#include <b3/paint/RasterGenerator.hpp>
#include <yq/shape/AxBox2.hxx>

using namespace yq;
using namespace yq::b3;

////////////////////////////////////////////////////////////////////////////////

static bool     docMapPng(Doc& doc)
{
    RasterGenerator         ras;
    std::filesystem::path   file    = doc.output_reextension(LAST, "png");

    if(!render_map(doc, ras)){
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
    if(!render_map(doc, svg)){
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

