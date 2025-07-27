////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "DObject.hpp"
#include "Project.hpp"

namespace yq::sdl {
    template <SomeDObject S>
    S*      Project::create()
    {
        return static_cast<S*>(create(meta<S>()));
    }

    template <SomeDObject S, typename Pred>
    auto    Project::foreach(Pred&&pred) 
    {
        static constexpr const bool is_object   = std::is_same_v<S,DObject>;
        
        if constexpr ( std::is_invocable_v<Pred, S&> ){
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
                const S*  val = nullptr;
                if constexpr (is_object){
                    val = itr.second;
                } else {
                    val = dynamic_cast<const S*>(itr.second);
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
                const S*  val = nullptr;
                if constexpr (is_object){
                    val = itr.second;
                } else {
                    val = dynamic_cast<const S*>(itr.second);
                }
                if(!val)
                    continue;
                if constexpr (!is_void){
                    return_t   ret = pred(val);
                    if(ret != return_t{})
                        return ret;
                } else
                    pred(val);
            }
            if constexpr (!is_void)
                return return_t{};
        } 
    }

    template <SomeDObject S, typename Pred>
    auto    Project::foreach(uid_k, const std::string& k, Pred&& pred)
    {
        static constexpr const bool is_object   = std::is_same_v<S,DObject>;
        
        if constexpr ( std::is_invocable_v<Pred, S&> ){
            using return_t  = std::invoke_result_t<Pred, S&>;
            static constexpr const bool is_void = std::is_same_v<return_t, void>;
            auto r = m_uidmap.equal_range(k);
            for(auto itr = r.first; itr != r.second; ++itr){
                DObject *obj = object(itr->second);
                S*  val = nullptr;
                if constexpr (is_object){
                    val = obj;
                } else {
                    val = dynamic_cast<S*>(obj);
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
        } else if constexpr ( std::is_invocable_v<Pred, S*> ){
            using return_t  = std::invoke_result_t<Pred, S*>;
            static constexpr const bool is_void = std::is_same_v<return_t, void>;
            auto r = m_uidmap.equal_range(k);
            for(auto itr = r.first; itr != r.second; ++itr){
                DObject *obj = object(itr->second);
                S*  val = nullptr;
                if constexpr (is_object){
                    val = obj;
                } else {
                    val = dynamic_cast<S*>(obj);
                }
                if(!val)
                    continue;
                if constexpr (!is_void){
                    return_t   ret = pred(val);
                    if(ret != return_t{})
                        return ret;
                } else
                    pred(val);
            }
            if constexpr (!is_void)
                return return_t{};
        } else if constexpr (std::is_invocable_v<Pred, ID> ){
            using return_t  = std::invoke_result_t<Pred, ID>;
            static constexpr const bool is_void = std::is_same_v<return_t, void>;
            auto r = m_uidmap.equal_range(k);
            for(auto itr = r.first; itr != r.second; ++itr){
                if constexpr (!is_void){
                    return_t   ret = pred(itr->second);
                    if(ret != return_t{})
                        return ret;
                } else
                    pred(itr->second);
            }
            if constexpr (!is_void)
                return return_t{};
        }
    }


    template <SomeDObject S, typename Pred>
    auto    Project::foreach(uid_k, const std::string& k, Pred&& pred) const
    {
        static constexpr const bool is_object   = std::is_same_v<S,DObject>;
        
        if constexpr ( std::is_invocable_v<Pred, const S&> ){
            using return_t  = std::invoke_result_t<Pred, const S&>;
            static constexpr const bool is_void = std::is_same_v<return_t, void>;
            auto r = m_uidmap.equal_range(k);
            for(auto itr = r.first; itr != r.second; ++itr){
                const DObject *obj = object(itr->second);
                const S*  val = nullptr;
                if constexpr (is_object){
                    val = obj;
                } else {
                    val = dynamic_cast<const S*>(obj);
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
            static_assert(!is_void);
            auto r = m_uidmap.equal_range(k);
            for(auto itr = r.first; itr != r.second; ++itr){
                const DObject *obj = object(itr->second);
                const S*  val = nullptr;
                if constexpr (is_object){
                    val = obj;
                } else {
                    val = dynamic_cast<const S*>(obj);
                }
                if(!val)
                    continue;
                if constexpr (!is_void){
                    return_t   ret = pred(val);
                    if(ret != return_t{})
                        return ret;
                } else
                    pred(val);
            }
            if constexpr (!is_void)
                return return_t{};
        } else if constexpr (std::is_invocable_v<Pred, ID> ){
            using return_t  = std::invoke_result_t<Pred, ID>;
            static constexpr const bool is_void = std::is_same_v<return_t, void>;
            static_assert(!is_void);
            auto r = m_uidmap.equal_range(k);
            for(auto itr = r.first; itr != r.second; ++itr){
                if constexpr (!is_void){
                    return_t   ret = pred(itr->second);
                    if(ret != return_t{})
                        return ret;
                } else
                    pred(itr->second);
            }
            if constexpr (!is_void)
                return return_t{};
        }
    }

    template <SomeDObject S>
    S*              Project::object(uid_k, const std::string&k)
    {
        return foreach<S>(UID, k, [](S* obj) -> S* { return obj; });
    }
    
    template <SomeDObject S>
    const S*        Project::object(uid_k, const std::string&k) const
    {
        return foreach<S>(UID, k, [](const S* obj) -> const S* { return obj; });
    }
}
