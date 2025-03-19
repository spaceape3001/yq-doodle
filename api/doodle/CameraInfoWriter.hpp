////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/DObjectInfoWriter.hpp>
#include <doodle/Camera.hpp>

namespace yq::doodle {
    template <typename T>
    class CameraInfo::Writer : public DObjectInfo::Writer<T> {
    public:
        Writer(CameraInfo* cInfo) : DObjectInfo::Writer<T>(cInfo)
        {
        }
        
        Writer(CameraInfo& cInfo) : Writer(&cInfo)
        {
        }
    };
}
