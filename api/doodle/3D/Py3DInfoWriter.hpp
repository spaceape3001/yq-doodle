////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/3D/Py3D.hpp>
#include <doodle/PyInfoWriter.hpp>

namespace yq::doodle {
    template <typename T>
    class Py3DInfo::Writer : public PyInfo::Writer<T> {
    public:
        Writer(Py3DInfo* pInfo) : PyInfo::Writer<T>(pInfo)
        {
        }
        
        Writer(Py3DInfo& pInfo) : Writer(&pInfo)
        {
        }
    };
}
