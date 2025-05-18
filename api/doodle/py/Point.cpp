////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Point.hpp"
#include <doodle/PyInfoWriter.hpp>
#include <algorithm>

YQ_DOODLE_IMPLEMENT(yq::doodle::Point)

namespace yq::doodle {
    void Point::init_info()
    {
        auto w = writer<Point>();
        w.description("Point");
        w.attribute("x", &Point::x);
        w.attribute("y", &Point::y);
        w.attribute("z", &Point::z);
        w.attribute("w", &Point::w);
    }

    uint8_t Point::dimensions(count_k) const
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

                
    Point::Point(Project& prj) : Py(prj)
    {
    }
    
    Point::Point(CopyAPI& api, const Point& cp) : Py(api, cp)
    {
    }
    
    Point::~Point()
    {
    }

    std::string_view  Point::w() const
    {
        if(m_values.size() >= 4)
            return m_values[3];
            
        auto& data  = m_attributes.data();
        if(auto i = data.find("w"); i != data.end())
            return i->second;

        return "";
    }

    std::string_view  Point::x() const
    {
        if(m_values.size() >= 1)
            return m_values[0];
        
        auto& data  = m_attributes.data();
        if(auto i = data.find("x"); i != data.end())
            return i->second;
        
        if(is_attribute(LOCAL, "r")){
            if(is_attribute("ang"))
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

    std::string_view  Point::y() const
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

    std::string_view  Point::z() const
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
