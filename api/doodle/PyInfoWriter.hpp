////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/DObjectInfoWriter.hpp>
#include <doodle/Py.hpp>

namespace yq::doodle {

    template <typename T>
    class PyInfo::Writer : public DObjectInfo::Writer<T> {
    public:
        Writer(PyInfo* pInfo) : DObjectInfo::Writer<T>(pInfo)
        {
        }
        
        Writer(PyInfo& pInfo) : Writer(&pInfo)
        {
        }
    };
}
