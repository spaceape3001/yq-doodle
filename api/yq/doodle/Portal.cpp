////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Portal.hpp"
#include "PortalMetaWriter.hpp"

YQ_OBJECT_IMPLEMENT(yq::doodle::Portal)

namespace yq::doodle {
    PortalMeta::PortalMeta(std::string_view zName, DObjectMeta& base, const std::source_location& sl) : DObjectMeta(zName, base, sl)
    {
        set(Flag::D2);
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    void Portal::init_meta()
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

