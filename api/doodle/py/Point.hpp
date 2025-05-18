////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/Py.hpp>

namespace yq::doodle {

    /*! Position in space (can move, etc)
    
        ## Attributes
    
        | Key | What                                    | Default                   |
        +-----+-----------------------------------------+---------------------------+
        | a   | CCW angle from +x axis (in degrees)     | atan2d(y,x)               |
        | ang | CCW angle from +x axis (in degrees)     | atan2d(y,x)               |
        | az  | CW angle from +y axis (in degrees)      | atan2d(x,y)               |
        | el  | angle upward (+z) from xy plane         | atan2d(z, sqrt(x^2+y^2))  |
        | r   | distance from origin                    | ...                       |
        | th  | CCW angle from +x axis (in radians)     | atan2(y,x)                |
        | w   | W-value (note, no convient override)    | (none)                    |
        | x   | X-value (this will OVERRIDE the trig)   | ...                       |
        | y   | Y-value (this will OVERRIDE the trig)   | ...                       |
        | z   | Z-value (this will OVERRIDE the trig)   | ...                       |
        
        For radius, the default assesses the number of dimensions, returns the 
        relevant geometric mean of x, y, z, and w.
        
        For x, y, z, w; the values are checked first and used.  
        If those are missing AND radius "r" is present, the default will return
        the appropriate trigonometry based function leveraging the present angle 
        attributes.
    */
    class Point : public Py {
        YQ_DOODLE_DECLARE(Point, Py)
    public:
        
        static void init_info();
        
        virtual uint8_t dimensions(count_k) const override;
                
        Point(Project&);
        Point(CopyAPI&, const Point&);
        ~Point();
        
        // Should always be valid (if defined), will default to empty otherwise
        std::string_view  r() const;

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
