////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "parse.hpp"
#include "types.hpp"
#include "context.hpp"
#include <yq/units.hpp>
#include <yq/container/Set.hpp>
#include <yq/core/ErrorDB.hpp>
#include <yq/text/chars.hpp>
#include <yq/text/match.hpp>
#include <yq/text/parse.hpp>
#include <yq/text/split.hpp>
#include <yq/text/transform.hpp>
#include <yq/text/vsplit.hpp>

namespace yq::b3::parse {
    Expect<unit::Degree>    angle(Context&c, std::string_view v)
    {
        auto x = real(c,v);
        if(!x)
            return unexpected(x.error());
        return unit::Degree{*x};
    }

    Expect<bool>                boolean(Context&, std::string_view v)
    {
        return to_boolean(v);
    }

    Expect<Brush>           brush(Context&c, std::string_view v)
    {
        auto x  = color(c,v);
        if(!x)
            return unexpected(x.error());
        return Brush{ *x };
    }

    Expect<Color>           color(Context&c, std::string_view v)
    {
        Color               ret{ std::string(v) };
        std::string_view    clr = c.color(ret.def);
        if(!clr.empty())
            ret.def     = std::string(clr);
        return ret;
    }

    Expect<CoordN>              coord(Context&c, std::string_view v)
    {
        std::error_code ec;
        CoordN      ret;
        vsplit(v, ',', [&](std::string_view s){
            if(ec != std::error_code()) 
                return;
            if(s.empty())
                return;
            Expect<int>     x   = integer(c,s);
            if(!x){
                ec  = x.error();
            } else {
                ret.indices.push_back(*x);
            }
        });
        if(ec != std::error_code()) 
            return unexpected(ec);
        return ret;
    }
    
    Expect<Coord2I>             coord2(Context&c, std::string_view v)
    {
        auto x  = coord(c, v);
        if(!x)
            return unexpected(x.error());
        return (Coord2I) *x;
    }
    
    Expect<Coord3I>             coord3(Context&c, std::string_view v)
    {
        auto x  = coord(c, v);
        if(!x)
            return unexpected(x.error());
        return (Coord3I) *x;
    }

    Expect<CountN>              count(Context&c, std::string_view v)
    {
        std::error_code ec;
        CountN      ret;
        vsplit(v, ',', [&](std::string_view s){
            if(ec != std::error_code()) 
                return;
            if(s.empty())
                return;
            Expect<int>     x   = integer(c,s);
            if(!x){
                ec  = x.error();
            } else {
                ret.axes.push_back(*x);
            }
        });
        if(ec != std::error_code()) 
            return unexpected(ec);
        return ret;
    }

    Expect<Font>            font(Context&c, std::string_view v)
    {
        Font    ret;
        auto bits = split(v,',');
        if(bits.size() > 0)
            ret.family    = std::string(bits[0]);
        if(bits.size() > 1){
            auto x = real(c,bits[1]);
            if(!x)
                return unexpected(x.error());
            ret.size    = *x;
        }
        return ret;
    }

    Expect<int>                 integer(Context&, std::string_view v)
    {
        return to_integer(v);
    }

    Expect<IntegerSet>          integer_set(Context&c, std::string_view v)
    {
        std::error_code ec;
        IntegerSet      ret;
        vsplit(v, ',', [&](std::string_view s){
            if(ec != std::error_code()) 
                return;
            if(s.empty())
                return;
            Expect<int>     x   = integer(c,s);
            if(!x){
                ec  = x.error();
            } else {
                ret.insert(*x);
            }
        });
        if(ec != std::error_code()) 
            return unexpected(ec);
        return ret;
    }

