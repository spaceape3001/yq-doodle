////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <b3/typedef.hpp>
#include <yq/container/StringMap.hpp>

namespace yq::b3 {
    class Context {
    public:
    
        void                color(const std::string&, const std::string&);
        std::string_view    color(const std::string& k) const;

        void                unit(const std::string&, double);
        double              unit(const std::string& k) const;

        void                style(const std::string&, Style*);
        const Style*        style(const std::string& k) const;
    
    private:
        StringMap       m_colors;
        DoubleMap       m_units;
        StyleMap        m_styles;
    };
}
