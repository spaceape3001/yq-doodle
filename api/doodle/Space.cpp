////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Space.hpp"
#include "SpaceMetaWriter.hpp"

YQ_OBJECT_IMPLEMENT(yq::doodle::Space)

namespace yq::doodle {
    SpaceMeta::SpaceMeta(std::string_view zName, DObjectMeta& base, const std::source_location& sl) : DObjectMeta(zName, base, sl)
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

