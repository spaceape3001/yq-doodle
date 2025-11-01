////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "TileGroup.hpp"
#include <yq/b3/ObjMetaWriter.hpp>

YQ_OBJECT_IMPLEMENT(yq::b3::TileGroup)

namespace yq::b3 {
    TileGroup::TileGroup(const Param & p) : Frame(p)
    {
    }
    
    TileGroup::~TileGroup()
    {
    }
}
