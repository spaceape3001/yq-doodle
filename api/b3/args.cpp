////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "args.hpp"
#include "parse.hpp"
#include "types.hpp"

namespace yq::b3 {
  
    std::string_view        ArgMap::operator[](const std::string&k) const
    {
        return attr(k);
    }
    
    std::string_view        ArgMap::attr(const std::string&k) const
    {
        auto i = attrs.find(k);
        if(i == attrs.end())
            return {};
        return i->second;
    }

    //  ........................................................................

    Expect<unit::Degree>    ArgMap::angle(Context&c, const std::string&k) const
    {
        return parse::angle(c, attr(k));
    }
    
    Expect<bool>            ArgMap::boolean(Context&c, const std::string&k) const
    {
        return parse::boolean(c,attr(k));
    }
    
    Expect<Brush>           ArgMap::brush(Context&c, const std::string&k) const
    {
        return parse::brush(c,attr(k));
    }
    
    Expect<Color>           ArgMap::color(Context&c, const std::string&k) const
    {
        return parse::color(c,attr(k));
    }
    
    Expect<CoordN>          ArgMap::coord(Context&c, const std::string&k) const
    {
        return parse::coord(c,attr(k));
    }
    
    Expect<Coord2I>         ArgMap::coord2(Context&c, const std::string&k) const
    {
        return parse::coord2(c,attr(k));
    }
    
    Expect<Coord3I>         ArgMap::coord3(Context&c, const std::string&k) const
    {
        return parse::coord3(c,attr(k));
    }
    
    Expect<CountN>          ArgMap::count(Context&c, const std::string&k) const
    {
        return parse::count(c,attr(k));
    }
    
    Expect<Font>            ArgMap::font(Context&c, const std::string&k) const
    {
        return parse::font(c,attr(k));
    }
    
    Expect<int>             ArgMap::integer(Context&c, const std::string&k) const
    {
        return parse::integer(c,attr(k));
    }
    
    Expect<IntegerSet>      ArgMap::integer_set(Context&c, const std::string&k) const
    {
        return parse::integer_set(c,attr(k));
    }
    
    Expect<double>          ArgMap::length(Context&c, const std::string&k) const
    {
        return parse::length(c,attr(k));
    }
    
    Expect<Pen>             ArgMap::pen(Context&c, const std::string&k) const
    {
        return parse::pen(c,attr(k));
    }
    
    Expect<PointN>          ArgMap::point(Context&c, const std::string&k) const
    {
        return parse::point(c,attr(k));
    }
    
    Expect<Vector2D>        ArgMap::point2(Context&c, const std::string&k) const
    {
        return parse::point2(c,attr(k));
    }
    
    Expect<Vector3D>        ArgMap::point3(Context&c, const std::string&k) const
    {
        return parse::point3(c,attr(k));
    }
    
    Expect<double>          ArgMap::real(Context&c, const std::string&k) const
    {
        return parse::real(c,attr(k));
    }
    
    Expect<SizeN>           ArgMap::size(Context&c, const std::string&k) const
    {
        return parse::size(c,attr(k));
    }
    
    Expect<Size2D>          ArgMap::size2(Context&c, const std::string&k) const
    {
        return parse::size2(c,attr(k));
    }
    
    Expect<Size3D>          ArgMap::size3(Context&c, const std::string&k) const
    {
        return parse::size3(c,attr(k));
    }
    
    Expect<StringSet>       ArgMap::string_set(Context&c, const std::string&k) const
    {
        return parse::string_set(c,attr(k));
    }
    
    Expect<VectorN>        ArgMap::vector(Context&c, const std::string&k) const
    {
        return parse::vector(c,attr(k));
    }

    Expect<Vector2D>        ArgMap::vector2(Context&c, const std::string&k) const
    {
        return parse::vector2(c,attr(k));
    }
    
    Expect<Vector3D>        ArgMap::vector3(Context&c, const std::string&k) const
    {
        return parse::vector3(c,attr(k));
    }
    
    
    ////////////////////////////////////////////////////////////////////////////

    std::string_view        ArgVector::operator[](size_t i) const
    {
        return value(i);
    }
    
    std::string_view        ArgVector::value(size_t i) const
    {
        if(i >= values.size())
            return {};
        return values[i];
    }
    
    //  ........................................................................


    Expect<unit::Degree>    ArgVector::angle(Context&c, size_t i) const
    {
        return parse::angle(c, value(i));
    }
    
    Expect<bool>            ArgVector::boolean(Context&c, size_t i) const
    {
        return parse::boolean(c,value(i));
    }
    
    Expect<Brush>           ArgVector::brush(Context&c, size_t i) const
    {
        return parse::brush(c,value(i));
    }
    
    Expect<Color>           ArgVector::color(Context&c, size_t i) const
    {
        return parse::color(c,value(i));
    }
    
    Expect<CoordN>          ArgVector::coord(Context&c, size_t i) const
    {
        return parse::coord(c,value(i));
    }
    
    Expect<Coord2I>         ArgVector::coord2(Context&c, size_t i) const
    {
        return parse::coord2(c,value(i));
    }
    
    Expect<Coord3I>         ArgVector::coord3(Context&c, size_t i) const
    {
        return parse::coord3(c,value(i));
    }
    
    Expect<CountN>          ArgVector::count(Context&c, size_t i) const
    {
        return parse::count(c,value(i));
    }
    
    Expect<Font>            ArgVector::font(Context&c, size_t i) const
    {
        return parse::font(c,value(i));
    }
    
    Expect<int>             ArgVector::integer(Context&c, size_t i) const
    {
        return parse::integer(c,value(i));
    }
    
    Expect<IntegerSet>      ArgVector::integer_set(Context&c, size_t i) const
    {
        return parse::integer_set(c,value(i));
    }
    
    Expect<double>          ArgVector::length(Context&c, size_t i) const
    {
        return parse::length(c,value(i));
    }
    
    Expect<Pen>             ArgVector::pen(Context&c, size_t i) const
    {
        return parse::pen(c,value(i));
    }
    
    Expect<PointN>          ArgVector::point(Context&c, size_t i) const
    {
        return parse::point(c,value(i));
    }
    
    Expect<Vector2D>        ArgVector::point2(Context&c, size_t i) const
    {
        return parse::point2(c,value(i));
    }
    
    Expect<Vector3D>        ArgVector::point3(Context&c, size_t i) const
    {
        return parse::point3(c,value(i));
    }
    
    Expect<double>          ArgVector::real(Context&c, size_t i) const
    {
        return parse::real(c,value(i));
    }
    
    Expect<SizeN>           ArgVector::size(Context&c, size_t i) const
    {
        return parse::size(c,value(i));
    }
    
    Expect<Size2D>          ArgVector::size2(Context&c, size_t i) const
    {
        return parse::size2(c,value(i));
    }
    
    Expect<Size3D>          ArgVector::size3(Context&c, size_t i) const
    {
        return parse::size3(c,value(i));
    }
    
    Expect<StringSet>       ArgVector::string_set(Context&c, size_t i) const
    {
        return parse::string_set(c,value(i));
    }
    
    Expect<VectorN>        ArgVector::vector(Context&c, size_t i) const
    {
        return parse::vector(c,value(i));
    }

    Expect<Vector2D>        ArgVector::vector2(Context&c, size_t i) const
    {
        return parse::vector2(c,value(i));
    }
    
    Expect<Vector3D>        ArgVector::vector3(Context&c, size_t i) const
    {
        return parse::vector3(c,value(i));
    }
}
