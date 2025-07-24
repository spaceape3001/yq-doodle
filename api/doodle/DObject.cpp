////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "DObject.hpp"
#include "DObjectMetaWriter.hpp"

#include <doodle/Project.hpp>

namespace yq::doodle {
    struct DObject::Repo {
        MetaLookup<DObjectMeta>     objects;
    };

////////////////////////////////////////////////////////////////////////////////

    DObjectMeta::DObjectMeta(std::string_view zName, ObjectMeta& base, const std::source_location& sl) :
        ObjectMeta(zName, base, sl)
    {
        DObject::repo().objects << this;
    }

    string_view_set_t           DObjectMeta::default_attribute_keys() const
    {
        string_view_set_t   ret;
        for(auto& i : m_attributes)
            ret.insert(i.first);
        return ret;
    }

    bool    DObjectMeta::has_default_attribute(std::string_view k) const
    {
        return m_attributes.contains(k);
    }
    
    bool    DObjectMeta::is_0d() const
    {
        return has(Flag::D0);
    }
    
    bool    DObjectMeta::is_1d() const
    {
        return has(Flag::D1);
    }
    
    bool    DObjectMeta::is_2d() const
    {
        return has(Flag::D2);
    }
    
    bool    DObjectMeta::is_3d() const
    {
        return has(Flag::D3);
    }
    
    bool    DObjectMeta::is_4d() const
    {
        return has(Flag::D4);
    }
    
    bool    DObjectMeta::is_5d() const
    {
        return has(Flag::D5);
    }
    
    bool    DObjectMeta::is_6d() const
    {
        return has(Flag::D6);
    }
    
    void    DObjectMeta::sweep_impl() 
    {
        ObjectMeta::sweep_impl();
        const DObjectMeta* parent   = dynamic_cast<const DObjectMeta*>(base());
        if(parent){
            for(auto& i : parent->m_attributes)
                m_attributes.insert(i);
        }
    }

    const DObjectMeta*       DObjectMeta::lookup(std::string_view ks)
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

    void DObject::init_meta()
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

    DObject::DObject(Project& prj) : m_project(prj), m_id(prj.insert(this))
    {
    }
    
    DObject::DObject(CopyAPI& api, const DObject& cp) : 
        m_project(api.project), 
        m_id(api.project.insert(this)),
        m_attributes(cp.m_attributes),
        m_values(cp.m_values)
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
        std::string_view    a;
        
        a   = attribute(LOCAL, k);
        if(!a.empty())
            return a;
        a   = attribute(DEFAULT, k);
        if(!a.empty())
            return a;
        return m_project.attribute(k);
    }

    std::string_view        DObject::attribute(default_k, const std::string& k) const
    {
        const DObjectMeta& dinfo = metaInfo();
        auto itr = dinfo.m_attributes.find(k);
        if(itr == dinfo.m_attributes.end())
            return {};
        if(auto p = std::get_if<std::string_view>(&itr->second))
            return *p;
        if(auto p = std::get_if<DObjectMeta::function_attribute_t>(&itr->second))
            return (*p)(this);
        return {};
    }

    std::string_view        DObject::attribute(global_k, const std::string& k) const
    {
        return m_project.attribute(k);
    }

    std::string_view        DObject::attribute(local_k, const std::string& k) const
    {
        return m_attributes.get_view(k);
    }
    
    void                    DObject::attribute_erase(const std::string& k)
    {
        m_attributes.erase(k);
    }
    
    string_set_t            DObject::attribute_keys() const
    {
        return m_attributes.key_set();
    }
    
    void                    DObject::attribute(set_k, const std::string&k, const std::string&v)
    {
        m_attributes.set(k, v);
    }
    
    void                    DObject::attribute(set_k, const std::string&k, std::string&&v)
    {
        m_attributes.set(k, std::move(v));
    }
    
    const string_map_t&     DObject::attributes() const
    {
        return m_attributes;
    }
    
    void    DObject::bump()
    {
        ++m_revision.local;
        ++m_revision.all;
        
        for(ID i = m_parent; i;){
            DObject*p   = m_project.object(i);
            if(!p)
                break;
            ++(p->m_revision.all);
            i   = p->m_parent;
        }
        
        m_project.bump();
    }

    DObject*    DObject::create(child_k, const DObjectMeta& sinfo)
    {
        DObject* obj = sinfo.create(m_project);
        if(!obj)
            return nullptr;
        
        obj->m_parent   = id();
        m_children.push_back(obj->id());
        bump();
        return obj;
    }

    bool                DObject::is_attribute(const std::string& k) const
    {
        return is_attribute(LOCAL, k) || is_attribute(DEFAULT, k) || is_attribute(GLOBAL, k);
    }

    bool                DObject::is_attribute(default_k, const std::string&k) const
    { 
        return metaInfo().has_default_attribute(k);
    }
    
    bool                DObject::is_attribute(local_k, const std::string&k) const
    {
        return m_attributes.contains(k);
    }

    bool                DObject::is_attribute(global_k, const std::string&k) const
    {
        return m_project.is_attribute(k);
    }

    const DObject*      DObject::parent(pointer_k) const
    {
        return m_project.object(m_parent);
    }
    
    DObject*            DObject::parent(pointer_k)
    {
        return m_project.object(m_parent);
    }

    void     DObject::remap(const Remapper& theMap)
    {
        m_parent    = theMap(m_parent);
        
        for(ID& i : m_children){
            i   = theMap(i);
            DObject*    dob = m_project.object(i);
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
        if(m_uid != v){
            if(!m_uid.empty())
                m_project.uid_umap(v, id());
            m_uid       = v;
            if(!m_uid.empty())
                m_project.uid_map(v, id());
        }
        bump();
    }
    
    void    DObject::set_title(const std::string&v)
    {
        m_title     = v;
        bump();
    }

    void    DObject::value(push_k, std::string&&v)
    {
        m_values.push_back(std::move(v));
        bump();
    }
    
    void    DObject::value(push_k, const std::string&v)
    {
        m_values.push_back(v);
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
