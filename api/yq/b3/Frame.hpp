////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/b3/Obj.hpp>
#include <yq/b3/typedef.hpp>
#include <yq/typedef/axbox2.hpp>
#include <yq/typedef/tensor23.hpp>

namespace yq::b3 {
    class Terrain;
    class Point;
    
    class Frame : public Obj {
        YQ_OBJECT_DECLARE(Frame, Obj)
    public:

        using const_children_t    = std::span<const Obj* const>;
        using children_t        = std::span<Obj* const>;
    
        Frame(const Param& p);
        virtual ~Frame();
        
        
        virtual void            calc_points() override;
        
        Obj*                    child(std::span<const std::string_view>);
        const Obj*              child(std::span<const std::string_view>) const;

        Obj*                    child(std::string_view);
        const Obj*              child(std::string_view) const;
        
        template <typename O>
        O*                      child_as(std::string_view);
        template <typename O>
        const O*                child_as(std::string_view) const;

        children_t              children() { return m_children; }
        const_children_t        children() const { return m_children; }

        template <typename Pred>
        auto                    children(Pred&&);
        
        template <typename Pred>
        auto                    children(Pred&&) const;

        template <typename O, typename Pred>
        auto                    children_as(Pred&&);
        
        template <typename O, typename Pred>
        auto                    children_as(Pred&&) const;

        template <typename O>
        Vector<O*>              children_as();
        
        template <typename O>
        Vector<const O*>        children_as() const;


        const Obj*              find(std::string_view) const;
        Obj*                    find(std::string_view) override;

        virtual void            frame_pop() {}    // used for end-of-frame considerations.....

        Point*                  point(const std::string&);
        const Point*            point(const std::string&) const;

        //  If not yet set, initialize AxBox2D to NaN
        void                    point_bounds(const Tensor23D&, AxBox2D&) const;
        

        Vector<Point*>          points(std::span<const std::string>);
        Vector<const Point*>    points(std::span<const std::string>) const;
        
     
        Terrain*                terrain() { return m_terrain; }
        const Terrain*          terrain() const { return m_terrain; }
        
        virtual Vector3D        to_frame(const Vector3D&) const;
        virtual Vector3D        to_parent(const Vector3D&) const;



#if 0
        

        template <typename A>
        Vector<A*>      allChildrenAs();

        template <typename A>
        Vector<const A*>    allChildrenAs() const;
        
        template <typename A, typename Pred>
        auto            allChildrenAs(Pred&&);        

        template <typename A, typename Pred>
        auto            allChildrenAs(Pred&&) const;        
#endif        

    private:
        friend class Obj;
        friend class Terrain;
        
        Vector<Obj*>    m_children;
        Terrain*        m_terrain   = nullptr;
        ObjMap          m_byName;
    };

}
