////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "DObject.hpp"
#include "DObjectInfoWriter.hpp"

#include <doodle/Project.hpp>

namespace yq::doodle {
    struct DObject::Repo {
        MetaLookup<DObjectInfo>     objects;
    };

////////////////////////////////////////////////////////////////////////////////

    DObjectInfo::DObjectInfo(std::string_view zName, ObjectInfo& base, const std::source_location& sl) :
        ObjectInfo(zName, base, sl)
    {
        DObject::repo().objects << this;
    }

    bool    DObjectInfo::is_0d() const
    {
        return has(Flag::D0);
    }
    
    bool    DObjectInfo::is_1d() const
    {
        return has(Flag::D1);
    }
    
    bool    DObjectInfo::is_2d() const
    {
        return has(Flag::D2);
    }
    
    bool    DObjectInfo::is_3d() const
    {
        return has(Flag::D3);
    }
    
    bool    DObjectInfo::is_4d() const
    {
        return has(Flag::D4);
    }
    
    bool    DObjectInfo::is_5d() const
    {
        return has(Flag::D5);
    }
    
    bool    DObjectInfo::is_6d() const
    {
        return has(Flag::D6);
    }
    
    const DObjectInfo*       DObjectInfo::lookup(std::string_view ks)
    {
        auto& r = DObject::repo();
        return r.objects.find(ks);
    }

    
////////////////////////////////////////////////////////////////////////////////

    DObject::Repo& DObject::repo()
    {
        static Repo s_repo;
        return s_repo;
    }

    void DObject::init_info()
    {
        auto w = writer<DObject>();
        w.description("Spatial Object");
        w.property("description", &DObject::description).setter(&DObject::set_description);
        w.property("uid", &DObject::uid).setter(&DObject::set_uid);
        w.property("notes", &DObject::notes).setter(&DObject::set_notes);
        w.property("title", &DObject::title).setter(&DObject::set_title);
        w.property("id", &DObject::get_id);
        w.property("revision", &DObject::get_revision);
    }

    DObject::DObject(Project& prj) : m_prj(prj), m_id(prj.insert(this))
    {
    }
    
    DObject::DObject(CopyAPI& api, const DObject& cp) : 
        m_prj(api.project), m_id(api.project.insert(this)), m_attributes(cp.m_attributes)
    {
        m_parent        = cp.m_parent;
        m_children      = cp.m_children;
        m_title         = cp.m_title;
        m_notes         = cp.m_notes;
        
        api.mapper.data[cp.id()] = id();
    }
    
    DObject::~DObject()
    {
        m_children.clear();
        m_parent    = {};
    }

    std::string_view        DObject::attribute(const std::string& k) const
    {
        return m_attributes.get(k);
    }

    std::string_view        DObject::attribute(const std::string& k, all_k) const
    {
        auto& map   = m_attributes.data();
        auto i = map.find(k);
        if(i != map.end())
            return i->second;
        
        if(const DObject*p = m_prj.object(m_parent)){
            return p->attribute(k);
        } else {
            return m_prj.attribute(k);
        }
    }
    
    void                    DObject::attribute_erase(const std::string& k)
    {
        m_attributes.erase(k);
    }
    
    string_set_t            DObject::attribute_keys() const
    {
        return m_attributes.keys();
    }
    
    void                    DObject::attribute_set(const std::string&k, const std::string&v)
    {
        m_attributes.set(k, v);
    }
    
    void                    DObject::attribute_set(const std::string&k, std::string&&v)
    {
        m_attributes.set(k, std::move(v));
    }
    
    const string_map_t&     DObject::attributes() const
    {
        return m_attributes.data();
    }
    
    void    DObject::bump()
    {
        ++m_revision.local;
        ++m_revision.all;
        
        for(ID i = m_parent; i;){
            DObject*p   = m_prj.object(i);
            if(!p)
                break;
            ++(p->m_revision.all);
            i   = p->m_parent;
        }
        
        m_prj.bump();
    }

    DObject*    DObject::create(child_k, const DObjectInfo& sinfo)
    {
        DObject* obj = sinfo.create(m_prj);
        if(!obj)
            return nullptr;
        
        obj->m_parent   = id();
        m_children.push_back(obj->id());
        bump();
        return obj;
    }
    
    bool                DObject::is_attribute(const std::string& k) const
    {
        return m_attributes.contains(k);
    }

    const DObject*      DObject::parent(pointer_k) const
    {
        return m_prj.object(m_parent);
    }
    
    DObject*            DObject::parent(pointer_k)
    {
        return m_prj.object(m_parent);
    }

    void     DObject::remap(const Remapper& theMap)
    {
        m_parent    = theMap(m_parent);
        
        for(ID& i : m_children){
            i   = theMap(i);
            DObject*    dob = m_prj.object(i);
            if(dob)
                dob -> remap(theMap);
        }
    }

    void    DObject::set_description(const std::string&v)
    {
        m_description   = v;
        bump();
    }
    
    void    DObject::set_notes(const std::string&v)
    {
        m_notes     = v;
        bump();
    }
    
    void    DObject::set_uid(const std::string&v)
    {
        m_uid       = v;
        bump();
    }
    
    void    DObject::set_title(const std::string&v)
    {
        m_title     = v;
        bump();
    }


    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    
    ID Remapper::operator()(ID i) const
    {
        auto j = data.find(i.id);
        if(j != data.end())
            return { j->second };
        return i;
    }
}

YQ_OBJECT_IMPLEMENT(yq::doodle::DObject)
