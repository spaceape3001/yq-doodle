////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/DObjectInfoWriter.hpp>
#include <doodle/Light.hpp>

namespace yq::doodle {

    template <typename T>
    class LightInfo::Writer : public DObjectInfo::Writer<T> {
    public:
        Writer(LightInfo* lInfo) : DObjectInfo::Writer<T>(lInfo)
        {
        }
        
        Writer(LightInfo& lInfo) : Writer(&lInfo)
        {
        }
    };

}
