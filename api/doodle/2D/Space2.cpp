////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Space2.hpp"
#include "Space2InfoWriter.hpp"

YQ_OBJECT_IMPLEMENT(yq::doodle::Space2)

namespace yq::doodle {
    Space2Info::Space2Info(std::string_view zName, SpaceInfo& base, const std::source_location& sl) : SpaceInfo(zName, base, sl)
    {
        set(Flag::SPACE);
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    void Space2::init_info()
    {
        auto w = writer<Space2>();
        w.description("Space in 2D");
    }

    Space2::Space2(Project&prj) : Space(prj)
    {
    }
    
    Space2::Space2(Project&prj, const Space2&cp) : Space(prj, cp)
    {
    }

    Space2::~Space2()
    {
    }


    //! Remap IDs/pointers appropriately
    void        Space2::remap(const Remapper&rMap)
    {
        Space::remap(rMap);
    }
}

