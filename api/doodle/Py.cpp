////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Py.hpp"
#include "PyInfoWriter.hpp"

YQ_OBJECT_IMPLEMENT(yq::doodle::Py)

namespace yq::doodle {
    PyInfo::PyInfo(std::string_view zName, DObjectInfo& base, const std::source_location& sl) : 
        DObjectInfo(zName, base, sl)
    {
        set(Flag::PHYSICAL);
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    void Py::init_info()
    {
        auto w = writer<Py>();
        w.description("Physical Object");
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

    //! Remap IDs/pointers appropriately
    void        Py::remap(const Remapper&rMap)
    {
        DObject::remap(rMap);
    }
}

