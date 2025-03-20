////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/SpaceInfoWriter.hpp>
#include <doodle/2D/Space2.hpp>

namespace yq::doodle {
    template <typename T>
    class Space2Info::Writer : public SpaceInfo::Writer<T> {
    public:
        Writer(Space2Info* mInfo) : SpaceInfo::Writer<T>(mInfo)
        {
        }
        
        Writer(Space2Info& mInfo) : Writer(&mInfo)
        {
        }
    };
}
