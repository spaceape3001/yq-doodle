////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Space1D.hpp"
#include "Space1DInfoWriter.hpp"

YQ_OBJECT_IMPLEMENT(yq::doodle::Space1D)

namespace yq::doodle {
    Space1DInfo::Space1DInfo(std::string_view zName, SpaceInfo& base, const std::source_location& sl) : SpaceInfo(zName, base, sl)
    {
        set(Flag::SPACE);
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    void Space1D::init_info()
    {
        auto w = writer<Space1D>();
        w.description("Space in 1D");
    }

    Space1D::Space1D(Project&prj) : Space(prj)
    {
    }
    
    Space1D::Space1D(CopyAPI&api, const Space1D&cp) : Space(api, cp)
    {
    }

    Space1D::~Space1D()
    {
    }


    //! Remap IDs/pointers appropriately
    void        Space1D::remap(const Remapper&rMap)
    {
        Space::remap(rMap);
    }
}

