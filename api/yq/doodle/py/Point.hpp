////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/doodle/Py.hpp>

namespace yq::doodle {

    /*! Position in space (can move, etc)
    */
    class Point : public Py {
        YQ_DOODLE_DECLARE(Point, Py)
    public:
        
        static void init_meta();
        
        virtual uint8_t dimensions(count_k) const override;
                
        Point(Project&);
        Point(CopyAPI&, const Point&);
        ~Point();
    };
}
