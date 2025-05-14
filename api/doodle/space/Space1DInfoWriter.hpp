////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/SpaceInfoWriter.hpp>
#include <doodle/space/Space1D.hpp>

namespace yq::doodle {
    template <typename T>
    class Space1DInfo::Writer : public SpaceInfo::Writer<T> {
    public:
        Writer(Space1DInfo* mInfo) : SpaceInfo::Writer<T>(mInfo)
        {
        }
        
        Writer(Space1DInfo& mInfo) : Writer(&mInfo)
        {
        }
    };
}
