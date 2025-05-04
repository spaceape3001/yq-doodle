////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Project.hxx"
#include "Project.hpp"
#include "DObject.hpp"
#include <doodle/bit/ID.hpp>
#include <yq/xml/XmlFile.hpp>
#include <yq/xml/XmlUtils.hpp>
#include <yq/file/FileUtils.hpp>
#include <yq/errors.hpp>
#include <doodle/strings.hpp>
#include <doodle/logging.hpp>
#include <yq/container/ByteArray.hpp>
#include <yq/text/match.hpp>
#include <yq/tags.hpp>
#include <yq/core/Any.hpp>

namespace yq::doodle {
    static constexpr unsigned kFormat       = 1;

    Project::Project()
    {
    }
    
    Project::~Project()
    {
    }


    std::string_view        Project::attribute(const std::string&k) const
    {
        return m_attributes.get(k);
    }

    void                    Project::attribute_erase(const std::string&k)
    {
        m_attributes.erase(k);
    }
    
    string_set_t            Project::attribute_keys() const
    {
        return m_attributes.keys();
    }
    
    void                    Project::attribute_set(const std::string& k, const std::string& v)
    {
        m_attributes.set(k,v);
    }
    
    void                    Project::attribute_set(const std::string& k, std::string&&v)
    {
        m_attributes.set(k, std::move(v));
    }

    const string_map_t&     Project::attributes() const
    {
        return m_attributes.data();
    }

    void                    Project::bump()
    {
        ++m_revision;
    }

    bool                    Project::contains(ID i) const
    {
        auto itr = m_objects.find(i);
        return (itr != m_objects.end()) && itr->second;
    }

    DObject*                Project::create(const DObjectInfo& info)
    { 
        return info.create(*this);
    }

    ID  Project::insert(DObject* obj)
    {
        if(!obj)
            return {};
            
        ID  ret = m_loading ? m_loading : ID{ ++m_nextID };
        m_objects[ret]  = obj;
        return ret;
    }

    bool                    Project::is_attribute(const std::string&k) const
    {
        return m_attributes.contains(k);
    }
    
    bool                    Project::is_empty() const
    {
        return m_objects.empty() && m_attributes.empty() && m_variables.empty() && m_title.empty() && 
            m_description.empty() && m_notes.empty() && m_uidmap.empty();
    }

    bool                    Project::is_variable(const std::string&k) const
    {
        return m_attributes.contains(k);
    }

    DObject*                Project::object(ID id)
    {
        auto i = m_objects.find(id);
        if(i != m_objects.end())
            return i->second;
        return nullptr;
    }
    
    const DObject*          Project::object(ID id) const
    {
        auto i = m_objects.find(id);
        if(i != m_objects.end())
            return i->second;
        return nullptr;
    }

    void                    Project::set_description(const std::string&d)
    {
        m_description = d;
        bump();
    }

    void                    Project::set_notes(const std::string& n)
    {
        m_notes = n;
        bump();
    }

    void                    Project::set_title(const std::string& t)
    {
        m_title = t;
        bump();
    }

    void    Project::uid_map(const std::string&s, ID )
    {
        // TODO
    }
    
    void    Project::uid_umap(const std::string&s, ID)
    {
        // TODO
    }

    std::string_view        Project::variable(const std::string&k) const
    {
        return m_variables.get(k);
    }

    void                    Project::variable_erase(const std::string&k)
    {
        m_variables.erase(k);
    }
    
    string_set_t            Project::variable_keys() const
    {
        return m_variables.keys();
    }
    
    void                    Project::variable_set(const std::string&k, const std::string&v)
    {
        m_variables.set(k, v);
    }
    
    void                    Project::variable_set(const std::string&k, std::string&&v)
    {
        m_variables.set(k, std::move(v));
    }
    
    const string_map_t&     Project::variables() const
    {
        return m_variables.data();
    }

    ////////////////////////////////////////////////////////////////////////////
    //  B3
    

    bool     Project::census_b3(Census&, const std::filesystem::path&)
    {   
        doodleError << "B3 reading not yet implemented";
        return false;
    }

    bool         Project::load_b3(ByteArray& bytes, generator_fn&& pred)
    {
        doodleError << "B3 reading not yet implemented";
        return false;
    }
    
    bool         Project::save_b3(const std::filesystem::path&) const
    {
        doodleError << "B3 saving not yet implemented";
        return false;
    }

    ////////////////////////////////////////////////////////////////////////////
    //  XML

    bool     Project::census_xml(Census&, const std::filesystem::path& fp)
    {
        XmlDocument prj;
        std::error_code ec  = read_file(prj, fp);
        if(ec != std::error_code())
            return false;
        const XmlNode* root = prj.first_node(szD3X);
        if(!root)
            return false;
        
        doodleError << "xml reading not yet implemented";
        return false;
    }

