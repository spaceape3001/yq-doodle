////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Context.hpp"

namespace yq::b3 {
    thread_local Context*    g_context = nullptr;
    
    void                Context::color(const std::string&k, const std::string&v)
    {
        m_colors[k] = v;
    }
    
    void                Context::unit(const std::string&k, double v)
    {
        m_units[k] = v;
    }

    void                Context::style(const std::string&k, Style*s)
    {
        m_styles[k]  = s;
    }
    
    const Style*        Context::style(const std::string& k) const
    {
        auto i = m_styles.find(k);
        if(i == m_styles.end())
            return nullptr;
        return i->second;
    }
}
