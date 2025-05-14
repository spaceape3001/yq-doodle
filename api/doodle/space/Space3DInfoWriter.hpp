////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/SpaceInfoWriter.hpp>
#include <doodle/space/Space3D.hpp>

namespace yq::doodle {
    template <typename T>
    class Space3DInfo::Writer : public SpaceInfo::Writer<T> {
    public:
        Writer(Space3DInfo* mInfo) : SpaceInfo::Writer<T>(mInfo)
        {
        }
        
        Writer(Space3DInfo& mInfo) : Writer(&mInfo)
        {
        }
    };
}
