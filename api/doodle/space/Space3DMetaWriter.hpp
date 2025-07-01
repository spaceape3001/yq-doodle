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
    class Space3DMeta::Writer : public SpaceMeta::Writer<T> {
    public:
        Writer(Space3DMeta* mMeta) : SpaceMeta::Writer<T>(mMeta)
        {
        }
        
        Writer(Space3DMeta& mMeta) : Writer(&mMeta)
        {
        }
    };
}
