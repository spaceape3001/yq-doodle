////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "DDocument.hpp"
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
    DDocument::DDocument()
    {
        m_objects.push_back(nullptr);
    }
    
    DDocument::~DDocument()
    {
    }


    std::string_view        DDocument::attribute(const std::string&k) const
    {
        return m_attributes.get(k);
    }

    void                    DDocument::attribute_erase(const std::string&k)
    {
        m_attributes.erase(k);
    }
    
    string_set_t            DDocument::attribute_keys() const
    {
        return m_attributes.keys();
    }
    
    void                    DDocument::attribute_set(const std::string& k, const std::string& v)
    {
        m_attributes.set(k,v);
    }
    
    void                    DDocument::attribute_set(const std::string& k, std::string&&v)
    {
        m_attributes.set(k, std::move(v));
    }

    const string_map_t&     DDocument::attributes() const
    {
        return m_attributes.data();
    }

    void                    DDocument::bump()
    {
        ++m_revision;
    }

    DObject*                DDocument::create(const DObjectInfo& info)
    { 
        return info.create(*this);
    }

    ID  DDocument::insert(DObject* obj)
    {
        if(!obj)
            return {};
        ID  ret{ (ID::id_t) m_objects.size() };
        m_objects.push_back(obj);
        return ret;
    }

    bool                    DDocument::is_attribute(const std::string&k) const
    {
        return m_attributes.contains(k);
    }
    
    bool                    DDocument::is_variable(const std::string&k) const
    {
        return m_attributes.contains(k);
    }

    DObject*                DDocument::object(ID i)
    {
        if(i >= (ID::id_t) m_objects.size())
            return m_objects[i];
        return m_objects[i];
    }
    
    const DObject*          DDocument::object(ID i) const
    {
        if(i >= (ID::id_t) m_objects.size())
            return m_objects[i];
        return m_objects[i];
    }

    void                    DDocument::set_description(const std::string&d)
    {
        m_description = d;
        bump();
    }

    void                    DDocument::set_notes(const std::string& n)
    {
        m_notes = n;
        bump();
    }

    void                    DDocument::set_title(const std::string& t)
    {
        m_title = t;
        bump();
    }

    void    DDocument::uid_map(const std::string&s, ID )
    {
        // TODO
    }
    
    void    DDocument::uid_umap(const std::string&s, ID)
    {
        // TODO
    }

    std::string_view        DDocument::variable(const std::string&k) const
    {
        return m_variables.get(k);
    }

    void                    DDocument::variable_erase(const std::string&k)
    {
        m_variables.erase(k);
    }
    
    string_set_t            DDocument::variable_keys() const
    {
        return m_variables.keys();
    }
    
    void                    DDocument::variable_set(const std::string&k, const std::string&v)
    {
        m_variables.set(k, v);
    }
    
    void                    DDocument::variable_set(const std::string&k, std::string&&v)
    {
        m_variables.set(k, std::move(v));
    }
    
    const string_map_t&     DDocument::variables() const
    {
        return m_variables.data();
    }

    ////////////////////////////////////////////////////////////////////////////
    //  B3
    

    bool     DDocument::census_b3(Census&, const std::filesystem::path&)
    {   
        doodleError << "B3 reading not yet implemented";
        return false;
    }

    template <typename Pred> 
    bool         DDocument::load_b3(ByteArray& bytes, Pred&& pred)
    {
        doodleError << "B3 reading not yet implemented";
        return false;
    }
    
    bool         DDocument::save_b3(const std::filesystem::path&) const
    {
        doodleError << "B3 saving not yet implemented";
        return false;
    }

    ////////////////////////////////////////////////////////////////////////////
    //  XML

    bool     DDocument::census_xml(Census&, const std::filesystem::path& fp)
    {
        XmlDocument doc;
        std::error_code ec  = read_file(doc, fp);
        if(ec != std::error_code())
            return false;
        const XmlNode* root = doc.first_node(szB3X);
        if(!root)
            return false;
        
        doodleError << "xml reading not yet implemented";
        return false;
    }

    bool         DDocument::read(const XmlDocument&doc)
    {
        const XmlNode* root = doc.first_node(szB3X);
        if(!root){
            doodleError << szExtXML << " does not contain the root element";
            return false;
        }
        
        doodleError << "xml reading not yet implemented";
        return false;
    }

    template <typename Pred> 
    bool         DDocument::load_xml(ByteArray& bytes, Pred&& pred)
    {
        XmlDocument doc;
        bytes << '\0';  // safety....

        try {
            doc.parse<0>(bytes.data());
        } catch(const rapidxml::parse_error& pe){
            size_t  pt  = pe.where<char>() - bytes.data();
            doodleError << "Xml parse error: " << pe.what() << " (at byte " << pt << ")";
            return false;
        }
        
        DDocument*p   = pred();
        if(!p)
            return false;
        
        return p->read(doc);
    }

    bool         DDocument::save_xml(const std::filesystem::path&) const
    {
        XmlDocument doc;
        
        
    
        doodleError << "xml saving not yet implemented";
        return false;
    }

    ////////////////////////////////////////////////////////////////////////////
    //  IO (High Level)

    static SFormat  guess_format(const std::filesystem::path& fp)
    {
        std::string sfx = fp.extension().string().substr(1);
        if(is_similar(sfx, DDocument::szExtB3))
            return B3;
        if(is_similar(sfx, DDocument::szExtXML))
            return XML;
        return SFormat::AUTO;
    }

    bool   DDocument::census(Census&ret, const std::filesystem::path&fp, SFormat fmt)
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

    template <typename Pred> 
    bool    DDocument::load(const std::filesystem::path& fp, SFormat fmt, Pred&& pred)
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
            return load_b3(bytes, std::move(pred));
        case SFormat::XML:
            return load_xml(bytes, std::move(pred));
        default:
            return false;
        }
    }

    DDocumentSPtr    DDocument::load(shared_k, const std::filesystem::path&fp, SFormat sf)
    {
        DDocumentSPtr   ret;
        
        bool    loaded  = load(fp, sf, [&]() -> DDocument* {
            ret = std::make_shared<DDocument>();
            return ret.get();
        });
        
        if(loaded)
            return ret;
        return {};
    }
    
    DDocumentUPtr    DDocument::load(unique_k, const std::filesystem::path&fp, SFormat sf)
    {
        DDocumentUPtr   ret;
        bool    loaded  = load(fp, sf, [&]() -> DDocument* {
            ret = std::make_unique<DDocument>();
            return ret.get();
        });
        
        if(loaded)
            return ret;
        return {};
    }
    
    DDocument*       DDocument::load(raw_k, const std::filesystem::path&fp, SFormat sf)
    {
        DDocument*  ret = nullptr;
        bool    loaded  = load(fp, sf, [&]() -> DDocument* {
            ret = new DDocument;
            return ret;
        });
        if(loaded)
            return ret;
        if(ret)
            delete ret;
        return nullptr;
    }

    bool             DDocument::save(const std::filesystem::path&fp, SFormat fmt) const
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
