////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <b3/keywords.hpp>
#include <yq/typedef/circle2.hpp>
#include <yq/typedef/segment2.hpp>
#include <string_view>

namespace yq::b3 {

    struct Brush;
    struct Font;
    struct Pen;
    struct Transform;

    //! Basics to painting (allows for SVG/PNG/etc)
    //! \note This API to remain *SIMPLE* and defaulted
    class PaintDevice {
    public:
    
        //! Always given, set to things that override
        struct Data {
            const Brush*        brush       = nullptr;
            const Font*         font        = nullptr;
            const Pen*          pen         = nullptr;
            const Transform*    transform   = nullptr;
        };
    
        virtual void    circle(const Circle2D&, const Data& d) {}
        virtual void    line(const Segment2D&, const Data& d) {}
        
        //  Starts a new transform
        virtual void    group(std::string_view, const Data& d){}
        //  Ends a tranform
        virtual void    group(pop_k){}
        
    protected:
        PaintDevice(){}
        ~PaintDevice(){}
    };
}
