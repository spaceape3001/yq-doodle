////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once


#include <b3/util/types.hpp>
#include <b3/util/typedef.hpp>

#include <yq/units.hpp>
#include <yq/container/Map.hpp>
#include <yq/container/Set.hpp>
#include <yq/container/Vector.hpp>
#include <yq/text/IgCase.hpp>
#include <yq/typedef/coord2.hpp>
#include <yq/typedef/coord3.hpp>
#include <yq/typedef/expected.hpp>
#include <yq/typedef/string_maps.hpp>
#include <yq/typedef/string_sets.hpp>
#include <yq/typedef/size2.hpp>
#include <yq/typedef/size3.hpp>
#include <yq/typedef/vector2.hpp>
#include <yq/typedef/vector3.hpp>

namespace yq::b3 {

    //! Series of positional based arguments (whatever they may be)
    struct ArgVector {
        Vector<std::string>     values;
        
        std::string_view        operator[](size_t) const;
        std::string_view        value(size_t) const;

        unit::Degree    angle(size_t) const;
        bool            boolean(size_t) const;
        Brush           brush(size_t) const;
        Color           color(size_t) const;
        CoordN          coord(size_t) const;
        Coord2I         coord2(size_t) const;
        Coord3I         coord3(size_t) const;
        CountN          count(size_t) const;
        Font            font(size_t) const;
        int             integer(size_t) const;
        IntegerSet      integer_set(size_t) const;
        double          length(size_t) const;
        Pen             pen(size_t) const;
        PointN          point(size_t) const;
        Vector2D        point2(size_t) const;
        Vector3D        point3(size_t) const;
        //! Double (but can't use "double" in the name)
        double          real(size_t) const;
        SizeN           size(size_t) const;
        Size2D          size2(size_t) const;
        Size3D          size3(size_t) const;
        StringSet       string_set(size_t) const;
        VectorN         vector(size_t) const;
        Vector2D        vector2(size_t) const;
        Vector3D        vector3(size_t) const;
        
    };
    
    using ArgList = ArgVector;

    //! Map based (key/value) arguments.
    struct ArgMap {
        StringMap               attrs;

        std::string_view        operator[](const std::string&) const;
        std::string_view        attr(const std::string&) const;

        unit::Degree    angle(const std::string&) const;
        bool            boolean(const std::string&) const;
        Brush           brush(const std::string&) const;
        Color           color(const std::string&) const;
        CoordN          coord(const std::string&) const;
        Coord2I         coord2(const std::string&) const;
        Coord3I         coord3(const std::string&) const;
        CountN          count(const std::string&) const;
        Font            font(const std::string&) const;
        int             integer(const std::string&) const;
        IntegerSet      integer_set(const std::string&) const;
        double          length(const std::string&) const;
        Pen             pen(const std::string&) const;
        PointN          point(const std::string&) const;
        Vector2D        point2(const std::string&) const;
        Vector3D        point3(const std::string&) const;
        //! Double (but can't use "double" in the name)
        double          real(const std::string&) const;
        SizeN           size(const std::string&) const;
        Size2D          size2(const std::string&) const;
        Size3D          size3(const std::string&) const;
        StringSet       string_set(const std::string&) const;
        VectorN         vector(const std::string&) const;
        Vector2D        vector2(const std::string&) const;
        Vector3D        vector3(const std::string&) const;
        
        ArgMap(){}
        virtual ~ArgMap(){}
    };
}
