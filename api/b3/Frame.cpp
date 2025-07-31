////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Frame.hpp"
#include "Frame.hxx"
#include <b3/ObjMetaWriter.hpp>
#include <b3/spatial/Point.hpp>

#include <yq/shape/AxBox2.hpp>
#include <yq/tensor/Tensor23.hpp>
#include <yq/text/split.hpp>

#include <yq/tensor/Tensor23.hxx>

YQ_OBJECT_IMPLEMENT(yq::b3::Frame)

namespace yq::b3 {
    Frame::Frame(const Param& p) : Obj(p)
    {
    }
    
    Frame::~Frame()
    {
    }

    void    Frame::calc_points()
    {
        for(Obj*obj : m_children){
            Point*  pt  = dynamic_cast<Point*>(obj);
            if(pt)
                pt->calc_points();
        }
        for(Obj* obj : m_children){
            if(!dynamic_cast<Point*>(obj))
                obj->calc_points();
        }
    }

    Obj*            Frame::child(std::string_view path)
    {
        if(path.empty())
            return nullptr;
        auto bits = split(path, '.');
        return child(bits);
    }
    
    const Obj*      Frame::child(std::string_view path) const
    {
        if(path.empty())
            return nullptr;
        auto bits = split(path, '.');
        return child(bits);
    }

    Obj*            Frame::child(std::span<const std::string_view> path)
    {
        if(path.empty())
            return nullptr;
            
        Frame*  f   = this;
        size_t  n   = 0;
        for(; f && ((n+1) < (size_t) path.size()); ++n){
            if(path[n].empty()){
                f   = nullptr;
            } else {
                f   = dynamic_cast<Frame*>(f->m_byName.get(std::string(path[n]), nullptr));
            }
        }
        
        if(!f)
            return nullptr;
        return f->m_byName.get(std::string(path[n]), nullptr);
    }
    
    const Obj*      Frame::child(std::span<const std::string_view> path) const
    {
        return const_cast<Frame*>(this) -> child(path);
    }

    Obj*            Frame::find(std::string_view path)
    {
        if(path.empty())
            return nullptr;
        auto bits = split(path, '.');
        if(bits.empty())
            return nullptr;
            
        for(Frame* f = this; f; f = f->frame()){
            Obj* obj = f->child(bits);
            if(obj)
                return obj;
        }
        return nullptr;
    }

    const Obj*      Frame::find(std::string_view path) const
    {
        return const_cast<Frame*>(this)->find(path);
    }
    
    Point*          Frame::point(const std::string&k)
    {
        for(Frame* f = this; f; f=f->frame()){
            if(Point*p = dynamic_cast<Point*>(m_byName.get(k, nullptr)))
                return p;
        }
        return nullptr;
    }
    
    const Point*    Frame::point(const std::string&k) const
    {
        for(const Frame* f = this; f; f=f->frame()){
            if(const Point*p = dynamic_cast<const Point*>(m_byName.get(k, nullptr)))
                return p;
        }
        return nullptr;
    }

    void    Frame::point_bounds(const Tensor23D& T, AxBox2D& box) const
    {
        for(const Obj* obj : m_children){
            if(const Point*p = dynamic_cast<const Point*>(obj)){
                Vector2D    v  = T * p->global();
                if(!is_nan(v)){
                    if(is_nan(box)){
                        box = { v, v };
                    } else {
                        box |= v;
                    }
                }
            }
            
            if(const Frame* f = dynamic_cast<const Frame*>(obj))
                f->point_bounds(T,box);
        }
    }

    Vector<Point*>          Frame::points(std::span<const std::string> them)
    {
        Vector<Point*> ret;
        ret.reserve(them.size());
        for(const std::string& s : them){
            if(Point* p = point(s))
                ret << p;
        }
        return ret;
    }
    
    Vector<const Point*>    Frame::points(std::span<const std::string> them) const
    {
        Vector<const Point*> ret;
        ret.reserve(them.size());
        for(const std::string& s : them){
            if(const Point* p = point(s))
                ret << p;
        }
        return ret;
    }

    Vector3D        Frame::to_frame(const Vector3D&v) const
    {
        return v;
    }
    
    Vector3D        Frame::to_parent(const Vector3D&v) const
    {
        return v;
    }

}
