////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "context.hpp"

namespace yq::b3 {
    std::string_view  Context::color(const std::string&s) const
    {
        auto i = colors.find(s);
        if(i == colors.end())
            return {};
        return i->second;
    }

    const double*     Context::unit(const std::string&s) const
    {
        auto i = units.find(s);
        if(i == units.end()) 
            return nullptr;
        return &(i->second);
    }
}

