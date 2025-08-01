////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "StdTerrain.hpp"
#include <b3/ObjMetaWriter.hpp>

YQ_OBJECT_IMPLEMENT(yq::b3::StdTerrain)

namespace yq::b3 {
    StdTerrain::StdTerrain(const std::filesystem::path& fp, const Param&p) : Terrain(fp, p)
    {
    }
    
    StdTerrain::~StdTerrain()
    {
    }
}
