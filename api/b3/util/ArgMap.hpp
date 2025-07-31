////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once


#include <b3/typedef.hpp>
#include <b3/util/types.hpp>

#include <yq/units.hpp>
#include <yq/container/Map.hpp>
#include <yq/container/Set.hpp>
#include <yq/text/IgCase.hpp>
#include <yq/typedef/expected.hpp>
#include <yq/typedef/string_maps.hpp>
#include <yq/typedef/string_sets.hpp>

namespace yq::b3 {

    //! Map based (key/value) arguments.
    struct ArgMap {
        StringMap               attrs;

        std::string_view        operator[](const std::string&) const;
        std::string_view        attr(const std::string&) const;
        
        void            erase(const std::string&);
        bool            has(const std::string&) const;

        unit::Degree    angle(const std::string&, unit::Degree def={0.}) const;
        bool            boolean(const std::string&, bool def=false) const;
        Brush           brush(const std::string&) const;
        Color           color(const std::string&) const;
        CoordN          coord(const std::string&) const;
        Coord2I         coord2(const std::string&) const;
        Coord3I         coord3(const std::string&) const;
        CountN          count(const std::string&) const;
        Font            font(const std::string&) const;
        int             integer(const std::string&, int def=0) const;
        IntegerSet      integer_set(const std::string&) const;
        double          length(const std::string&, double def=0.) const;
        Pen             pen(const std::string&) const;
        PointN          point(const std::string&) const;
        Vector2D        point2(const std::string&) const;
        Vector3D        point3(const std::string&) const;
        //! Double (but can't use "double" in the name)
        double          real(const std::string&, double def=0.) const;
        SizeN           size(const std::string&) const;
        Size2D          size2(const std::string&) const;
        Size3D          size3(const std::string&) const;
        std::string     string(const std::string&, const std::string_view def={}) const;
        StringSet       string_set(const std::string&) const;
        VectorN         vector(const std::string&) const;
        Vector2D        vector2(const std::string&) const;
        Vector3D        vector3(const std::string&) const;
        
        ArgMap();
        ~ArgMap();
        ArgMap(const ArgMap&);
        ArgMap(ArgMap&&);
        ArgMap(const StringMap&);
        ArgMap(StringMap&&);
        ArgMap& operator=(const ArgMap&);
        ArgMap& operator=(ArgMap&&);
        
        ArgMap& operator=(const StringMap&);
        ArgMap& operator=(StringMap&&);
    };
}
