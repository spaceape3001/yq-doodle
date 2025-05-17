////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/typedef/vector1.hpp>
#include <yq/typedef/vector2.hpp>
#include <yq/typedef/vector3.hpp>
#include <yq/typedef/vector4.hpp>
#include <yq/meta/InfoBinder.hpp>

#include <variant>

namespace yq {
    struct AlgebraString;
}

namespace yq::doodle {
    using double_v  = std::variant<std::monostate, std::string, double>;
    using vector1_v = std::variant<std::monostate, std::string, Vector1D>;
    using vector2_v = std::variant<std::monostate, std::string, Vector2D>;
    using vector3_v = std::variant<std::monostate, std::string, Vector3D>;
    using vector4_v = std::variant<std::monostate, std::string, Vector4D>;
}

YQ_TYPE_DECLARE(yq::doodle::double_v)
YQ_TYPE_DECLARE(yq::doodle::vector1_v)
YQ_TYPE_DECLARE(yq::doodle::vector2_v)
YQ_TYPE_DECLARE(yq::doodle::vector3_v)
YQ_TYPE_DECLARE(yq::doodle::vector4_v)
