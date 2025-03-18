////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/0D/Py0.hpp>
#include <doodle/PyInfoWriter.hpp>

namespace yq::doodle {
    template <typename T>
    class Py0Info::Writer : public PyInfo::Writer<T> {
    public:
        Writer(Py0Info* pInfo) : PyInfo::Writer<T>(pInfo)
        {
        }
        
        Writer(Py0Info& pInfo) : Writer(&pInfo)
        {
        }
    };
}
