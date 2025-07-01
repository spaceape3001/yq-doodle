////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/SpaceMetaWriter.hpp>
#include <doodle/space/Space1D.hpp>

namespace yq::doodle {
    template <typename T>
    class Space1DMeta::Writer : public SpaceMeta::Writer<T> {
    public:
        Writer(Space1DMeta* mMeta) : SpaceMeta::Writer<T>(mMeta)
        {
        }
        
        Writer(Space1DMeta& mMeta) : Writer(&mMeta)
        {
        }
    };
}
