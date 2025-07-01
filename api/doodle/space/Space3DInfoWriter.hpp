////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/SpaceMetaWriter.hpp>
#include <doodle/space/Space3D.hpp>

namespace yq::doodle {
    template <typename T>
    class Space3DInfo::Writer : public SpaceMeta::Writer<T> {
    public:
        Writer(Space3DInfo* mInfo) : SpaceMeta::Writer<T>(mInfo)
        {
        }
        
        Writer(Space3DInfo& mInfo) : Writer(&mInfo)
        {
        }
    };
}
