////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "double.hpp"
#include <yq/meta/Init.hpp>
#include <yq/core/StreamOps.hpp>
#include <yq/text/format.hpp>
#include <yq/text/parse.hpp>
#include <yq/text/transform.hpp>

using namespace yq;
using namespace yq::doodle;

YQ_TYPE_IMPLEMENT(double_v)

namespace  {
    void print_double(Stream& str, const double_v& v)
    {
        if(auto p = std::get_if<double>(&v)){
            str << *p;
        } else if(auto p = std::get_if<std::string>(&)){
            str << *p;
        }
    }

    std::string_view    write_double(const double_v& v)
    {
        if(auto p = std::get_if<double>(&v))
            return to_string_view(*p);
        if(auto p = std::get_if<std::string_view>(&v))
            return *p;
        return "";
    }
    
    static bool parse_double(double_v& v, std::string_view s)
    {
        if(s.empty()){
            v   = {};
        } else if(auto dx = to_double(s)){
            v   = *dx;
        } else {
            v   = std::string(trimmed(s));
        }
        return true;
    }
}
