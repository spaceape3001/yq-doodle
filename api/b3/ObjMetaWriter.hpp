////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <b3/Obj.hpp>
#include <yq/meta/ObjectMetaWriter.hpp>

namespace yq::b3 {
    template <typename C>
    class ObjMeta::Writer : public ObjectMeta::Writer<C> {
    public:
        Writer(ObjMeta* dInfo) : ObjectMeta::Writer<C>(dInfo), m_meta(dInfo)
        {
        }
        
        Writer(ObjMeta& dInfo) : Writer(&dInfo)
        {
        }
        
        template <typename T>
        Writer&     delegate(void(*fn)(T&, C&))
        {
            if(m_meta && Meta::thread_safe_write()){
                m_meta -> m_delegates[meta<T>().id()] = [fn](void* arg, Obj* obj) {
                    fn(*(T*)arg, *static_cast<C*>(obj));
                };
            }
        }
    
        template <typename T>
        Writer&     delegate(void(*fn)(T&, const C&))
        {
            if(m_meta && Meta::thread_safe_write()){
                m_meta -> m_cDelegates[meta<T>().id()] = [fn](void* arg, const Obj* obj) {
                    fn(*(T*)arg, *static_cast<const C*>(obj));
                };
            }
        }

    private:
        ObjMeta*    m_meta;
    };
    

}

