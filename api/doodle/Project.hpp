////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/keywords.hpp>
#include <doodle/bit/SStringMap.hpp>
#include <doodle/bit/ID.hpp>
#include <doodle/io/SFormat.hpp>
#include <doodle/typedef/project.hpp>
#include <doodle/typedef/dobject.hpp>
#include <doodle/typedef/id.hpp>
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
    class Project  {
    public:
        using object_map_t  = std::map<ID,DObject*>;

        //  DO NOT USE IN PRODUCTION (it's for meta purposes)
        static Project&         testing(Project* p = nullptr);

        Project();
        virtual ~Project();
    
        DObject*            object(ID);
        const DObject*      object(ID) const;
        
        static constexpr const char*    szExtB3     = "d3";
        static constexpr const char*    szExtXML    = "d3x";
        
        //! Returns the first object with UID
        template <SomeDObject S=DObject>
        S*                      object(uid_k, const std::string&);
        template <SomeDObject S=DObject>
        const S*                object(uid_k, const std::string&) const;

        static bool             census(Census&, const std::filesystem::path&, SFormat fmt=SFormat::AUTO);
        
        static ProjectSPtr      load(shared_k, const std::filesystem::path&, SFormat sf=SFormat::AUTO);
        static ProjectUPtr      load(unique_k, const std::filesystem::path&, SFormat sf=SFormat::AUTO);
        static Project*         load(raw_k, const std::filesystem::path&, SFormat sf=SFormat::AUTO);
    
        virtual bool            save(const std::filesystem::path&, SFormat sf=SFormat::AUTO) const;
        
        std::string_view        attribute(const std::string&) const;
        void                    attribute_erase(const std::string&);
        string_set_t            attribute_keys() const;
        void                    attribute_set(const std::string&, const std::string&);
        void                    attribute_set(const std::string&, std::string&&);
        const string_map_t&     attributes() const;
        
        bool                    contains(ID) const;
        
        bool                    is_empty() const;
        
        bool                    is_attribute(const std::string&) const;
        bool                    is_attribute(ID, const std::string&) const;
 
        //bool                    is_variable(const std::string&) const;

        //std::string_view        variable(const std::string&) const;
        //void                    variable_erase(const std::string&);
        //string_set_t            variable_keys() const;
        //void                    variable_set(const std::string&, const std::string&);
        //void                    variable_set(const std::string&, std::string&&);
        //const string_map_t&     variables() const;
    
        revision_t              revision() const { return m_revision; }
        
        const std::string&      title() const { return m_title; }
        void                    set_title(const std::string&);

        const std::string&      description() const { return m_description; }
        void                    set_description(const std::string&);
        const std::string&      notes() const { return m_description; }
        void                    set_notes(const std::string&);

        void                    bump();
        
        DObject*                create(const DObjectInfo&);
        
        const object_map_t&     objects() const { return m_objects; }
        
        template <SomeDObject S>
        S*                      create();
        
        const std::vector<ID>&  roots() const { return m_roots; }
    
        using generator_fn  = std::function<Project*()>;
        static bool     load(const std::filesystem::path&, SFormat, generator_fn&&);
        
        #ifdef foreach
        #undef foreach
        #endif
        
        template <SomeDObject S=DObject, typename Pred>
        auto    foreach(Pred&&);
        template <SomeDObject S=DObject, typename Pred>
        auto    foreach(Pred&&) const;
        
        template <SomeDObject S=DObject, typename Pred>
        auto    foreach(uid_k, const std::string&, Pred&&);
        template <SomeDObject S=DObject, typename Pred>
        auto    foreach(uid_k, const std::string&, Pred&&) const;

        size_t          count(object_k) const { return m_objects.size(); }
        size_t          count(object_k, uid_k, const std::string&) const;
        

    private:
        friend class DObject;
        Project(Project&&) = delete;
        Project(const Project&) = delete;
        Project& operator=(const Project&) = delete;
        Project& operator=(Project&&) = delete;

        SStringMap                              m_attributes;
        SStringMap                              m_variables;
        std::string                             m_title;
        std::string                             m_description;
        std::string                             m_notes;
        object_map_t                            m_objects;
        std::vector<ID>                         m_roots;
        std::multimap<std::string,ID,IgCase>    m_uidmap;
        revision_t                              m_revision  = {};
        ID::id_t                                m_nextID    = 1;
        ID                                      m_loading   = {};
        
        ID  insert(DObject*);
        
        void    uid_map(const std::string&, ID);
        void    uid_umap(const std::string&, ID);
        
        static bool     load_b3(ByteArray&, generator_fn&&);
        static bool     load_xml(ByteArray&, generator_fn&&);
        
        bool            read(const XmlDocument&);
        void            write(XmlDocument&) const;
        
        bool            save_xml(const std::filesystem::path&) const;
        bool            save_b3(const std::filesystem::path&) const;

        static bool     census_xml(Census&, const std::filesystem::path&);
        static bool     census_b3(Census&, const std::filesystem::path&);
    };
}
