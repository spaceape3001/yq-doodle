////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/keywords.hpp>
#include <doodle/bit/SFormat.hpp>

namespace yq::doodle {
    struct b3_k {
        consteval operator SFormat() const { return SFormat::B3; }
    };
    struct xml_k {
        consteval operator SFormat() const { return SFormat::XML; }
    };
    
    static constexpr const b3_k     B3;
    static constexpr const xml_k    XML;
}
