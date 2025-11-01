////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <variant>
#include <yq/art/forward.hpp>
#include <yq/color/RGB.hpp>
#include <yq/color/RGBA.hpp>

namespace yq::art {
    using color_t = std::variant<
        std::monostate, // empty/unspecified color
        std::string,    // named color
        RGB3F,
        RGB3U8,
        RGB3U16,
        RGBA4F,
        RGBA4U8,
        RGBA4U16,
        ID,             // a color object (by ID)
        Key             // a color object (by Key)
    >;
}

