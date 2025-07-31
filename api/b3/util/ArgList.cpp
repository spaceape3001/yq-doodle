////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "ArgList.hpp"
#include "parse.hpp"

namespace yq::b3 {
    std::string_view        ArgList::operator[](size_t i) const
    {
        return value(i);
    }

    ArgList         ArgList::subarg(size_t pos, size_t n) const
    {
        if(pos >= values.size())
            return {};
        if(n > values.size())
            n   = values.size();
        size_t  m   = std::min(values.size(), pos+n);
        
        auto    b   = values.begin() + pos;
        auto    e   = values.begin() + m;
        std::vector<std::string>    res(b,e);
        
        return ArgList{.values=std::move(res)};
    }
    
    std::string_view        ArgList::value(size_t i) const
    {
        if(i >= values.size())
            return {};
        return values[i];
    }
    
    //  ........................................................................


    unit::Degree    ArgList::angle(size_t i, unit::Degree def) const
    {
        std::string_view    s = value(i);
        if(s.empty())
            return def;
        return parse::angle(s, def);
    }
    
    bool            ArgList::boolean(size_t i, bool def) const
    {
        std::string_view    s = value(i);
        if(s.empty())
            return def;
        return parse::boolean(s, def);
    }
    
    Brush           ArgList::brush(size_t i) const
    {
        return parse::brush(value(i));
    }
    
    Color           ArgList::color(size_t i) const
    {
        return parse::color(value(i));
    }
    
    CoordN          ArgList::coord(size_t i) const
    {
        return parse::coord(value(i));
    }
    
    Coord2I         ArgList::coord2(size_t i) const
    {
        return parse::coord2(value(i));
    }
    
    Coord3I         ArgList::coord3(size_t i) const
    {
        return parse::coord3(value(i));
    }
    
    CountN          ArgList::count(size_t i) const
    {
        return parse::count(value(i));
    }
    
    Font            ArgList::font(size_t i) const
    {
        return parse::font(value(i));
    }
    
    int             ArgList::integer(size_t i, int def) const
    {
        std::string_view    s = value(i);
        if(s.empty())
            return def;
        return parse::integer(s, def);
    }
    
    IntegerSet      ArgList::integer_set(size_t i) const
    {
        return parse::integer_set(value(i));
    }
    
    double          ArgList::length(size_t i, double def) const
    {
        std::string_view    s = value(i);
        if(s.empty())
            return def;
        return parse::length(s, def);
    }
    
    Pen             ArgList::pen(size_t i) const
    {
        return parse::pen(value(i));
    }
    
    PointN          ArgList::point(size_t i) const
    {
        return parse::point(value(i));
    }
    
    Vector2D        ArgList::point2(size_t i) const
    {
        return parse::point2(value(i));
    }
    
    Vector3D        ArgList::point3(size_t i) const
    {
        return parse::point3(value(i));
    }
    
    double          ArgList::real(size_t i, double def) const
    {
        std::string_view    s = value(i);
        if(s.empty())
            return def;
        return parse::real(s, def);
    }
    
    SizeN           ArgList::size(size_t i) const
    {
        return parse::size(value(i));
    }
    
    Size2D          ArgList::size2(size_t i) const
    {
        return parse::size2(value(i));
    }
    
    Size3D          ArgList::size3(size_t i) const
    {
        return parse::size3(value(i));
    }
    
    std::string     ArgList::string(size_t i, std::string_view def) const
    {
        if(i < values.size())
            return values[i];
        return std::string(def);
    }

    StringSet       ArgList::string_set(size_t i) const
    {
        return parse::string_set(value(i));
    }
    
    VectorN        ArgList::vector(size_t i) const
    {
        return parse::vector(value(i));
    }

    Vector2D        ArgList::vector2(size_t i) const
    {
        return parse::vector2(value(i));
    }
    
    Vector3D        ArgList::vector3(size_t i) const
    {
        return parse::vector3(value(i));
    }
}
