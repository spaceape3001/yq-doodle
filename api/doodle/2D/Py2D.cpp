////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Py2D.hpp"
#include "Py2DInfoWriter.hpp"
#include <doodle/strings.hpp>

YQ_OBJECT_IMPLEMENT(yq::doodle::Py2D)

namespace yq::doodle {
    Py2DInfo::Py2DInfo(std::string_view zName, PyInfo& base, const std::source_location& sl) : PyInfo(zName, base, sl)
    {
        set(Flag::D2);
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    void Py2D::init_info()
    {
        auto w = writer<Py2D>();
        w.description("Physical Object in 2D");
    }

    Py2D::Py2D(Project& prj) : Py(prj)
    {
    }
    
    Py2D::Py2D(Project& prj, const Py2D&cp) : Py(prj, cp)
    {
    }

    Py2D::~Py2D()
    {
    }

    //! Remap IDs/pointers appropriately
    void        Py2D::remap(const Remapper&rMap)
    {
        Py::remap(rMap);
    }

    std::string_view    Py2D::x() const
    {
        return attribute("x");
    }

    std::string_view    Py2D::y() const
    {
        return attribute("y");
    }
}

