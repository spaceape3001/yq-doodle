////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <functional>
#include <vector>
#include <variant>

namespace yq::doodle {
    class Project;

    struct ID;

    using IDVector      = std::vector<ID>;

    using IDProviderV   = std::function<IDVector()>;
    using IDProviderP   = std::function<IDVector(const Project&)>;
    using IDProviderPI  = std::function<IDVector(const Project&,ID)>;
    
    using IDProvider    = std::variant<std::monostate, IDProviderV, IDProviderP, IDProviderPI>;
}
