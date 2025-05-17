////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/keywords.hpp>
#include <doodle/io/SFormat.hpp>

namespace yq::doodle {
    struct b3_k {
        consteval operator SFormat() const { return SFormat::B3; }
    };
    struct uid_k {};
    struct xml_k {
        consteval operator SFormat() const { return SFormat::XML; }
    };
    
    
    static constexpr const b3_k     B3;
    static constexpr const uid_k    UID;
    static constexpr const xml_k    XML;
}
