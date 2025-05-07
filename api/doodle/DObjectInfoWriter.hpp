////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/DObject.hpp>
#include <yq/meta/ObjectInfoWriter.hpp>

namespace yq::doodle {
    template <typename C>
    class DObjectInfo::Writer : public ObjectInfo::Writer<C> {
    public:
        Writer(DObjectInfo* dInfo) : ObjectInfo::Writer<C>(dInfo), m_meta(dInfo)
        {
        }
        
        Writer(DObjectInfo& dInfo) : Writer(&dInfo)
        {
        }
        
        Writer& icon(uint16_t n, std::string_view v)
        {
            if(m_meta)
                m_meta -> m_icons[n] = std::string(v);
            return *this;
        }
        
        Writer& support_0d()
        {
            if(m_meta)
                m_meta -> m_supports |= Dim::D0;
            return *this;
        }
        
        Writer& support_1d()
        {
            if(m_meta)
                m_meta -> m_supports |= Dim::D1;
            return *this;
        }

        Writer& support_2d()
        {
            if(m_meta)
                m_meta -> m_supports |= Dim::D2;
            return *this;
        }

        Writer& support_3d()
        {
            if(m_meta)
                m_meta -> m_supports |= Dim::D3;
            return *this;
        }

        Writer& support_4d()
        {
            if(m_meta)
                m_meta -> m_supports |= Dim::D4;
            return *this;
        }

        Writer& support_5d()
        {
            if(m_meta)
                m_meta -> m_supports |= Dim::D5;
            return *this;
        }

        Writer& support_6d()
        {
            if(m_meta)
                m_meta -> m_supports |= Dim::D6;
            return *this;
        }
    private:
        DObjectInfo*    m_meta;
    };
    
    template <typename Obj>
    class DObjectFixer : public ObjectFixer<Obj> {
    public:
        DObjectFixer(std::string_view szName, typename Obj::MyBase::MyInfo& myBase, std::source_location sl=std::source_location::current()) : 
            ObjectFixer<Obj>(szName, myBase, sl) 
        {
        }

        virtual Obj* create() const override { return nullptr; }

        
        virtual DObject* create(Project&prj) const override
        {
            //  While the std::is_constructible_v<> test seemed nice, it unfortunately requires 
            //  PUBLIC constructors & destructors, which we do *NOT* want here.  Instead, we 
            //  have to do the macro trick with abstract, and mark appropriately.
            if constexpr (!Obj::kAbstract && !std::is_abstract_v<Obj>) {
                if(ObjectInfo::is_abstract()){
                    return nullptr;
                }
                return new Obj(prj);
            } else {
                return nullptr;
            }
        }
        
        virtual DObject* copy(Project&prj, const DObject&obj) const override
        {
            if constexpr (!Obj::kAbstract && !std::is_abstract_v<Obj>) {
                if(ObjectInfo::is_abstract())
                    return nullptr;
                return new Obj(prj, static_cast<const Obj&>(obj));
            } else
                return nullptr;
        }
    };
}

