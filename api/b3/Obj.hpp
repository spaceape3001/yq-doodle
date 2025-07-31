////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <b3/typedef.hpp>
#include <b3/util/ArgList.hpp>
#include <b3/util/ArgMap.hpp>

#include <yq/core/Flags.hpp>
#include <yq/core/Object.hpp>
#include <yq/typedef/axbox2.hpp>
#include <yq/typedef/axbox3.hpp>
#include <yq/typedef/vector2.hpp>
#include <yq/typedef/vector3.hpp>

namespace yq::b3 {

    class Obj;

    class ObjMeta : public ObjectMeta {
    public:
        template <typename> class Writer;
        ObjMeta(std::string_view zName, ObjectMeta& base, const std::source_location& sl=std::source_location::current());
    
    private:
        typedef bool    (*MakerFN)(void*, Obj*);
        std::map<Meta::id_t,MakerFN>      m_makers;
    
    };

    struct Frame;
    struct Doc;
    
    template <class O>
    concept SomeObj        = std::derived_from<O,Obj>;

    class Obj : public Object {
        YQ_OBJECT_META(ObjMeta)
        YQ_OBJECT_DECLARE(Obj, Object)
    public:
    
        enum class F {
            Hide,
            Terrain
        };
        
        struct Param {
            ArgList         args;               //!< positional arguments to the command
            ArgMap          attrs;              //!< named arguments to the command
            std::string     name;               //!< object name
            Frame*          parent  = nullptr;  //!< containing frame (root will be null)
        };
    
        Obj(const Param&);
        virtual ~Obj();
        
        template <typename O>
        O*                  ancestor_as();
        template <typename O>
        const O*            ancestor_as() const;

        std::string_view    attr(const std::string&, std::string_view def={}) const;
        const ArgMap&       attrs() const { return m_attrs; }

        virtual void        calc_points(){}
        void                collect_args(DoubleMap&, std::span<const std::string>) const;

        Doc*                document() { return m_doc; }
        const Doc*          document() const { return m_doc; }
        virtual Obj*        find(std::string_view);
        virtual const Obj*  find(std::string_view) const;
        auto                flags() const { return m_flags; }
        Frame*              frame() { return m_frame; }
        const Frame*        frame() const { return m_frame; }
        std::string         full_name() const;
        bool                is_terrain() const;
        bool                is_hidden() const;
        std::string_view    name() const { return m_name; }
        Frame*              parent() { return m_frame; }
        const Frame*        parent() const { return m_frame; }

        AxCorners23D        to_global(const AxBox2D&) const;
        AxCorners33D        to_global(const AxBox3D&) const;
        virtual Vector3D    to_global(const Vector3D&) const;
        virtual Vector3D    to_global_msl(const Vector2D&, double) const;
        virtual Vector3D    to_global_agl(const Vector2D&, double) const;

        virtual Vector3D    to_local(const Vector3D&) const;

        std::string_view    type_name() const;


    private:
        friend class Doc;
        friend class Frame;

        ArgMap              m_attrs;
        Doc*                m_doc       = nullptr;
        Flags<F>            m_flags;
        Frame*              m_frame     = nullptr;
        std::string         m_full;
        std::string         m_name;
    };

}
