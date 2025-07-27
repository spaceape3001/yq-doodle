////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <b3/types.hpp>
#include <yq/units.hpp>
#include <yq/container/Set.hpp>
#include <yq/typedef/expected.hpp>
#include <yq/typedef/string_sets.hpp>

namespace yq::b3::parse {
    Expect<unit::Degree>    angle(Context&, std::string_view);
    Expect<bool>            boolean(Context&, std::string_view);
    Expect<Brush>           brush(Context&, std::string_view);
    Expect<Color>           color(Context&, std::string_view);
    Expect<CoordN>          coord(Context&, std::string_view);
    Expect<Coord2I>         coord2(Context&, std::string_view);
    Expect<Coord3I>         coord3(Context&, std::string_view);
    Expect<CountN>          count(Context&, std::string_view);
    Expect<Font>            font(Context&, std::string_view);
    Expect<int>             integer(Context&, std::string_view);
    Expect<IntegerSet>      integer_set(Context&, std::string_view);
    Expect<double>          length(Context&, std::string_view);
    Expect<Pen>             pen(Context&, std::string_view);
    Expect<PointN>          point(Context&, std::string_view);
    Expect<Vector2D>        point2(Context&, std::string_view);
    Expect<Vector3D>        point3(Context&, std::string_view);
    //! Double (but can't use "double" in the name)
    Expect<double>          real(Context&, std::string_view);
    Expect<SizeN>           size(Context&, std::string_view);
    Expect<Size2D>          size2(Context&, std::string_view);
    Expect<Size3D>          size3(Context&, std::string_view);
    Expect<StringSet>       string_set(Context&, std::string_view);
    Expect<VectorN>         vector(Context&, std::string_view);
    Expect<Vector2D>        vector2(Context&, std::string_view);
    Expect<Vector3D>        vector3(Context&, std::string_view);
};

