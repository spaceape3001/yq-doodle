////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Py.hpp"
#include "PyInfoWriter.hpp"

YQ_DOODLE_IMPLEMENT(yq::doodle::Py)

namespace yq::doodle {
    PyInfo::PyInfo(std::string_view zName, DObjectInfo& base, const std::source_location& sl) : 
        DObjectInfo(zName, base, sl)
    {
        set(Flag::PHYSICAL);
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    void Py::init_meta()
    {
        auto w = writer<Py>();
        w.description("Physical Object");
        w.attribute("a", "atan2d(y,x)");
        w.attribute("ang", "atan2d(y,x)");
        w.attribute("az", "atan2d(x,y)");
        w.attribute("el", "atan2d(z,sqrt(x^2+y^2))");
        w.attribute("rz", &Py::rz);
        w.attribute("th", "atan2(y,x)");
        w.attribute("x", &Py::x);
        w.attribute("y", &Py::y);
        w.attribute("z", &Py::z);
    }

    Py::Py(Project& prj) : DObject(prj)
    {
    }
    
    Py::Py(CopyAPI& api, const Py&cp) : DObject(api, cp)
    {
    }

    Py::~Py()
    {
    }

    bool    Py::supports(dimensions_k, uint8_t n) const
    {
        return n <= dimensions(COUNT);
    }

    //! Remap IDs/pointers appropriately
    void        Py::remap(const Remapper&rMap)
    {
        DObject::remap(rMap);
    }

    std::string_view  Py::rz() const
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

    std::string_view  Py::x() const
    {
        if(m_values.size() >= 1)
            return m_values[0];
        
        auto& data  = m_attributes.data();
        if(auto i = data.find("x"); i != data.end())
            return i->second;
        if(is_attribute(LOCAL, "Δx"))
            return "_parent_.x+Δx";
        
        if(is_attribute(LOCAL, "rz")){
            if(is_attribute(LOCAL, "ang"))
                return "rz*cosd(ang)";
            if(is_attribute(LOCAL, "a"))
                return "rz*cosd(a)";
            if(is_attribute(LOCAL, "th"))
                return "rz*cos(th)";
            if(is_attribute(LOCAL, "az")){
                if(is_attribute(LOCAL, "el")){
                    return "rz*sind(az)*cosd(el)";
                } else {
                    return "rz*sind(az)";
                }
            }
        } 
        return "";
    }

    std::string_view  Py::y() const
    {
        if(m_values.size() >= 2)
            return m_values[1];

        auto& data  = m_attributes.data();
        if(auto i = data.find("y"); i != data.end())
            return i->second;
        if(is_attribute(LOCAL, "Δy"))
            return "_parent_.y+Δy";
        
        if(is_attribute(LOCAL, "rz")){
            if(is_attribute(LOCAL, "ang"))
                return "rz*sind(ang)";
            if(is_attribute(LOCAL, "a"))
                return "rz*sind(a)";
            if(is_attribute(LOCAL, "th"))
                return "rz*sin(th)";
            if(is_attribute(LOCAL, "az")){
                if(is_attribute(LOCAL, "el")){
                    return "rz*cosd(az)*cosd(el)";
                } else {
                    return "rz*cosd(az)";
                }
            }
        } 
        return "";
    }

    std::string_view  Py::z() const
    {
        if(m_values.size() >= 3)
            return m_values[2];
        
        auto& data  = m_attributes.data();
        if(auto i = data.find("z"); i != data.end())
            return i->second;

        if(is_attribute(LOCAL, "Δz"))
            return "_parent_.z+Δz";

        if(is_attribute(LOCAL, "r") && is_attribute(LOCAL, "el")){
            return "rz*sind(el)";
        }
        
        return "";
    }
}

