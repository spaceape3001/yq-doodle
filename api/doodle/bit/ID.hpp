////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstdint>
#include <yq/meta/InfoBinder.hpp>
#include <doodle/typedef/id.hpp>

namespace yq::doodle {
    struct ID {
        using id_t      = uint32_t;
        id_t    id  = {};
        constexpr operator id_t () const noexcept { return id; }
        constexpr auto operator<=>(const ID&) const noexcept = default;
    };
}

YQ_TYPE_DECLARE(yq::doodle::ID)
