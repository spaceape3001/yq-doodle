////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

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
#include <yq/xml/XmlUtils.hpp>

namespace yq::doodle {
    Project::Project()
    {
        m_objects.push_back(nullptr);
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

    DObject*                Project::create(const DObjectInfo& info)
    { 
        return info.create(*this);
    }

    ID  Project::insert(DObject* obj)
    {
        if(!obj)
            return {};
        ID  ret{ (ID::id_t) m_objects.size() };
        m_objects.push_back(obj);
        return ret;
    }

    bool                    Project::is_attribute(const std::string&k) const
    {
        return m_attributes.contains(k);
    }
    
    bool                    Project::is_variable(const std::string&k) const
    {
        return m_attributes.contains(k);
    }

    DObject*                Project::object(ID i)
    {
        if(i >= (ID::id_t) m_objects.size())
            return m_objects[i];
        return m_objects[i];
    }
    
    const DObject*          Project::object(ID i) const
    {
        if(i >= (ID::id_t) m_objects.size())
            return m_objects[i];
        return m_objects[i];
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
        const XmlNode* root = prj.first_node(szB3X);
        if(!root)
            return false;
        
        doodleError << "xml reading not yet implemented";
        return false;
    }

    bool         Project::read(const XmlDocument&prj)
    {
        const XmlNode* root = prj.first_node(szB3X);
        if(!root){
            doodleError << szExtXML << " does not contain the root element";
            return false;
        }
        
        doodleError << "xml reading not yet implemented";
        return false;
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

    bool         Project::save_xml(const std::filesystem::path&) const
    {
        XmlDocument prj;
        
        
    
        doodleError << "xml saving not yet implemented";
        return false;
    }

    ////////////////////////////////////////////////////////////////////////////
    //  IO (High Level)

    static SFormat  guess_format(const std::filesystem::path& fp)
    {
        std::string sfx = fp.extension().string().substr(1);
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