    bool         Project::read(const XmlDocument&prj)
    {
        const XmlNode* root = prj.first_node(szD3X);
        if(!root){
            doodleError << szExtXML << " does not contain the root element";
            return false;
        }

        m_title         = read_child(*root, szTitle, x_string);
        m_description   = read_child(*root, szTitle, x_string);
        m_notes         = read_child(*root, szNotes, x_string);
        for(const XmlNode* x = root->first_node(szAttribute); x; x = x->next_sibling(szAttribute)){
            std::string k = read_attribute(*x, szKey, x_string);
            std::string v = x_string(*x);
            m_attributes.set(k,v);
        }
        for(const XmlNode* x = root->first_node(szVariable); x; x = x->next_sibling(szVariable)){
            std::string k = read_attribute(*x, szKey, x_string);
            std::string v = x_string(*x);
            m_variables.set(k,v);
        }
        for(const XmlNode* x = root->first_node(szObject); x; x = x->next_sibling(szObject)){
            std::string cls = read_attribute(*x, szClass, x_string);
            if(cls.empty()){
                doodleWarning << "unspecified class for object";
                continue;
            }
            auto id = read_attribute(*x, szID, x_uint32);
            if(!id){
                doodleWarning << "unable to read the ID for object (" << cls << ")";
                continue;
            }
            
            const DObjectInfo*   dinfo  = DObjectInfo::lookup(cls);
            if(!dinfo){
                doodleWarning << "unable to find an object type " << cls;
                continue;
            }
            
            m_loading.id    = *id;
            DObject*    obj = dinfo->create(*this);
            if(!obj){
                doodleWarning << "unable to create an object type " << cls;
                continue;
            }

            auto par = read_child(*x, szParent, x_uint64);
            if(par)
                obj->m_parent.id    = *par;

            obj->m_uid          = read_child(*x, szParent, x_string);
            obj->m_title        = read_child(*x, szTitle, x_string);
            obj->m_description  = read_child(*x, szDescription, x_string);
            obj->m_notes        = read_child(*x, szNotes, x_string);
            
            for(const XmlNode* c = x->first_node(szChild); c; c=c->next_sibling(szChild)){
                auto id = x_uint32(*c);
                if(!id)
                    continue;
                obj->m_children.push_back({*id});
            }
            
            for(const XmlNode* a = x->first_node(szAttribute); a; a = a->next_sibling(szAttribute)){
                std::string k = read_attribute(*a, szKey, x_string);
                std::string v = x_string(*a);
                obj->m_attributes.set(k,v);
            }
            
            for(const XmlNode* p = x->first_node(szProperty); p; p = p->next_sibling(szProperty)){
                std::string k = read_attribute(*p, szKey, x_string);
                const PropertyInfo* pi  = dinfo->properties(ALL).find(k);
                if(!pi){
                    doodleWarning << "unable to find property (" << k << ") on type " << cls;
                    continue;
                }
                
                std::string t = read_attribute(*p, szType, x_string);
                const TypeInfo* ti  = nullptr;
                if(!t.empty()){
                    ti  = TypeInfo::find(t);
                    if(!ti){
                        doodleWarning << "Unable to find type info for " << t;
                        continue;
                    }
                }

                const TypeInfo& type = ti ? *ti : pi->type();
                Any value;

                if(type.can_write_and_parse()){
                    if(!value.parse(type, x_string(*p)))
                        continue;
                } else {
                    //  non write/parse.... TODO
                    continue;
                }
                pi->set(obj, value);
            }
            
            obj->load(*x);
        }
        m_loading = {};
        return true;
    }

    bool         Project::load_xml(ByteArray& bytes, generator_fn&& fn)
    {
        XmlDocument prj;
        bytes << '\0';  // safety....

        try {
            prj.parse<0>(bytes.data());
        } catch(const rapidxml::parse_error& pe){
            size_t  pt  = pe.where<char>() - bytes.data();
            doodleError << "Xml parse error: " << pe.what() << " (at byte " << pt << ")";
            return false;
        }
        
        Project*p   = fn();
        if(!p)
            return false;
        
        return p->read(prj);
    }

