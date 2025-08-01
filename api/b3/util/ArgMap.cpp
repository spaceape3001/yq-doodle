////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "ArgMap.hpp"
#include "parse.hpp"

namespace yq::b3 {
  
    ArgMap::ArgMap() = default;
    ArgMap::~ArgMap() = default;
    ArgMap::ArgMap(const ArgMap&) = default;
    ArgMap::ArgMap(ArgMap&&) = default;
    ArgMap& ArgMap::operator=(const ArgMap&) = default;
    ArgMap& ArgMap::operator=(ArgMap&&) = default;

    ArgMap::ArgMap(const StringMap&vals) : attrs(vals) {}
    ArgMap::ArgMap(StringMap&&vals) : attrs(std::move(vals)) {}

    ArgMap& ArgMap::operator=(const StringMap& vals)
    {
        attrs   = vals;
        return *this;
    }
    
    ArgMap& ArgMap::operator=(StringMap&&vals)
    {
        if(&vals != &attrs)
            attrs   = std::move(vals);
        return *this;
    }

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

    void            ArgMap::erase(const std::string& k)
    {
        attrs.erase(k);
    }
    
    bool            ArgMap::has(const std::string&k) const
    {
        return attrs.has(k);
    }

    //  ........................................................................

    unit::Degree    ArgMap::angle(const std::string&k, unit::Degree def) const
    {
        std::string_view    s   = attr(k);
        if(s.empty())
            return def;
        return parse::angle(s, def);
    }
    
    bool            ArgMap::boolean(const std::string&k, bool def) const
    {
        std::string_view    s   = attr(k);
        if(s.empty())
            return def;
        return parse::boolean(s, def);
    }
    
    Brush           ArgMap::brush(const std::string&k) const
    {
        return parse::brush(attr(k));
    }
    
    Color           ArgMap::color(const std::string&k) const
    {
        return parse::color(attr(k));
    }
    
    CoordN          ArgMap::coord(const std::string&k) const
    {
        return parse::coord(attr(k));
    }
    
    Coord2I         ArgMap::coord2(const std::string&k) const
    {
        return parse::coord2(attr(k));
    }
    
    Coord3I         ArgMap::coord3(const std::string&k) const
    {
        return parse::coord3(attr(k));
    }
    
    CountN          ArgMap::count(const std::string&k) const
    {
        return parse::count(attr(k));
    }
    
    Font            ArgMap::font(const std::string&k) const
    {
        return parse::font(attr(k));
    }
    
    int             ArgMap::integer(const std::string&k, int def) const
    {
        std::string_view    s   = attr(k);
        if(s.empty())
            return def;
        return parse::integer(s, def);
    }
    
    IntegerSet      ArgMap::integer_set(const std::string&k) const
    {
        return parse::integer_set(attr(k));
    }

    RangeI          ArgMap::irange(const std::string& k, const RangeI& def) const
    {
        return parse::irange(attr(k));
    }
    
    double          ArgMap::length(const std::string&k, double def) const
    {
        std::string_view    s   = attr(k);
        if(s.empty())
            return def;
        return parse::length(s);
    }
    
    Pen             ArgMap::pen(const std::string&k) const
    {
        return parse::pen(attr(k));
    }
    
    PointN          ArgMap::point(const std::string&k) const
    {
        return parse::point(attr(k));
    }
    
    Vector2D        ArgMap::point2(const std::string&k) const
    {
        return parse::point2(attr(k));
    }
    
    Vector3D        ArgMap::point3(const std::string&k) const
    {
        return parse::point3(attr(k));
    }
    
    double          ArgMap::real(const std::string&k, double def) const
    {
        std::string_view    s   = attr(k);
        if(s.empty())
            return def;
        return parse::real(s,def);
    }
    
    SizeN           ArgMap::size(const std::string&k) const
    {
        return parse::size(attr(k));
    }
    
    Size2D          ArgMap::size2(const std::string&k) const
    {
        return parse::size2(attr(k));
    }
    
    Size3D          ArgMap::size3(const std::string&k) const
    {
        return parse::size3(attr(k));
    }

    std::string     ArgMap::string(const std::string&k, const std::string_view def) const
    {
        auto i = attrs.find(k);
        if(i != attrs.end())
            return i->second;
        return std::string(def);
    }
    
    StringSet       ArgMap::string_set(const std::string&k) const
    {
        return parse::string_set(attr(k));
    }
    
    VectorN        ArgMap::vector(const std::string&k) const
    {
        return parse::vector(attr(k));
    }

    Vector2D        ArgMap::vector2(const std::string&k) const
    {
        return parse::vector2(attr(k));
    }
    
    Vector3D        ArgMap::vector3(const std::string&k) const
    {
        return parse::vector3(attr(k));
    }
}
