////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/SpaceInfoWriter.hpp>
#include <doodle/space/Space4D.hpp>

namespace yq::doodle {
    template <typename T>
    class Space4DInfo::Writer : public SpaceInfo::Writer<T> {
    public:
        Writer(Space4DInfo* mInfo) : SpaceInfo::Writer<T>(mInfo)
        {
        }
        
        Writer(Space4DInfo& mInfo) : Writer(&mInfo)
        {
        }
    };
}
