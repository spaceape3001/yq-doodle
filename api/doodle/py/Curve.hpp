////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/Py.hpp>

namespace yq::doodle {
    /*! Curve in space (can move, etc)
    
        ## Additional Attributes
    
        | Key | What                                    | Default                   |
        +-----+-----------------------------------------+---------------------------+
        | s   | Parametric distance along the curve     |                           |
        | s0  | Starting s-value                        | 0.                        |
        | s1  | Finishing s-value                       | 1.                        |
    */

    class Curve : public Py {
        YQ_DOODLE_DECLARE(Curve, Py)
    public:
        
        static void init_meta();
        
        virtual uint8_t dimensions(count_k) const override;

        Curve(Project&);
        Curve(CopyAPI&, const Curve&);
        ~Curve();
    };

}
