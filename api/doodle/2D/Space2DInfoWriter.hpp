////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/SpaceInfoWriter.hpp>
#include <doodle/2D/Space2D.hpp>

namespace yq::doodle {
    template <typename T>
    class Space2DInfo::Writer : public SpaceInfo::Writer<T> {
    public:
        Writer(Space2DInfo* mInfo) : SpaceInfo::Writer<T>(mInfo)
        {
        }
        
        Writer(Space2DInfo& mInfo) : Writer(&mInfo)
        {
        }
    };
}
