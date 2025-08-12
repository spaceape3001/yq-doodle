////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/keywords.hpp>

namespace yq::art {
    struct doc_k {};
    struct dynamic_k {};    //< Note, may conflict in tachyon, will resolve later
    static constexpr const doc_k        DOC;
    static constexpr const dynamic_k    DYNAMIC;
}
