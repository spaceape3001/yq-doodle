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
        
        static void init_info();
        
        virtual uint8_t dimensions(count_k) const override;
                
        Point(Project&);
        Point(CopyAPI&, const Point&);
        ~Point();
        
        // Should always be valid (if defined), will default to empty otherwise
        std::string_view  x() const;

        // Should always be valid (if defined), will default to empty otherwise
        std::string_view  y() const;

        // Should always be valid (if defined), will default to empty otherwise
        std::string_view  z() const;

        // Should always be valid (if defined), will default to empty otherwise
        std::string_view  w() const;
    };
}
