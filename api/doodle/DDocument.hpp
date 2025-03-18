////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/keywords.hpp>
#include <doodle/bit/SStringMap.hpp>
#include <doodle/bit/SFormat.hpp>
#include <doodle/bit/ID.hpp>
#include <doodle/typedef/sdocument.hpp>
#include <doodle/typedef/sobject.hpp>
#include <doodle/typedef/revision.hpp>
#include <filesystem>
#include <vector>
#include <yq/typedef/string_maps.hpp>
#include <yq/typedef/string_sets.hpp>
#include <yq/typedef/xml.hpp>
#include <yq/text/IgCase.hpp>
#include <map>

namespace yq {
    class ByteArray;
}

namespace yq::doodle {
    class DObject;
    class DObjectInfo;
    struct ID;

    struct Census {
        std::string     title, description;
    };
    
    //! This is more about data than anything....
    class DDocument  {
    public:

        DDocument();
        ~DDocument();
    
        DObject*            object(ID);
        const DObject*      object(ID) const;
        
        static constexpr const char*    szExtB3     = "b3";
        static constexpr const char*    szExtXML    = "b3x";

        static bool             census(Census&, const std::filesystem::path&, SFormat fmt=SFormat::AUTO);
        
        static DDocumentSPtr    load(shared_k, const std::filesystem::path&, SFormat sf=SFormat::AUTO);
        static DDocumentUPtr    load(unique_k, const std::filesystem::path&, SFormat sf=SFormat::AUTO);
        static DDocument*       load(raw_k, const std::filesystem::path&, SFormat sf=SFormat::AUTO);
    
        bool                    save(const std::filesystem::path&, SFormat sf=SFormat::AUTO) const;
        
        std::string_view        attribute(const std::string&) const;
        void                    attribute_erase(const std::string&);
        string_set_t            attribute_keys() const;
        void                    attribute_set(const std::string&, const std::string&);
        void                    attribute_set(const std::string&, std::string&&);
        const string_map_t&     attributes() const;
        
        bool                    is_attribute(const std::string&) const;
        bool                    is_variable(const std::string&) const;

        std::string_view        variable(const std::string&) const;
        void                    variable_erase(const std::string&);
        string_set_t            variable_keys() const;
        void                    variable_set(const std::string&, const std::string&);
        void                    variable_set(const std::string&, std::string&&);
        const string_map_t&     variables() const;
    
        revision_t              revision() const { return m_revision; }
        
        const std::string&      title() const { return m_title; }
        void                    set_title(const std::string&);

        const std::string&      description() const { return m_description; }
        void                    set_description(const std::string&);
        const std::string&      notes() const { return m_description; }
        void                    set_notes(const std::string&);

        void                    bump();
        
        DObject*                create(const DObjectInfo&);
        
        template <SomeDObject S>
        S*                      create();
    
    private:
        friend class DObject;
        DDocument(DDocument&&) = delete;
        DDocument(const DDocument&) = delete;
        DDocument& operator=(const DDocument&) = delete;
        DDocument& operator=(DDocument&&) = delete;

        SStringMap                              m_attributes;
        SStringMap                              m_variables;
        std::string                             m_title;
        std::string                             m_description;
        std::string                             m_notes;
        std::vector<DObject*>                   m_objects;
        std::multimap<std::string,ID,IgCase>    m_uidmap;
        revision_t                              m_revision  = {};
        
        ID  insert(DObject*);
        
        void    uid_map(const std::string&, ID);
        void    uid_umap(const std::string&, ID);
        
        template <typename Pred> 
        static bool     load(const std::filesystem::path&, SFormat, Pred&&);
        template <typename Pred> 
        static bool     load_b3(ByteArray&, Pred&&);
        template <typename Pred> 
        static bool     load_xml(ByteArray&, Pred&&);
        
        bool            read(const XmlDocument&);
        
        bool            save_xml(const std::filesystem::path&) const;
        bool            save_b3(const std::filesystem::path&) const;

        static bool     census_xml(Census&, const std::filesystem::path&);
        static bool     census_b3(Census&, const std::filesystem::path&);
    };
}
