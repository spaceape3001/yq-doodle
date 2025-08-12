////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Obj.hpp"

#include <art/doc/Doc.hpp>
#include <art/ObjMetaWriter.hpp>

#include <yq/core/Any.hpp>
#include <yq/xml/XmlUtils.hpp>

YQ_OBJECT_IMPLEMENT(yq::art::Obj)

namespace yq::art {
    struct Obj::Repo {
        Map<std::string_view,const ObjMeta*>    byTag;
        MetaLookup<ObjMeta>                     lookup;
    };

    ObjMeta::ObjMeta(std::string_view zName, AbstractMeta& base, const std::source_location& sl) : 
        AbstractMeta(zName, base, sl)
    {
        auto& _r = Obj::repo();
        _r.byTag[stem()]    = this;
        _r.lookup << this;
    }

////////////////////////////////////////////////////////////////////////////////

    const ObjMeta*   Obj::find_by_xml_tag(std::string_view x)
    {
        return repo().byTag.get(x, nullptr);
    }

    void Obj::init_meta()
    {
        {
        }
    
        {
            auto w = writer<Obj>();
            w.description("Art object");
        }
    }

    Obj::Repo& Obj::repo()
    {   
        static Repo s_repo;
        return s_repo;
    }

////////////////////////////////////////////////////////////////////////////////

    Obj::Obj(Doc& doc) : m_doc(doc), m_id(doc._insert(this))
    {
    }
    
    Obj::~Obj()
    {
    }

    void    Obj::save_to(XmlNode&x) const 
    {
        Abstract::save_to(x);
        write_attribute(x, "id", m_id);
        if(m_parent)
            write_child(x, "parent", m_id);
        for(auto& ch : m_children)
            write_child(x, "child", ch);
    }
    
    bool    Obj::load_from(const XmlNode&x) 
    {
        bool success = Abstract::load_from(x);
        auto par    = read_child(x, "parent", x_uint64);
        if(par)
            m_parent    = { *par };
        for(const XmlNode* ch = x.first_node("child"); ch; ch = x.next_sibling("child")){
            auto chid   = x_uint64(x);
            if(chid)
                m_children.push_back({*chid});
        }
        return success;
    }

    void    Obj::bump()
    {
        ++m_revision.local;
        for(ID i=m_id; Obj* p = m_doc.object(i); i = p->parent())
            ++(p->m_revision.all);
        ++m_doc.m_revision.all;
    }

}
