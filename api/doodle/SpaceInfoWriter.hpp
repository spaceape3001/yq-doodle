////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/DObjectInfoWriter.hpp>
#include <doodle/Space.hpp>

namespace yq::doodle {
    template <typename T>
    class SpaceInfo::Writer : public DObjectInfo::Writer<T> {
    public:
        Writer(SpaceInfo* mInfo) : DObjectInfo::Writer<T>(mInfo)
        {
        }
        
        Writer(SpaceInfo& mInfo) : Writer(&mInfo)
        {
        }
    };
}
