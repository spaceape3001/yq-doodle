////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/doodle/DObjectMetaWriter.hpp>
#include <yq/doodle/Light.hpp>

namespace yq::doodle {

    template <typename T>
    class LightMeta::Writer : public DObjectMeta::Writer<T> {
    public:
        Writer(LightMeta* lInfo) : DObjectMeta::Writer<T>(lInfo)
        {
        }
        
        Writer(LightMeta& lInfo) : Writer(&lInfo)
        {
        }
    };

}
