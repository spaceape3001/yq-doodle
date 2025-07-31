////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "args.hpp"
#include "types.hpp"

#include <yq/core/ErrorDB.hpp>
#include <yq/text/chars.hpp>
#include <yq/text/match.hpp>
#include <yq/text/parse.hpp>
#include <yq/text/split.hpp>
#include <yq/text/transform.hpp>
#include <yq/text/vsplit.hpp>


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

    unit::Degree    ArgMap::angle(const std::string&k) const
    {
        return parse::angle(attr(k));
    }
    
    bool            ArgMap::boolean(const std::string&k) const
    {
        return parse::boolean(attr(k));
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
    
    int             ArgMap::integer(const std::string&k) const
    {
        return parse::integer(attr(k));
    }
    
    IntegerSet      ArgMap::integer_set(const std::string&k) const
    {
        return parse::integer_set(attr(k));
    }
    
    double          ArgMap::length(const std::string&k) const
    {
        return parse::length(attr(k));
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
    
    double          ArgMap::real(const std::string&k) const
    {
        return parse::real(attr(k));
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


    unit::Degree    ArgVector::angle(size_t i) const
    {
        return parse::angle(value(i));
    }
    
    bool            ArgVector::boolean(size_t i) const
    {
        return parse::boolean(value(i));
    }
    
    Brush           ArgVector::brush(size_t i) const
    {
        return parse::brush(value(i));
    }
    
    Color           ArgVector::color(size_t i) const
    {
        return parse::color(value(i));
    }
    
    CoordN          ArgVector::coord(size_t i) const
    {
        return parse::coord(value(i));
    }
    
    Coord2I         ArgVector::coord2(size_t i) const
    {
        return parse::coord2(value(i));
    }
    
    Coord3I         ArgVector::coord3(size_t i) const
    {
        return parse::coord3(value(i));
    }
    
    CountN          ArgVector::count(size_t i) const
    {
        return parse::count(value(i));
    }
    
    Font            ArgVector::font(size_t i) const
    {
        return parse::font(value(i));
    }
    
    int             ArgVector::integer(size_t i) const
    {
        return parse::integer(value(i));
    }
    
    IntegerSet      ArgVector::integer_set(size_t i) const
    {
        return parse::integer_set(value(i));
    }
    
    double          ArgVector::length(size_t i) const
    {
        return parse::length(value(i));
    }
    
    Pen             ArgVector::pen(size_t i) const
    {
        return parse::pen(value(i));
    }
    
    PointN          ArgVector::point(size_t i) const
    {
        return parse::point(value(i));
    }
    
    Vector2D        ArgVector::point2(size_t i) const
    {
        return parse::point2(value(i));
    }
    
    Vector3D        ArgVector::point3(size_t i) const
    {
        return parse::point3(value(i));
    }
    
    double          ArgVector::real(size_t i) const
    {
        return parse::real(value(i));
    }
    
    SizeN           ArgVector::size(size_t i) const
    {
        return parse::size(value(i));
    }
    
    Size2D          ArgVector::size2(size_t i) const
    {
        return parse::size2(value(i));
    }
    
    Size3D          ArgVector::size3(size_t i) const
    {
        return parse::size3(value(i));
    }
    
    StringSet       ArgVector::string_set(size_t i) const
    {
        return parse::string_set(value(i));
    }
    
    VectorN        ArgVector::vector(size_t i) const
    {
        return parse::vector(value(i));
    }

    Vector2D        ArgVector::vector2(size_t i) const
    {
        return parse::vector2(value(i));
    }
    
    Vector3D        ArgVector::vector3(size_t i) const
    {
        return parse::vector3(value(i));
    }
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


namespace yq::b3::parse {

    struct Repo {
        StringMap       colors;
        DoubleMap       units;
        
        std::string_view    color(const std::string& k) const
        {
            auto i = colors.find(k);
            if(i == colors.end())
                return k;
            return i->second;
        }
        
        double              unit(const std::string& k) const
        {
            auto i = units.find(k);
            if(i == units.end())
                return 1.0;
            return i->second;
        }
    };
    
    Repo&   repo()
    {
        static Repo s_repo;
        return s_repo;
    }

    void    add_color(const std::string& k, const std::string& v)
    {
        repo().colors[k]    = std::string(v);
    }
    
    void    add_unit(const std::string& k, double v)
    {
        repo().units[k]     = v;
    }

    unit::Degree    angle(std::string_view v)
    {
        return unit::Degree{real(v)};
    }

    bool    boolean(std::string_view v)
    {
        auto x = to_boolean(v);
        if(!x)
            return false;
        return *x;
    }

    Brush           brush(std::string_view v)
    {
        return Brush{ color(v) };
    }

    Color   color(std::string_view v)
    {
        Color               ret{ std::string(v) };
        std::string_view    clr = repo().color(ret.def);
        if(!clr.empty())
            ret.def     = std::string(clr);
        return ret;
    }

    CoordN              coord(std::string_view v)
    {
        CoordN      ret;
        vsplit(v, ',', [&](std::string_view s){
            if(s.empty())
                return;
            ret.indices.push_back(integer(s));
        });
        return ret;
    }
    
    Coord2I             coord2(std::string_view v)
    {
        return (Coord2I) coord(v);
    }
    
    Coord3I             coord3(std::string_view v)
    {
        return (Coord3I) coord(v);
    }

    CountN              count(std::string_view v)
    {
        CountN      ret;
        vsplit(v, ',', [&](std::string_view s){
            if(s.empty())
                return;
            ret.axes.push_back(integer(s));
        });
        return ret;
    }

    Font            font(std::string_view v)
    {
        Font    ret;
        auto bits = split(v,',');
        if(bits.size() > 0)
            ret.family    = std::string(bits[0]);
        if(bits.size() > 1)
            ret.size = real(bits[1]);
        return ret;
    }

    int                 integer(std::string_view v)
    {
        auto x =  to_integer(v);
        if(!x)
            return 0;
        return *x;
    }

    IntegerSet          integer_set(std::string_view v)
    {
        IntegerSet      ret;
        vsplit(v, ',', [&](std::string_view s){
            if(s.empty())
                return;
            ret.insert(integer(s));
        });
        return ret;
    }

    double          length(std::string_view v)
    {
        size_t n;
        for(n=v.size()-1;n>=0; --n)
            if(!is_alpha(v[n]))
                break;

        if(n < v.size()-1){
            std::string         unit(v.substr(n+1));
            std::string_view    value   = v.substr(0,n);
            
            auto x  = to_double(value);
            if(!x)
                return 0.;
            
            return repo().unit(unit) * *x;
        } else {
            auto x  = to_double(v);
            if(!x)
                return 0.;
            return *x;
        }
    }
    
    Pen             pen(std::string_view v)
    {
        Pen ret;
        auto bits   = split(v, '/');
        if(bits.size() > 0)
            ret.color   = color(bits[0]);
        if(bits.size() > 1)
            ret.width   =  real(bits[1]);
        if(bits.size() > 2){
            auto style  = bits[2];
            if(is_similar(style, "solid")){
                ret.style  = PenStyle::Solid;
            } else if(is_similar(style, "dash")) {
                ret.style  = PenStyle::Dash;
            } else if(is_similar(style, "dot")) {
                ret.style  = PenStyle::Dot;
            } else if(is_similar(style, "dashdot") || is_similar(style, "dotdash")){
                ret.style  = PenStyle::DashDot;
            } 
        }
        return ret;
    }

    PointN           point(std::string_view v)
    {
        PointN      ret;
        vsplit(v, ',', [&](std::string_view s){
            if(s.empty())
                return;
            ret.axes.push_back(length(s));
        });
        return ret;
    }

    Vector2D         point2(std::string_view v)
    {
        return (Vector2D) point(v);
    }
    
    Vector3D         point3(std::string_view v)
    {
        return (Vector3D) point(v);
    }

    double              real(std::string_view v)
    {
        auto x = to_double(v);
        if(!x)
            return 0.;
        return *x;
    }
    
    SizeN               size(std::string_view v)
    {
        SizeN      ret;
        vsplit(v, ',', [&](std::string_view s){
            if(s.empty())
                return;
            ret.axes.push_back(length(s));
        });
        return ret;
    }

    Size2D        size2(std::string_view v)
    {
        return (Size2D) size(v);
    }
    
    Size3D        size3(std::string_view v)
    {
        return (Size3D) size(v);
    }

    StringSet       string_set(std::string_view v)
    {
        StringSet       ret;
        vsplit(v, ',', [&](std::string_view s){
            ret.insert(std::string(trimmed(s)));
        });
        return ret;
    }
    
    VectorN         vector(std::string_view v)
    {
        VectorN      ret;
        vsplit(v, ',', [&](std::string_view s){
            if(s.empty())
                return;
            ret.axes.push_back(real(s));
        });
        return ret;
    }

    Vector2D        vector2(std::string_view v)
    {
        return (Vector2D) vector(v);
    }
    
    Vector3D        vector3(std::string_view v)
    {
        return (Vector3D) vector(v);
    }
}
