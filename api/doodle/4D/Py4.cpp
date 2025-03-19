////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Py4.hpp"
#include "Py4InfoWriter.hpp"
#include <doodle/strings.hpp>

YQ_OBJECT_IMPLEMENT(yq::doodle::Py4)

namespace yq::doodle {
    Py4Info::Py4Info(std::string_view zName, PyInfo& base, const std::source_location& sl) : PyInfo(zName, base, sl)
    {
        set(Flag::D4);
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    void Py4::init_info()
    {
        auto w = writer<Py4>();
        w.description("Physical Object in 4D");
    }

    Py4::Py4(Project& prj) : Py(prj)
    {
    }
    
    Py4::Py4(Project& prj, const Py4&cp) : Py(prj, cp)
    {
    }

    Py4::~Py4()
    {
    }

    //! Remap IDs/pointers appropriately
    void        Py4::remap(const Remapper&rMap)
    {
        Py::remap(rMap);
    }

    std::string_view    Py4::x() const
    {
        return attribute("x");
    }

    std::string_view    Py4::y() const
    {
        return attribute("y");
    }
    
    std::string_view    Py4::z() const
    {
        return attribute("z");
    }
    
    std::string_view    Py4::w() const
    {
        return attribute("w");
    }

}

