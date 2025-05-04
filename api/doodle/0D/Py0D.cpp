////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Py0D.hpp"
#include "Py0DInfoWriter.hpp"

YQ_OBJECT_IMPLEMENT(yq::doodle::Py0D)

namespace yq::doodle {
    Py0DInfo::Py0DInfo(std::string_view zName, PyInfo& base, const std::source_location& sl) : PyInfo(zName, base, sl)
    {
        set(Flag::D0);
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    void Py0D::init_info()
    {
        auto w = writer<Py0D>();
        w.description("Physical Object in 0D");
    }

    Py0D::Py0D(Project& prj) : Py(prj)
    {
    }
    
    Py0D::Py0D(Project& prj, const Py0D&cp) : Py(prj, cp)
    {
    }

    Py0D::~Py0D()
    {
    }

    //! Remap IDs/pointers appropriately
    void        Py0D::remap(const Remapper&rMap)
    {
        Py::remap(rMap);
    }

}

