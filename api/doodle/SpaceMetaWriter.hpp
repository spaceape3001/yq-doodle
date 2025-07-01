////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/DObjectMetaWriter.hpp>
#include <doodle/Space.hpp>

namespace yq::doodle {
    template <typename T>
    class SpaceMeta::Writer : public DObjectMeta::Writer<T> {
    public:
        Writer(SpaceMeta* mInfo) : DObjectMeta::Writer<T>(mInfo)
        {
        }
        
        Writer(SpaceMeta& mInfo) : Writer(&mInfo)
        {
        }
    };
}
