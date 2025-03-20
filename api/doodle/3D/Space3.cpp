////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Space3.hpp"
#include "Space3InfoWriter.hpp"

YQ_OBJECT_IMPLEMENT(yq::doodle::Space3)

namespace yq::doodle {
    Space3Info::Space3Info(std::string_view zName, SpaceInfo& base, const std::source_location& sl) : SpaceInfo(zName, base, sl)
    {
        set(Flag::SPACE);
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    void Space3::init_info()
    {
        auto w = writer<Space3>();
        w.description("Space in 3D");
    }

    Space3::Space3(Project&prj) : Space(prj)
    {
    }
    
    Space3::Space3(Project&prj, const Space3&cp) : Space(prj, cp)
    {
    }

    Space3::~Space3()
    {
    }


    //! Remap IDs/pointers appropriately
    void        Space3::remap(const Remapper&rMap)
    {
        Space::remap(rMap);
    }
}