    Expect<double>          length(Context&c, std::string_view v)
    {
        size_t n;
        for(n=v.size()-1;n>=0; --n)
            if(!is_alpha(v[n]))
                break;

        if(n < v.size()-1){
            std::string         unit(v.substr(n+1));
            std::string_view    value   = v.substr(0,n);
            
            const double*       u       = c.unit(unit);
            if(!u)
                return unexpected<"unit not recognized">();
            
            auto x  = to_double(value);
            if(!x)
                return unexpected(x.error());
            return *u * *x;
        } else {
            return to_double(v);
        }
    }
    
    Expect<Pen>             pen(Context&c, std::string_view v)
    {
        Pen ret;
        auto bits   = split(v, '/');
        if(bits.size() > 0){
            auto x = color(c,bits[0]);
            if(!x)
                return unexpected(x.error());
            ret.color   = *x;
        }
        if(bits.size() > 1){
            auto x  = real(c,bits[1]);
            if(!x)
                return unexpected(x.error());
            ret.width   = *x;
        }
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
            } else
                return unexpected<"style not recognized">();
        }
        return ret;
    }

    Expect<PointN>          point(Context& c, std::string_view v)
    {
        std::error_code ec;
        PointN      ret;
        vsplit(v, ',', [&](std::string_view s){
            if(ec != std::error_code()) 
                return;
            if(s.empty())
                return;
            Expect<int>     x   = length(c,s);
            if(!x){
                ec  = x.error();
            } else {
                ret.axes.push_back(*x);
            }
        });
        if(ec != std::error_code()) 
            return unexpected(ec);
        return ret;
    }

    Expect<Vector2D>        point2(Context&c, std::string_view v)
    {
        auto x  = point(c, v);
        if(!x)
            return unexpected(x.error());
        return (Vector2D) *x;
    }
    
    Expect<Vector3D>        point3(Context&c, std::string_view v)
    {
        auto x  = point(c, v);
        if(!x)
            return unexpected(x.error());
        return (Vector3D) *x;
    }

    Expect<double>              real(Context&, std::string_view v)
    {
        return to_double(v);
    }
    
    Expect<SizeN>               size(Context&c, std::string_view v)
    {
        std::error_code ec;
        SizeN      ret;
        vsplit(v, ',', [&](std::string_view s){
            if(ec != std::error_code()) 
                return;
            if(s.empty())
                return;
            Expect<int>     x   = length(c,s);
            if(!x){
                ec  = x.error();
            } else {
                ret.axes.push_back(*x);
            }
        });
        if(ec != std::error_code()) 
            return unexpected(ec);
        return ret;
    }

    Expect<Size2D>        size2(Context&c, std::string_view v)
    {
        auto x  = size(c, v);
        if(!x)
            return unexpected(x.error());
        return (Size2D) *x;
    }
    
    Expect<Size3D>        size3(Context&c, std::string_view v)
    {
        auto x  = size(c, v);
        if(!x)
            return unexpected(x.error());
        return (Size3D) *x;
    }

    Expect<StringSet>       string_set(Context&, std::string_view v)
    {
        StringSet       ret;
        vsplit(v, ',', [&](std::string_view s){
            ret.insert(std::string(trimmed(s)));
        });
        return ret;
    }
    
    Expect<VectorN>         vector(Context&c, std::string_view v)
    {
        std::error_code ec;
        VectorN      ret;
        vsplit(v, ',', [&](std::string_view s){
            if(ec != std::error_code()) 
                return;
            if(s.empty())
                return;
            Expect<int>     x   = real(c,s);
            if(!x){
                ec  = x.error();
            } else {
                ret.axes.push_back(*x);
            }
        });
        if(ec != std::error_code()) 
            return unexpected(ec);
        return ret;
    }

    Expect<Vector2D>        vector2(Context&c, std::string_view v)
    {
        auto x  = vector(c, v);
        if(!x)
            return unexpected(x.error());
        return (Vector2D) *x;
    }
    
    Expect<Vector3D>        vector3(Context&c, std::string_view v)
    {
        auto x  = vector(c, v);
        if(!x)
            return unexpected(x.error());
        return (Vector3D) *x;
    }
}
