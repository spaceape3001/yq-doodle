////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/doodle/DObjectMetaWriter.hpp>
#include <yq/doodle/Camera.hpp>

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
