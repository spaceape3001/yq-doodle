////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/1D/Py1D.hpp>
#include <doodle/PyInfoWriter.hpp>

namespace yq::doodle {
    template <typename T>
    class Py1DInfo::Writer : public PyInfo::Writer<T> {
    public:
        Writer(Py1DInfo* pInfo) : PyInfo::Writer<T>(pInfo)
        {
        }
        
        Writer(Py1DInfo& pInfo) : Writer(&pInfo)
        {
        }
    };
}
