////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/4D/Py4.hpp>
#include <doodle/PyInfoWriter.hpp>

namespace yq::doodle {
    template <typename T>
    class Py4Info::Writer : public PyInfo::Writer<T> {
    public:
        Writer(Py4Info* pInfo) : PyInfo::Writer<T>(pInfo)
        {
        }
        
        Writer(Py4Info& pInfo) : Writer(&pInfo)
        {
        }
    };
}
