////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/3D/Py3.hpp>
#include <doodle/PyInfoWriter.hpp>

namespace yq::doodle {
    template <typename T>
    class Py3Info::Writer : public PyInfo::Writer<T> {
    public:
        Writer(Py3Info* pInfo) : PyInfo::Writer<T>(pInfo)
        {
        }
        
        Writer(Py3Info& pInfo) : Writer(&pInfo)
        {
        }
    };
}
