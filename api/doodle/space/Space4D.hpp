////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/Space.hpp>
#include <yq/shape/AxBox4.hpp>
#include <yq/typedef/range.hpp>
#include <yq/typedef/vector4.hpp>

#ifdef NAN
#undef NAN
#endif


namespace yq::doodle {
    class Space4DInfo : public SpaceMeta {
    public:
        template <typename T> class Writer;
        Space4DInfo(std::string_view zName, SpaceMeta& base, const std::source_location& sl=std::source_location::current());
    };
    

    /*! A space 
    
        Defines a 4D space in four dimensions (strict)
    */
    class Space4D : public Space {
        YQ_OBJECT_INFO(Space4DInfo)
        YQ_DOODLE_DECLARE(Space4D, Space)
    public:
    
        static void init_meta();
    
        virtual bool        supports_4D() const override { return true; }
        
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
        
        const AxBox4D&      bounds(hard_k) const { return m_hard; }
        constexpr RangeD    bounds(hard_k, x_k) const;
        constexpr RangeD    bounds(hard_k, y_k) const;
        constexpr RangeD    bounds(hard_k, z_k) const;
        constexpr RangeD    bounds(hard_k, w_k) const;

        constexpr double    bounds(hard_k, low_k, x_k) const;
        constexpr double    bounds(hard_k, low_k, y_k) const;
        constexpr double    bounds(hard_k, low_k, z_k) const;
        constexpr double    bounds(hard_k, low_k, w_k) const;

        constexpr double    bounds(hard_k, high_k, x_k) const;
        constexpr double    bounds(hard_k, high_k, y_k) const;
        constexpr double    bounds(hard_k, high_k, z_k) const;
        constexpr double    bounds(hard_k, high_k, w_k) const;
        
        const AxBox4D&      bounds(soft_k) const { return m_soft; }
        constexpr RangeD    bounds(soft_k, x_k) const;
        constexpr RangeD    bounds(soft_k, y_k) const;
        constexpr RangeD    bounds(soft_k, z_k) const;
        constexpr RangeD    bounds(soft_k, w_k) const;

        constexpr double    bounds(soft_k, low_k, x_k) const;
        constexpr double    bounds(soft_k, low_k, y_k) const;
        constexpr double    bounds(soft_k, low_k, z_k) const;
        constexpr double    bounds(soft_k, low_k, w_k) const;

        constexpr double    bounds(soft_k, high_k, x_k) const;
        constexpr double    bounds(soft_k, high_k, y_k) const;
        constexpr double    bounds(soft_k, high_k, z_k) const;
        constexpr double    bounds(soft_k, high_k, w_k) const;

        virtual bool        valid(hard_k, const Vector4D&) const;
        virtual bool        valid(soft_k, const Vector4D&) const;

    protected:
        Space4D(Project&);
        Space4D(CopyAPI&, const Space4D&);
        ~Space4D();

        //! Remap IDs/pointers appropriately
        virtual void        remap(const Remapper&);
        
        AxBox4D     m_hard = NAN;
        AxBox4D     m_soft = NAN;
        
    private:
        Space4D(const Space4D&) = delete;
        Space4D(Space4D&&) = delete;
        Space4D& operator=(const Space4D&) = delete;
        Space4D& operator=(Space4D&&) = delete;
    };
}
