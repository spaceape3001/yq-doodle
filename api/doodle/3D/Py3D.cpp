////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Py3D.hpp"
#include "Py3DInfoWriter.hpp"
#include <doodle/strings.hpp>

YQ_OBJECT_IMPLEMENT(yq::doodle::Py3D)

namespace yq::doodle {
    Py3DInfo::Py3DInfo(std::string_view zName, PyInfo& base, const std::source_location& sl) : PyInfo(zName, base, sl)
    {
        set(Flag::D3);
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    void Py3D::init_info()
    {
        auto w = writer<Py3D>();
        w.description("Physical Object in 3D");
    }

    Py3D::Py3D(Project& prj) : Py(prj)
    {
    }
    
    Py3D::Py3D(Project& prj, const Py3D&cp) : Py(prj, cp)
    {
    }

    Py3D::~Py3D()
    {
    }

    //! Remap IDs/pointers appropriately
    void        Py3D::remap(const Remapper&rMap)
    {
        Py::remap(rMap);
    }

    std::string_view    Py3D::x() const
    {
        return attribute("x");
    }

    std::string_view    Py3D::y() const
    {
        return attribute("y");
    }
    
    std::string_view    Py3D::z() const
    {
        return attribute("z");
    }
}

