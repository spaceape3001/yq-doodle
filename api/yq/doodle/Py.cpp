////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Py.hpp"
#include "PyMetaWriter.hpp"

YQ_DOODLE_IMPLEMENT(yq::doodle::Py)

namespace yq::doodle {
    PyMeta::PyMeta(std::string_view zName, DObjectMeta& base, const std::source_location& sl) : 
        DObjectMeta(zName, base, sl)
    {
        set(Flag::PHYSICAL);
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    void Py::init_meta()
    {
        auto w = writer<Py>();
        w.description("Physical Object");
        w.attribute("ang", "atan2d(y,x)");
        w.attribute("az", "atan2d(y,x)");
        w.attribute("el", "atan2d(z,sqrt(x^2+y^2))");
        w.attribute("r", &Py::r);
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

    std::string_view  Py::r() const
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
        
        if(auto i = m_attributes.find("x"); i != m_attributes.end())
            return i->second;
        if(is_attribute(LOCAL, "Δx"))
            return "_parent_.x+Δx";
        if(is_attribute(LOCAL, "dx"))
            return "_parent_.x+dx";
        
        if(is_attribute(LOCAL, "r")){
            if(is_attribute(LOCAL, "ang"))
                return "r*cosd(ang)";
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

    std::string_view  Py::y() const
    {
        if(m_values.size() >= 2)
            return m_values[1];

        if(auto i = m_attributes.find("y"); i != m_attributes.end())
            return i->second;
        if(is_attribute(LOCAL, "Δy"))
            return "_parent_.y+Δy";
        if(is_attribute(LOCAL, "dy"))
            return "_parent_.y+dy";
        
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

    std::string_view  Py::z() const
    {
        if(m_values.size() >= 3)
            return m_values[2];
        
        if(auto i = m_attributes.find("z"); i != m_attributes.end())
            return i->second;

        if(is_attribute(LOCAL, "Δz"))
            return "_parent_.z+Δz";
        if(is_attribute(LOCAL, "dz"))
            return "_parent_.z+dz";

        if(is_attribute(LOCAL, "r") && is_attribute(LOCAL, "el")){
            return "r*sind(el)";
        }
        
        return "";
    }
}

