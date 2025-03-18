////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/1D/Py1.hpp>
#include <doodle/PyInfoWriter.hpp>

namespace yq::doodle {
    template <typename T>
    class Py1Info::Writer : public PyInfo::Writer<T> {
    public:
        Writer(Py1Info* pInfo) : PyInfo::Writer<T>(pInfo)
        {
        }
        
        Writer(Py1Info& pInfo) : Writer(&pInfo)
        {
        }
    };
}
