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
    struct child_k {};
    struct raw_k {};
    struct shared_k {};
    struct unique_k {};
    struct xml_k {
        consteval operator SFormat() const { return SFormat::XML; }
    };
    
    static constexpr const b3_k     B3;
    static constexpr const child_k  CHILD;
    static constexpr const raw_k    RAW;
    static constexpr const shared_k SHARED;
    static constexpr const unique_k UNIQUE;
    static constexpr const xml_k    XML;
}
