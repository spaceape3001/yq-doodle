////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/meta/MetaBinder.hpp>
#include <variant>

namespace yq::doodle {
    using double_v  = std::variant<std::monostate, std::string, double>;
}

YQ_TYPE_DECLARE(yq::doodle::double_v)
