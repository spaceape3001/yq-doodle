////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/Py.hpp>

namespace yq::doodle {

    //! Position in space (can move, etc
    class Point : public Py {
        YQ_DOODLE_DECLARE(Point, Py)
    public:
        
        Point(Project&);
        Point(Project&, const Point&);
        ~Point();
    };
    
}
