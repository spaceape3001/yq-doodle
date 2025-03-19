////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/DObjectInfoWriter.hpp>
#include <doodle/Motion.hpp>

namespace yq::doodle {
    template <typename T>
    class MotionInfo::Writer : public DObjectInfo::Writer<T> {
    public:
        Writer(MotionInfo* mInfo) : DObjectInfo::Writer<T>(mInfo)
        {
        }
        
        Writer(MotionInfo& mInfo) : Writer(&mInfo)
        {
        }
    };
}
