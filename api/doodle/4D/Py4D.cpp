////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Py4D.hpp"
#include "Py4DInfoWriter.hpp"
#include <doodle/strings.hpp>

YQ_OBJECT_IMPLEMENT(yq::doodle::Py4D)

namespace yq::doodle {
    Py4DInfo::Py4DInfo(std::string_view zName, PyInfo& base, const std::source_location& sl) : PyInfo(zName, base, sl)
    {
        set(Flag::D4);
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    void Py4D::init_info()
    {
        auto w = writer<Py4D>();
        w.description("Physical Object in 4D");
    }

    Py4D::Py4D(Project& prj) : Py(prj)
    {
    }
    
    Py4D::Py4D(Project& prj, const Py4D&cp) : Py(prj, cp)
    {
    }

    Py4D::~Py4D()
    {
    }

    //! Remap IDs/pointers appropriately
    void        Py4D::remap(const Remapper&rMap)
    {
        Py::remap(rMap);
    }

    std::string_view    Py4D::x() const
    {
        return attribute("x");
    }

    std::string_view    Py4D::y() const
    {
        return attribute("y");
    }
    
    std::string_view    Py4D::z() const
    {
        return attribute("z");
    }
    
    std::string_view    Py4D::w() const
    {
        return attribute("w");
    }

}

