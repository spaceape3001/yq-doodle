////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/container/forward.hpp>

namespace yq::b3 {
    enum class PenStyle {
        Solid,
        Dash,
        Dot,
        DashDot
    };

    using IntegerSet    = Set<int>;

    struct Context;
    struct Color;

    struct CoordN;
    struct CountN;
    struct Brush;
    struct Pen;
    struct Font;
    struct PointN;
    struct SizeN;
    struct VectorN;
}
