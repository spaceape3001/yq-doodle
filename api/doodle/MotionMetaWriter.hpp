////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/DObjectMetaWriter.hpp>
#include <doodle/Motion.hpp>

namespace yq::doodle {
    template <typename T>
    class MotionMeta::Writer : public DObjectMeta::Writer<T> {
    public:
        Writer(MotionMeta* mInfo) : DObjectMeta::Writer<T>(mInfo)
        {
        }
        
        Writer(MotionMeta& mInfo) : Writer(&mInfo)
        {
        }
    };
}
