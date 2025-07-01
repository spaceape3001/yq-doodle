////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/SpaceMetaWriter.hpp>
#include <doodle/space/Space1D.hpp>

namespace yq::doodle {
    template <typename T>
    class Space1DInfo::Writer : public SpaceMeta::Writer<T> {
    public:
        Writer(Space1DInfo* mInfo) : SpaceMeta::Writer<T>(mInfo)
        {
        }
        
        Writer(Space1DInfo& mInfo) : Writer(&mInfo)
        {
        }
    };
}
