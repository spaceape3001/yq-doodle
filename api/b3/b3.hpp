////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/*
    B3 is intended to be "lightweight" and more geared for processing.  
    We'll see which wins....
*/

namespace yq::b3 {
    struct ArgList {
    };
    
    struct ArgMap {
    };

    struct B3 {
        std::string         cmd;
        
        std::vector<B3>     children;
    };
}
