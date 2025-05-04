////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Py1D.hpp"
#include "Py1DInfoWriter.hpp"

YQ_OBJECT_IMPLEMENT(yq::doodle::Py1D)

namespace yq::doodle {
    Py1DInfo::Py1DInfo(std::string_view zName, PyInfo& base, const std::source_location& sl) : PyInfo(zName, base, sl)
    {
        set(Flag::D1);
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    void Py1D::init_info()
    {
        auto w = writer<Py1D>();
        w.description("Physical Object in 1D");
    }

    Py1D::Py1D(Project& prj) : Py(prj)
    {
    }
    
    Py1D::Py1D(Project& prj, const Py1D&cp) : Py(prj, cp)
    {
    }

    Py1D::~Py1D()
    {
    }

    //! Remap IDs/pointers appropriately
    void        Py1D::remap(const Remapper&rMap)
    {
        Py::remap(rMap);
    }

    std::string_view    Py1D::x() const
    {
        return attribute("x");
    }

}

