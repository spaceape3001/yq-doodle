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
        struct PointRepo;

        Doc*            operator->() { return m_doc; }
        const Doc*      operator->() const { return m_doc; }

        typedef bool    (*FNProc)(Parser&, const ArgList&, const ArgMap&);
        
        Parser(Doc* _doc);
        
            
        bool            readFile(const std::filesystem::path&, bool fSkipIfAlreadyDone);
        //void            gripe(const std::string& message);
        bool            execute(const ArgList&, const ArgMap&);

        std::string     evalValue(const std::string&, const std::string& def={}) const;
    //    void        setValue(const QString&, const QString&);
        
        File*           top();
        const File*     top() const;

        bool            hasFrames() const { return !m_frames.empty(); }

        void            framePush(Frame*);
        void            framePop();
        Frame*          frame();
        
        //void            makePoint(PointType, const zvec3&, const QString&);
        //bool            makeFrame(FrameType, const ArgList&, const Args&);
        
        void            gripe(std::string_view);
        
        static const StringSet&  commandList();
        
        void            install(Obj* obj, const ArgMap&);
        
        void            setLast(Obj*);
        Obj*            last() { return m_last; }
        
        void            operator<<(Obj*obj)
        {
            m_last  = obj;
        }
        
    //    static Instruction      s_kITable[];
        
        Doc*            doc() { return m_doc; }
        const Doc*      doc() const { return m_doc; }

        static int      addInstruction(const std::string&, uint64_t flags, uint64_t args, FNProc);

        PointRepo&      pointRepo();
        
        const std::filesystem::path&    file() const;
    
    
    private:
        struct Repo;
        struct Instruction;
        
        static Repo&        repo();

        Doc*                        m_doc   = nullptr;
        Stack<File*>                m_files;
        Stack<Frame*>               m_frames;
        Set<std::filesystem::path>  m_included;
        Obj*                        m_last  = nullptr;
        PointRepo*                  m_points;    
    };
}


#define YQ_B3_COMMAND(name, flags, args, proc)    \
    static int  YQ_B3_INTERNAL_CMD_NAME(__LINE__)  = ::yq::b3::Parser::addInstruction(name, flags, args, proc);
