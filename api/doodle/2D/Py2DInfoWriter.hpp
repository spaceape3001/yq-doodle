////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/2D/Py2D.hpp>
#include <doodle/PyInfoWriter.hpp>

namespace yq::doodle {
    template <typename T>
    class Py2DInfo::Writer : public PyInfo::Writer<T> {
    public:
        Writer(Py2DInfo* pInfo) : PyInfo::Writer<T>(pInfo)
        {
        }
        
        Writer(Py2DInfo& pInfo) : Writer(&pInfo)
        {
        }
    };
}
