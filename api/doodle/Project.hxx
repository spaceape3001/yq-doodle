////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "DObject.hpp"
#include "Project.hpp"

namespace yq::doodle {
    template <SomeDObject S>
    S*      Project::create()
    {
        return static_cast<S*>(create(meta<S>()));
    }

    template <SomeDObject S, typename Pred>
    auto    Project::foreach(Pred&&pred) 
    {
        static constexpr const bool is_object   = std::is_same_v<S,DObject>;
        
        if constexpr ( std::is_invocable_v<Pred, const S&> ){
            using return_t  = std::invoke_result_t<Pred, const S&>;
            static constexpr const bool is_void = std::is_same_v<return_t, void>;
            for(auto& itr : m_objects){
                S*  val = nullptr;
                if constexpr (is_object){
                    val = itr.second;
                } else {
                    val = dynamic_cast<S*>(itr.second);
                }
                if(!val)
                    continue;
                if constexpr (!is_void){
                    return_t   ret = pred(*val);
                    if(ret != return_t{})
                        return ret;
                } else
                    pred(*val);
            }
            if constexpr (!is_void)
                return return_t{};
        } else if constexpr ( std::is_invocable_v<Pred, S&> ){
            using return_t  = std::invoke_result_t<Pred, S&>;
            static constexpr const bool is_void = std::is_same_v<return_t, void>;
            for(auto& itr : m_objects){
                S*  val = nullptr;
                if constexpr (is_object){
                    val = itr.second;
                } else {
                    val = dynamic_cast<S*>(itr.second);
                }
                if(!val)
                    continue;
                if constexpr (!is_void){
                    return_t   ret = pred(*val);
                    if(ret != return_t{})
                        return ret;
                } else
                    pred(*val);
            }
            if constexpr (!is_void)
                return return_t{};
        } else if constexpr ( std::is_invocable_v<Pred, const S*> ){
            using return_t  = std::invoke_result_t<Pred, const S*>;
            static constexpr const bool is_void = std::is_same_v<return_t, void>;
            for(auto& itr : m_objects){
                S*  val = nullptr;
                if constexpr (is_object){
                    val = itr.second;
                } else {
                    val = dynamic_cast<S*>(itr.second);
                }
                if(!val)
                    continue;
                if constexpr (!is_void){
                    return_t   ret = pred(val);
                    if(ret != return_t{})
                        return ret;
                } else
                    pred(*val);
            }
            if constexpr (!is_void)
                return return_t{};
        } else if constexpr ( std::is_invocable_v<Pred, S*> ){
            using return_t  = std::invoke_result_t<Pred, S*>;
            static constexpr const bool is_void = std::is_same_v<return_t, void>;
            for(auto& itr : m_objects){
                S*  val = nullptr;
                if constexpr (is_object){
                    val = itr.second;
                } else {
                    val = dynamic_cast<S*>(itr.second);
                }
                if(!val)
                    continue;
                if constexpr (!is_void){
                    return_t   ret = pred(val);
                    if(ret != return_t{})
                        return ret;
                } else
                    pred(*val);
            }
            if constexpr (!is_void)
                return return_t{};
        }
    }


    template <SomeDObject S, typename Pred>
    auto    Project::foreach(Pred&&pred) const
    {
        static constexpr const bool is_object   = std::is_same_v<S,DObject>;
        
        if constexpr ( std::is_invocable_v<Pred, const S&> ){
            using return_t  = std::invoke_result_t<Pred, const S&>;
            static constexpr const bool is_void = std::is_same_v<return_t, void>;
            for(auto& itr : m_objects){
                S*  val = nullptr;
                if constexpr (is_object){
                    val = itr.second;
                } else {
                    val = dynamic_cast<S*>(itr.second);
                }
                if(!val)
                    continue;
                if constexpr (!is_void){
                    return_t   ret = pred(*val);
                    if(ret != return_t{})
                        return ret;
                } else
                    pred(*val);
            }
            if constexpr (!is_void)
                return return_t{};
        } else if constexpr ( std::is_invocable_v<Pred, const S*> ){
            using return_t  = std::invoke_result_t<Pred, const S*>;
            static constexpr const bool is_void = std::is_same_v<return_t, void>;
            for(auto& itr : m_objects){
                S*  val = nullptr;
                if constexpr (is_object){
                    val = itr.second;
                } else {
                    val = dynamic_cast<S*>(itr.second);
                }
                if(!val)
                    continue;
                if constexpr (!is_void){
                    return_t   ret = pred(val);
                    if(ret != return_t{})
                        return ret;
                } else
                    pred(*val);
            }
            if constexpr (!is_void)
                return return_t{};
        } 
    }
}
