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
        Writer&     maker(void(*fn)(T&, C&))
        {
            if(m_meta && Meta::thread_safe_write()){
                m_meta -> m_makers[meta<T>().id()] = [fn](void* arg, Obj* obj) {
                    fn(*(T*)arg, *static_cast<C*>(obj));
                };
            }
        }
    
    private:
        ObjMeta*    m_meta;
    };
    

}

