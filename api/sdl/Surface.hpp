////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <sdl/DObject.hpp>
#include <sdl/keywords.hpp>
#include <yq/shape/AxBox2.hpp>
#include <yq/typedef/range.hpp>
#include <yq/typedef/vector2.hpp>

#ifdef NAN
#undef NAN
#endif

namespace yq::sdl {
    /*! A drawing surface
    */
    class Surface : public DObject {
        YQ_SDL_DECLARE(Surface, DObject)
    public:
    
        static void init_meta();

        /*  
            Bounds are the limits of validity for a space.  
            Hard is the outer most impenetrable "wall", while a 
            soft is more of a guidance/cushion.
            
            NOTE (1)    Just because a coordinate is "inside" does NOT 
                        imply it's valid, simply a coordinate outside 
                        definitely is outside.  Conventions will be 
                        worked out (eventually).
            
            NOTE (2)    NaNs imply there is no limit (and will be 
                        the default).
                        
            An example (in 2D) is that of a page, the soft limits
            would be the page boundary, while the hard limits are
            NaN (undefined).  Cut that paper into a funny shape, 
            and the inside test will fail whereever the paper's 
            been cut away.
            
            NOTE (3)    override the box ones first, the other 
                        helpers default implementations will
                        call that.
        */
        AxBox2D             bounds(hard_k) const;
        AxBox2D             bounds(soft_k) const;
     
    protected:
        Surface(Project&);
        Surface(CopyAPI&, const Surface&);
        ~Surface();

        //! Remap IDs/pointers appropriately
        virtual void        remap(const Remapper&);
        
        virtual AxBox2D     calc(soft_k) const = 0;
        virtual AxBox2D     calc(hard_k) const = 0;
        
    private:
        Surface(const Surface&) = delete;
        Surface(Surface&&) = delete;
        Surface& operator=(const Surface&) = delete;
        Surface& operator=(Surface&&) = delete;
    };
}
