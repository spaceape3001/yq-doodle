////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Portal.hpp"
#include "PortalInfoWriter.hpp"

YQ_OBJECT_IMPLEMENT(yq::doodle::Portal)

namespace yq::doodle {
    PortalInfo::PortalInfo(std::string_view zName, DObjectInfo& base, const std::source_location& sl) : DObjectInfo(zName, base, sl)
    {
        set(Flag::D2);
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    void Portal::init_info()
    {
        auto w = writer<Portal>();
        w.description("Portal");
    }
        
    Portal::Portal(Project&prj) : DObject(prj)
    {
    }
    
    Portal::Portal(Project&prj, const Portal&cp) : DObject(prj, cp)
    {
    }

    Portal::~Portal()
    {
    }


    //! Remap IDs/pointers appropriately
    void        Portal::remap(const Remapper&rMap)
    {
        DObject::remap(rMap);
    }
}

