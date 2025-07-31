////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/container/Stack.hpp>
#include <yq/container/Set.hpp>
#include <yq/typedef/string_sets.hpp>
#include <b3/typedef.hpp>
#include <filesystem>
#include <memory>

namespace yq::b3 {
    #ifdef IF
        #undef IF
    #endif
    
    class Obj;
    class Doc;
    class Frame;
    class ArgList;
    class ArgMap;

    enum IFlags {
        ifNone          = 0x0,
        ifSubcommand    = 0x1,  //  is a subcommand
        ifArgExact      = 0x2   //  position args must match
    };
    
    class Parser {
    public:
        struct File;
        struct Points;

        typedef bool    (*FNProc)(Parser&, const ArgList&, const ArgMap&);

        static const StringSet& command_list();
        static int              add_instruction(const std::string&, uint64_t flags, size_t args, FNProc);


        Doc*            operator->() { return m_doc; }
        const Doc*      operator->() const { return m_doc; }
        
        Parser(Doc* _doc);
        
        
        Doc*            doc() { return m_doc; }
        const Doc*      doc() const { return m_doc; }
            
        //void            gripe(const std::string& message);

        std::string     eval_value(const std::string&, const std::string& def={}) const;
        
        bool            execute(const ArgList&, const ArgMap&);

          //void        setValue(const QString&, const QString&);
        

        const std::filesystem::path&    file() const;

        Frame*          frame();
        void            frame_pop();
        void            frame_push(Frame*);
        
        void            gripe(const std::string&);

        bool            has_frames() const { return !m_frames.empty(); }

        void            install(Obj* obj, const ArgMap&);

        Obj*            last() { return m_last; }

        Points&         point_repo();

        bool            read_file(const std::filesystem::path&, bool fSkipIfAlreadyDone);

        void            set_last(Obj*);

        File*           top();
        const File*     top() const;

        //void            makePoint(PointType, const zvec3&, const QString&);
        //bool            makeFrame(FrameType, const ArgList&, const Args&);
        
        void            operator<<(Obj*obj)
        {
            m_last  = obj;
        }
        
    //    static Instruction      s_kITable[];
    
    
    private:
        struct Repo;
        struct Instruction;
        
        static Repo&        repo();

        friend class Doc;

        Doc*  const                 m_doc;
        Stack<File*>                m_files;
        Stack<Frame*>               m_frames;
        Set<std::filesystem::path>  m_included;
        Obj*                        m_last      = nullptr;
        Points*                     m_points    = nullptr;    
    };
}


#define YQ_B3_COMMAND(name, flags, args, proc)    \
    static int  YQ_B3_INTERNAL_CMD_NAME(__LINE__)  = ::yq::b3::Parser::add_instruction(name, flags, args, proc);
