////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string_view>

namespace yq::b3 {
    enum class PointType {
        Unknown,
        D1,
        D2,
        D3,
        AGL,
        MSL
    };

    PointType           decode_point_type(std::string_view);
    std::string_view    key_for(PointType);
}
