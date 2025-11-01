////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/DObjectMetaWriter.hpp>
#include <doodle/Camera.hpp>

namespace yq::doodle {
    template <typename T>
    class CameraMeta::Writer : public DObjectMeta::Writer<T> {
    public:
        Writer(CameraMeta* cInfo) : DObjectMeta::Writer<T>(cInfo)
        {
        }
        
        Writer(CameraMeta& cInfo) : Writer(&cInfo)
        {
        }
    };
}
