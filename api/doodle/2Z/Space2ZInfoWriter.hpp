////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/SpaceInfoWriter.hpp>
#include <doodle/space/Space2Z.hpp>

namespace yq::doodle {
    template <typename T>
    class Space2ZInfo::Writer : public SpaceInfo::Writer<T> {
    public:
        Writer(Space2ZInfo* mInfo) : SpaceInfo::Writer<T>(mInfo)
        {
        }
        
        Writer(Space2ZInfo& mInfo) : Writer(&mInfo)
        {
        }
    };
}
