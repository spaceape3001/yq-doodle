////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/SpaceMetaWriter.hpp>
#include <doodle/space/Space2D.hpp>

namespace yq::doodle {
    template <typename T>
    class Space2DMeta::Writer : public SpaceMeta::Writer<T> {
    public:
        Writer(Space2DMeta* mMeta) : SpaceMeta::Writer<T>(mMeta)
        {
        }
        
        Writer(Space2DMeta& mMeta) : Writer(&mMeta)
        {
        }
    };
}
