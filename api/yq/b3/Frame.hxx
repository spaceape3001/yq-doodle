////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/b3/Frame.hpp>
#include <yq/algorithm/foreach_iterable.hpp>
#include <type_traits>

namespace yq::b3 {

    template <typename O>
    O*        Frame::child_as(std::string_view k)
    {
        return dynamic_cast<O*>(child(k));
    }
    
    template <typename O>
    const O*  Frame::child_as(std::string_view k) const
    {
        return dynamic_cast<const O*>(child(k));
    }

    template <typename Pred>
    auto      Frame::children(Pred&& pred)
    {
        return foreach_iterable<Obj,Obj,Pred>(m_children, std::move(pred));
    }
    
    template <typename Pred>
    auto      Frame::children(Pred&&pred) const
    {
        return foreach_iterable<const Obj,const Obj,Pred>(m_children, std::move(pred));
    }

    template <typename O, typename Pred>
    auto      Frame::children_as(Pred&& pred)
    {
        return foreach_iterable<Obj,O,Pred>(m_children, std::move(pred));
    }
    
    template <typename O, typename Pred>
    auto      Frame::children_as(Pred&& pred) const
    {
        return foreach_iterable<const Obj,const O,Pred>(m_children, std::move(pred));
    }

    template <typename O>
    Vector<O*>  Frame::children_as()
    {
        Vector<O*>  ret;
        children_as<O>([&](O* obj){
            ret << obj;
        });
        return ret;
    }
    
    template <typename O>
    Vector<const O*>  Frame::children_as() const
    {
        Vector<const O*>  ret;
        children_as<const O>([&](const O* obj){
            ret << obj;
        });
        return ret;
    }
}
