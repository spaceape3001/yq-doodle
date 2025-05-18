////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Curve.hpp"
#include <doodle/PyInfoWriter.hpp>
#include <algorithm>

YQ_DOODLE_IMPLEMENT(yq::doodle::Curve)

namespace yq::doodle {
    void Curve::init_info()
    {
        auto w = writer<Curve>();
        w.description("Curve");
        w.attribute("a", "atan2d(y,x)");
        w.attribute("ang", "atan2d(y,x)");
        w.attribute("az", "atan2d(x,y)");
        w.attribute("el", "atan2d(z,sqrt(x^2+y^2))");
        w.attribute("r", &Curve::r);
        w.attribute("th", "atan2(y,x)");
        w.attribute("s", "0.");         // need the default here
        w.attribute("s0", "0.");
        w.attribute("s1", "1.");
        w.attribute("x", &Curve::x);
        w.attribute("y", &Curve::y);
        w.attribute("z", &Curve::z);
        w.attribute("w", &Curve::w);
    }

    uint8_t Curve::dimensions(count_k) const
    {
        size_t  m   = values(COUNT);
        if(m>=255)
            return 0xFF;
        uint8_t n   = (uint8_t) m;
        if(is_attribute("x"))
            n = std::min(n,(uint8_t) 1);
        if(is_attribute("y"))
            n = std::min(n,(uint8_t) 2);
        if(is_attribute("z"))
            n = std::min(n,(uint8_t) 3);
        if(is_attribute("w"))
            n = std::min(n,(uint8_t) 4);
        if(is_attribute("ang"))
            n = std::min(n,(uint8_t) 2);
        if(is_attribute("a"))
            n = std::min(n,(uint8_t) 2);
        if(is_attribute("az"))
            n = std::min(n,(uint8_t) 2);
        if(is_attribute("el"))
            n = std::min(n,(uint8_t) 3);
        if(is_attribute("lat"))
            n = std::min(n,(uint8_t) 2);
        if(is_attribute("lon"))
            n = std::min(n,(uint8_t) 3);
        if(is_attribute("alt"))
            n = std::min(n,(uint8_t) 2);
        if(is_attribute("th"))
            n = std::min(n,(uint8_t) 2);
        return n;
    }

                
    Curve::Curve(Project& prj) : Py(prj)
    {
    }
    
    Curve::Curve(CopyAPI& api, const Curve& cp) : Py(api, cp)
    {
    }
    
    Curve::~Curve()
    {
    }

    std::string_view  Curve::r() const
    {
        switch(dimensions(COUNT)){
        case 0:
            return "0";
        case 1:
            return "abs(x)";
        case 2:
            return "sqrt(x^2+y^2)";
        case 3:
            return "sqrt(x^2+y^2+z^2)";
        case 4:
            return "sqrt(x^2+y^2+z^2+w^2)";
        default:
            return "0";
        }
    }

    std::string_view  Curve::w() const
    {
        if(m_values.size() >= 4)
            return m_values[3];
            
        auto& data  = m_attributes.data();
        if(auto i = data.find("w"); i != data.end())
            return i->second;

        return "";
    }

    std::string_view  Curve::x() const
    {
        if(m_values.size() >= 1)
            return m_values[0];
        
        auto& data  = m_attributes.data();
        if(auto i = data.find("x"); i != data.end())
            return i->second;
        
        if(is_attribute(LOCAL, "r")){
            if(is_attribute(LOCAL, "ang"))
                return "r*cosd(ang)";
            if(is_attribute(LOCAL, "a"))
                return "r*cosd(a)";
            if(is_attribute(LOCAL, "th"))
                return "r*cos(th)";
            if(is_attribute(LOCAL, "az")){
                if(is_attribute(LOCAL, "el")){
                    return "r*sind(az)*cosd(el)";
                } else {
                    return "r*sind(az)";
                }
            }
        } 
        return "";
    }

    std::string_view  Curve::y() const
    {
        if(m_values.size() >= 2)
            return m_values[1];

        auto& data  = m_attributes.data();
        if(auto i = data.find("y"); i != data.end())
            return i->second;
        
        if(is_attribute(LOCAL, "r")){
            if(is_attribute(LOCAL, "ang"))
                return "r*sind(ang)";
            if(is_attribute(LOCAL, "a"))
                return "r*sind(a)";
            if(is_attribute(LOCAL, "th"))
                return "r*sin(th)";
            if(is_attribute(LOCAL, "az")){
                if(is_attribute(LOCAL, "el")){
                    return "r*cosd(az)*cosd(el)";
                } else {
                    return "r*cosd(az)";
                }
            }
        } 
        return "";
    }

    std::string_view  Curve::z() const
    {
        if(m_values.size() >= 3)
            return m_values[2];
        
        auto& data  = m_attributes.data();
        if(auto i = data.find("z"); i != data.end())
            return i->second;

        if(is_attribute(LOCAL, "r") && is_attribute(LOCAL, "el")){
            return "r*sind(el)";
        }
        
        return "";
    }

}
