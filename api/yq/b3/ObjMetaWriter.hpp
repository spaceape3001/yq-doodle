////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/b3/Obj.hpp>
#include <yq/meta/ObjectMetaWriter.hpp>

namespace yq::b3 {

    struct ObjMeta::DelegateFN {
        virtual void    invoke(void*,Obj*) const = 0;
    };
    
    template <class C, typename T>
    class ObjDelegateFN : public ObjMeta::DelegateFN {
    public:
        typedef void (*FN)(T&, C&);
        ObjDelegateFN(FN fn) : m_fn(fn) {}
        
        void    invoke(void* arg, Obj* obj) const override
        {
            m_fn(*(T*)arg, *static_cast<C*>(obj));
        }
        
    private:
        FN m_fn;
    };
    


    struct ObjMeta::DelegateCFN {
        virtual void    invoke(void*,const Obj*) const = 0;
    };
    
    template <class C, typename T>
    class ObjDelegateCFN : public ObjMeta::DelegateCFN {
    public:
        typedef void (*FN)(T&, const C&);
        ObjDelegateCFN(FN fn) : m_fn(fn) {}
        
        void    invoke(void* arg, const Obj* obj) const override
        {
            m_fn(*(T*)arg, *static_cast<const C*>(obj));
        }
        
    private:
        FN m_fn;
    };


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
            if(fn && m_meta && Meta::thread_safe_write()){
                m_meta -> m_delegates[meta<T>().id()] = new ObjDelegateFN<C,T>(fn);
            }
            return *this;
        }
    
        template <typename T>
        Writer&     delegate(void(*fn)(T&, const C&))
        {
            if(m_meta && Meta::thread_safe_write()){
                m_meta -> m_cDelegates[meta<T>().id()] = new ObjDelegateCFN<C,T>(fn);
            }
            return *this;
        }

    private:
        ObjMeta*    m_meta;
    };
    

}

