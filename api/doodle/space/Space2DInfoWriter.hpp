////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/SpaceMetaWriter.hpp>
#include <doodle/space/Space2D.hpp>

namespace yq::doodle {
    template <typename T>
    class Space2DInfo::Writer : public SpaceMeta::Writer<T> {
    public:
        Writer(Space2DInfo* mInfo) : SpaceMeta::Writer<T>(mInfo)
        {
        }
        
        Writer(Space2DInfo& mInfo) : Writer(&mInfo)
        {
        }
    };
}
