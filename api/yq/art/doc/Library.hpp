////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/art/doc/Doc.hpp>
#include <yq/shape/AxBox2.hpp>

namespace yq::art {
    class Library : public Doc {
        YQ_OBJECT_DECLARE(Library, Doc)
    public:
    
        static void init_meta();
        Library();
        virtual ~Library();
    };
}