    void         Project::write(XmlDocument&doc) const
    {
        XmlNode& root    = *doc.create_element(szD3X);
        write_attribute(root, szFormat, kFormat);
        if(!m_title.empty())
            write_child(root, szTitle, m_title);
        if(!m_description.empty())
            write_child(root, szDescription, m_description);
        if(!m_notes.empty())
            write_child(root, szNotes, m_notes);
        for(auto& i : m_attributes.data()){
            XmlNode& x   = *root.create_element(szAttribute);
            write_attribute(x, szKey, i.first);
            write_x(x, i.second);
        }
        for(auto& i : m_variables.data()){
            XmlNode& x   = *root.create_element(szVariable);
            write_attribute(x, szKey, i.first);
            write_x(x, i.second);
        }
        for(auto& itr : m_objects){
            const DObject* obj  = itr.second;
            if(!obj)
                continue;
            XmlNode& x = *root.create_element(szObject);
            write_attribute(x, szID, obj->id().id);
            write_attribute(x, szClass, obj->metaInfo().name());
            if(!obj->uid().empty())
                write_child(x, szUID, obj->uid());
            if(obj->parent())
                write_child(x, szParent, obj->parent().id);
            if(!obj->title().empty())
                write_child(root, szTitle, obj->title());
            if(!obj->description().empty())
                write_child(root, szDescription, obj->description());
            if(!obj->notes().empty())
                write_child(root, szNotes, obj->notes());
            for(ID j : obj->children())
                write_child(x, szChild, j.id);
            for(auto& i : obj->attributes()){
                XmlNode& a = *x.create_element(szAttribute);
                write_attribute(a, szKey, i.first);
                write_x(a, i.second);
            }
            for(const PropertyInfo* p : obj->metaInfo().properties(ALL).all){
                if(!p->tagged(kTag_Save))
                    continue;
                
                any_x   value   = p->get(obj);
                if(!value)  
                    continue;
                    
            
                XmlNode& prop = *x.create_element(szProperty);
                write_attribute(prop, szKey, p->name());
                
                const TypeInfo& type    = (*value).type();
                if(type.id() != p->type().id())
                    write_attribute(prop, szType, type.name());
                
                if(type.can_write_and_parse()){
                    write_x(prop, (*value).writable());
                    continue;
                }

                //  non write/parse.... TBD
            }
            obj->save(x);
        }
    }

    bool         Project::save_xml(const std::filesystem::path& fp) const
    {
        XmlDocument prj;
        xml_start(prj);
        write(prj);
        return save_file(prj, fp) == std::error_code();
    }

    ////////////////////////////////////////////////////////////////////////////
    //  IO (High Level)

    static SFormat  guess_format(const std::filesystem::path& fp)
    {
        std::string sfx = fp.extension().string();
        if(sfx.empty())
            return SFormat::AUTO;
        sfx = sfx.substr(1);
        if(is_similar(sfx, Project::szExtB3))
            return B3;
        if(is_similar(sfx, Project::szExtXML))
            return XML;
        return SFormat::AUTO;
    }

    bool   Project::census(Census&ret, const std::filesystem::path&fp, SFormat fmt)
    {
        if(fmt == SFormat::AUTO)
            fmt = guess_format(fp);
        switch(fmt){
        case SFormat::XML:
            return census_xml(ret, fp);
        case SFormat::B3:
            return census_b3(ret, fp);
        default:
            doodleError << "Unable to determine format for " << fp.string();
            return false;
        }
    }

    bool    Project::load(const std::filesystem::path& fp, SFormat fmt, generator_fn&& fn)
    {
        if(!file_exists(fp)){
            doodleError << "File does not exist.  " << fp.string();
            return false;
        }
        
        if(!file_readable(fp)){
            doodleError << "File is not readable.  " << fp.string();
            return false;
        }

        if(fmt == SFormat::AUTO)
            fmt = guess_format(fp);

        if(fmt == SFormat::AUTO){
            doodleError << "Unable to determine format for " << fp.string();
            return false;
        }
        
        ByteArray   bytes   = file_bytes(fp);
        if(bytes.empty()){
            doodleError << "File is empty.  " << fp.string();
            return false;
        }
        
        switch(fmt){
        case SFormat::B3:
            return load_b3(bytes, std::move(fn));
        case SFormat::XML:
            return load_xml(bytes, std::move(fn));
        default:
            return false;
        }
    }

    ProjectSPtr    Project::load(shared_k, const std::filesystem::path&fp, SFormat sf)
    {
        ProjectSPtr   ret;
        
        bool    loaded  = load(fp, sf, [&]() -> Project* {
            ret = std::make_shared<Project>();
            return ret.get();
        });
        
        if(loaded)
            return ret;
        return {};
    }
    
    ProjectUPtr    Project::load(unique_k, const std::filesystem::path&fp, SFormat sf)
    {
        ProjectUPtr   ret;
        bool    loaded  = load(fp, sf, [&]() -> Project* {
            ret = std::make_unique<Project>();
            return ret.get();
        });
        
        if(loaded)
            return ret;
        return {};
    }
    
    Project*       Project::load(raw_k, const std::filesystem::path&fp, SFormat sf)
    {
        Project*  ret = nullptr;
        bool    loaded  = load(fp, sf, [&]() -> Project* {
            ret = new Project;
            return ret;
        });
        if(loaded)
            return ret;
        if(ret)
            delete ret;
        return nullptr;
    }

    bool             Project::save(const std::filesystem::path&fp, SFormat fmt) const
    {
        if(fmt == SFormat::AUTO)
            fmt = guess_format(fp);
        switch(fmt){
        case SFormat::B3:
            return save_b3(fp);
        case SFormat::XML:
            return save_xml(fp);
        default:
            doodleError << "Unable to determine format for " << fp.string();
            return false;
        }
    }
}
