////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "PointType.hpp"
#include <yq/text/match.hpp>

namespace yq::b3 {
    PointType           decode_point_type(std::string_view k)
    {
        if(is_similar(k,"1d"))
            return PointType::D1;
        else if(is_similar(k,"2d"))
            return PointType::D2;
        else if(is_similar(k,"3d"))
            return PointType::D3;
        else if(is_similar(k,"agl"))
            return PointType::AGL;
        else if(is_similar(k,"msl"))
            return PointType::MSL;
        else    
            return PointType::Unknown;
    }
    
    std::string_view    key_for(PointType pt)
    {
        switch(pt){
        case PointType::D1:
            return "1d";
        case PointType::D2:
            return "2d";
        case PointType::D3:
            return "3d";
        case PointType::AGL:
            return "agl";
        case PointType::MSL:
            return "msl";
        case PointType::Unknown:
            return "unk";
        default:
            return "???";
        }
    }
}

