////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/Space.hpp>
#include <yq/shape/AxBox3.hpp>
#include <yq/typedef/range.hpp>
#include <yq/typedef/vector3.hpp>

#ifdef NAN
#undef NAN
#endif

namespace yq::doodle {
    class Space3DInfo : public SpaceInfo {
    public:
        template <typename T> class Writer;
        Space3DInfo(std::string_view zName, SpaceInfo& base, const std::source_location& sl=std::source_location::current());
    };
    

    /*! A space 
    
        Defines a 3D space in three dimensions (strict)
    */
    class Space3D : public Space {
        YQ_OBJECT_INFO(Space3DInfo)
        YQ_OBJECT_DECLARE(Space3D, Space)
    public:
    
        static void init_info();
    
        virtual bool        supports_3D() const override { return true; }

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
        
        const AxBox3D&      bounds(hard_k) const { return m_hard; }
        constexpr RangeD    bounds(hard_k, x_k) const;
        constexpr RangeD    bounds(hard_k, y_k) const;
        constexpr RangeD    bounds(hard_k, z_k) const;

        constexpr double    bounds(hard_k, low_k, x_k) const;
        constexpr double    bounds(hard_k, low_k, y_k) const;
        constexpr double    bounds(hard_k, low_k, z_k) const;

        constexpr double    bounds(hard_k, high_k, x_k) const;
        constexpr double    bounds(hard_k, high_k, y_k) const;
        constexpr double    bounds(hard_k, high_k, z_k) const;
        
        const AxBox3D&      bounds(soft_k) const { return m_soft; }
        constexpr RangeD    bounds(soft_k, x_k) const;
        constexpr RangeD    bounds(soft_k, y_k) const;
        constexpr RangeD    bounds(soft_k, z_k) const;

        constexpr double    bounds(soft_k, low_k, x_k) const;
        constexpr double    bounds(soft_k, low_k, y_k) const;
        constexpr double    bounds(soft_k, low_k, z_k) const;

        constexpr double    bounds(soft_k, high_k, x_k) const;
        constexpr double    bounds(soft_k, high_k, y_k) const;
        constexpr double    bounds(soft_k, high_k, z_k) const;

        virtual bool        valid(hard_k, const Vector3D&) const;
        virtual bool        valid(soft_k, const Vector3D&) const;

    protected:
        Space3D(Project&);
        Space3D(Project&, const Space3D&);
        ~Space3D();

        //! Remap IDs/pointers appropriately
        virtual void        remap(const Remapper&);
        
        AxBox3D     m_hard  = NAN;
        AxBox3D     m_soft  = NAN;
        
    private:
        Space3D(const Space3D&) = delete;
        Space3D(Space3D&&) = delete;
        Space3D& operator=(const Space3D&) = delete;
        Space3D& operator=(Space3D&&) = delete;
    };
}
