////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/b3/typedef.hpp>
#include <yq/b3/util/types.hpp>

#include <yq/units.hpp>
#include <yq/container/Set.hpp>
#include <yq/math/Range.hpp>
#include <yq/typedef/range.hpp>
#include <yq/typedef/string_sets.hpp>

namespace yq::b3 {

    //! Series of positional based arguments (whatever they may be)
    struct ArgList {
        Vector<std::string>     values;
        
        std::string_view        operator[](size_t) const;
        std::string_view        value(size_t) const;
        
        bool            empty() const { return values.empty(); }
        size_t          size() const { return values.size(); }
        ArgList         subarg(size_t pos, size_t n=SIZE_MAX) const;

        unit::Degree    angle(size_t, unit::Degree def={0.}) const;
        bool            boolean(size_t, bool def=false) const;
        Brush           brush(size_t) const;
        Color           color(size_t) const;
        CoordN          coord(size_t) const;
        Coord2I         coord2(size_t) const;
        Coord3I         coord3(size_t) const;
        CountN          count(size_t) const;
        Font            font(size_t) const;
        int             integer(size_t, int def=0) const;
        IntegerSet      integer_set(size_t) const;
        RangeI          irange(size_t, const RangeI& def={}) const;
        double          length(size_t, double def=0.) const;
        Pen             pen(size_t) const;
        PointN          point(size_t) const;
        Vector2D        point2(size_t) const;
        Vector3D        point3(size_t) const;
        //! Double (but can't use "double" in the name)
        double          real(size_t, double def=0.) const;
        SizeN           size(size_t) const;
        Size2D          size2(size_t) const;
        Size3D          size3(size_t) const;
        std::string     string(size_t, std::string_view def={}) const;
        StringSet       string_set(size_t) const;
        VectorN         vector(size_t) const;
        Vector2D        vector2(size_t) const;
        Vector3D        vector3(size_t) const;
        
    };

}
