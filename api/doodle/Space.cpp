////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Space.hpp"
#include "SpaceInfoWriter.hpp"

YQ_OBJECT_IMPLEMENT(yq::doodle::Space)

namespace yq::doodle {
    SpaceInfo::SpaceInfo(std::string_view zName, DObjectInfo& base, const std::source_location& sl) : DObjectInfo(zName, base, sl)
    {
        set(Flag::D2);
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    void Space::init_meta()
    {
        auto w = writer<Space>();
        w.description("Space");
    }
        
    Space::Space(Project&prj) : DObject(prj)
    {
    }
    
    Space::Space(CopyAPI&api, const Space&cp) : DObject(api, cp)
    {
    }

    Space::~Space()
    {
    }


    //! Remap IDs/pointers appropriately
    void        Space::remap(const Remapper&rMap)
    {
        DObject::remap(rMap);
    }
}

