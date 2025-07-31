////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <b3/Frame.hpp>
#include <b3/Context.hpp>
#include <yq/shape/AxBox2.hpp>

#ifdef NAN
    #undef NAN
#endif

namespace yq::b3 {
    class Doc : public Frame, public Context {
        YQ_OBJECT_DECLARE(Doc, Frame)
    public:
        Doc(const Param&);
        virtual ~Doc();
        
        const ArgList&  args() const { return m_args; }
        
        virtual void    calc_points() override;
        
        double      west_bound() const { return m_bounds.lo.x; }
        double      east_bound() const { return m_bounds.hi.x; }
        double      south_bound() const { return m_bounds.lo.y; }
        double      north_bound() const { return m_bounds.hi.y; }
        
        bool    has_terrain() const;
        
        const std::filesystem::path&    file() const { return m_file; }
        
        typedef bool    (*FNHandler)(Doc&);
        static int              add_handler(const std::string& key, const std::string& description, FNHandler proc);
        static const StringSet& handlers();
        static FNHandler        handler(const std::string&);
        static bool             has_handler(const std::string&);
        static std::string      description(const std::string&);

    private:
        struct Handler;
        struct Repo;
        
        static Repo& repo();
    
        ArgList                 m_args;
        Vector<Object*>         m_objects;
        Vector<Point*>          m_points;
        AxBox2D                 m_edges = NAN;
        AxBox2D                 m_bounds = NAN;
        std::filesystem::path   m_file;
        
        static bool any_terrain(const Obj*);
    };
}

#define YQ_B3_HANDLER(name, desc, proc) \
    static int YQ_B3_INTERNAL_CMD_NAME(__LINE__) = Doc::addHandler(name, desc, proc)

