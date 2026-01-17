////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/b3/typedef.hpp>
#include <yq/b3fmt/context.hpp>
#include <yq/container/StringMap.hpp>

namespace yq::b3 {
    class Context : public parse::context_t {
    public:
    
        using parse::context_t::color;
        void                color(const std::string&, const std::string&);
        //std::string_view    color(const std::string& k) const;

        using parse::context_t::unit;
        void                unit(const std::string&, double);
        //double              unit(const std::string& k) const;

        void                style(const std::string&, Style*);
        const Style*        style(const std::string& k) const;
    
    private:
        StyleMap        m_styles;
    };
}
