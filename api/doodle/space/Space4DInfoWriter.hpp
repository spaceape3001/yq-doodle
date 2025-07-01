////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/SpaceMetaWriter.hpp>
#include <doodle/space/Space4D.hpp>

namespace yq::doodle {
    template <typename T>
    class Space4DInfo::Writer : public SpaceMeta::Writer<T> {
    public:
        Writer(Space4DInfo* mInfo) : SpaceMeta::Writer<T>(mInfo)
        {
        }
        
        Writer(Space4DInfo& mInfo) : Writer(&mInfo)
        {
        }
    };
}
