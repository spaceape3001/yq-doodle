////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/doodle/DObjectMetaWriter.hpp>
#include <yq/doodle/Py.hpp>

namespace yq::doodle {

    template <typename T>
    class PyMeta::Writer : public DObjectMeta::Writer<T> {
    public:
        Writer(PyMeta* pInfo) : DObjectMeta::Writer<T>(pInfo)
        {
        }
        
        Writer(PyMeta& pInfo) : Writer(&pInfo)
        {
        }
    };
}
