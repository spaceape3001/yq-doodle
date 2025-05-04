////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/4D/Py4D.hpp>
#include <doodle/PyInfoWriter.hpp>

namespace yq::doodle {
    template <typename T>
    class Py4DInfo::Writer : public PyInfo::Writer<T> {
    public:
        Writer(Py4DInfo* pInfo) : PyInfo::Writer<T>(pInfo)
        {
        }
        
        Writer(Py4DInfo& pInfo) : Writer(&pInfo)
        {
        }
    };
}
