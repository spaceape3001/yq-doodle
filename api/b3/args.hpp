////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <b3/typedef.hpp>
#include <yq/container/Map.hpp>
#include <yq/container/Vector.hpp>
#include <yq/text/IgCase.hpp>
#include <yq/typedef/coord2.hpp>
#include <yq/typedef/coord3.hpp>
#include <yq/typedef/expected.hpp>
#include <yq/typedef/string_sets.hpp>
#include <yq/typedef/size2.hpp>
#include <yq/typedef/size3.hpp>
#include <yq/typedef/vector2.hpp>
#include <yq/typedef/vector3.hpp>
#include <yq/unit/declare.hpp>

namespace yq::b3 {

    //! Series of positional based arguments (whatever they may be)
    struct ArgVector {
        Vector<std::string>     values;
        
        std::string_view        operator[](size_t) const;
        std::string_view        value(size_t) const;

        Expect<unit::Degree>    angle(Context&, size_t) const;
        Expect<bool>            boolean(Context&, size_t) const;
        Expect<Brush>           brush(Context&, size_t) const;
        Expect<Color>           color(Context&, size_t) const;
        Expect<CoordN>          coord(Context&, size_t) const;
        Expect<Coord2I>         coord2(Context&, size_t) const;
        Expect<Coord3I>         coord3(Context&, size_t) const;
        Expect<CountN>          count(Context&, size_t) const;
        Expect<Font>            font(Context&, size_t) const;
        Expect<int>             integer(Context&, size_t) const;
        Expect<IntegerSet>      integer_set(Context&, size_t) const;
        Expect<double>          length(Context&, size_t) const;
        Expect<Pen>             pen(Context&, size_t) const;
        Expect<PointN>          point(Context&, size_t) const;
        Expect<Vector2D>        point2(Context&, size_t) const;
        Expect<Vector3D>        point3(Context&, size_t) const;
        //! Double (but can't use "double" in the name)
        Expect<double>          real(Context&, size_t) const;
        Expect<SizeN>           size(Context&, size_t) const;
        Expect<Size2D>          size2(Context&, size_t) const;
        Expect<Size3D>          size3(Context&, size_t) const;
        Expect<StringSet>       string_set(Context&, size_t) const;
        Expect<VectorN>         vector(Context&, size_t) const;
        Expect<Vector2D>        vector2(Context&, size_t) const;
        Expect<Vector3D>        vector3(Context&, size_t) const;
        
    };

    //! Map based (key/value) arguments.
    struct ArgMap {
        Map<std::string,std::string,IgCase>     attrs;

        std::string_view        operator[](const std::string&) const;
        std::string_view        attr(const std::string&) const;

        Expect<unit::Degree>    angle(Context&, const std::string&) const;
        Expect<bool>            boolean(Context&, const std::string&) const;
        Expect<Brush>           brush(Context&, const std::string&) const;
        Expect<Color>           color(Context&, const std::string&) const;
        Expect<CoordN>          coord(Context&, const std::string&) const;
        Expect<Coord2I>         coord2(Context&, const std::string&) const;
        Expect<Coord3I>         coord3(Context&, const std::string&) const;
        Expect<CountN>          count(Context&, const std::string&) const;
        Expect<Font>            font(Context&, const std::string&) const;
        Expect<int>             integer(Context&, const std::string&) const;
        Expect<IntegerSet>      integer_set(Context&, const std::string&) const;
        Expect<double>          length(Context&, const std::string&) const;
        Expect<Pen>             pen(Context&, const std::string&) const;
        Expect<PointN>          point(Context&, const std::string&) const;
        Expect<Vector2D>        point2(Context&, const std::string&) const;
        Expect<Vector3D>        point3(Context&, const std::string&) const;
        //! Double (but can't use "double" in the name)
        Expect<double>          real(Context&, const std::string&) const;
        Expect<SizeN>           size(Context&, const std::string&) const;
        Expect<Size2D>          size2(Context&, const std::string&) const;
        Expect<Size3D>          size3(Context&, const std::string&) const;
        Expect<StringSet>       string_set(Context&, const std::string&) const;
        Expect<VectorN>         vector(Context&, const std::string&) const;
        Expect<Vector2D>        vector2(Context&, const std::string&) const;
        Expect<Vector3D>        vector3(Context&, const std::string&) const;
    };
}
