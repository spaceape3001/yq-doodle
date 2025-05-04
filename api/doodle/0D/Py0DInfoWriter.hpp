////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/0D/Py0D.hpp>
#include <doodle/PyInfoWriter.hpp>

namespace yq::doodle {
    template <typename T>
    class Py0DInfo::Writer : public PyInfo::Writer<T> {
    public:
        Writer(Py0DInfo* pInfo) : PyInfo::Writer<T>(pInfo)
        {
        }
        
        Writer(Py0DInfo& pInfo) : Writer(&pInfo)
        {
        }
    };
}
