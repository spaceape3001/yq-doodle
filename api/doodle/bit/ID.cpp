////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "ID.hpp"

#include <yq/core/DelayInit.hpp>
#include <yq/meta/TypeMetaWriter.hpp>
#include <yq/meta/Init.hpp>

namespace yq::doodle {
    static void reg_id()
    {
        auto w = writer<ID>();
        w.description("Identifier");
    }
    
    YQ_INVOKE(reg_id();)
}

YQ_TYPE_IMPLEMENT(yq::doodle::ID)
