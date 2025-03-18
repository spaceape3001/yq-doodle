////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/2D/Py2.hpp>
#include <doodle/PyInfoWriter.hpp>

namespace yq::doodle {
    template <typename T>
    class Py2Info::Writer : public PyInfo::Writer<T> {
    public:
        Writer(Py2Info* pInfo) : PyInfo::Writer<T>(pInfo)
        {
        }
        
        Writer(Py2Info& pInfo) : Writer(&pInfo)
        {
        }
    };
}
