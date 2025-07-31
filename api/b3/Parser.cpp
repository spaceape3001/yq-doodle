////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Parser.hpp"
#include <yq/container/Map.hpp>
#include <yq/container/Set.hpp>
#include <yq/text/IgCase.hpp>
#include <yq/typedef/string_sets.hpp>
#include <fstream>

namespace yq::b3 {
    struct Parser::File {
        std::ifstream           io;
        std::filesystem::path   file;
        uint32_t                line    = 0;
        
        File()
        {
        }
        
        ~File()
        {
            if(is_open())
                io.close();
        }
        
        bool    is_open() const
        {
            return io.good() && io.is_open();
        }
        
        bool    open(const std::filesystem::path& name)
        {
            if(is_open())
                return false;
            io.open(name);
            if(!is_open())
                return false;
            
            file    = name;
            return true;
        }
    };
    
    struct Parser::Instruction {
        std::string     ins;
        uint64_t        flags = 0;
        uint64_t        args  = 0;   //!< minimum  number of arguments (unless ifArgExact is set)
        FNProc          proc  = nullptr;
    };


    struct Parser::Repo {
        Map<std::string, Instruction*,IgCase>   kIMap;
        StringSet                               keys;
    };

    Parser::Repo&        Parser::repo()
    {
        static Repo     _r;
        return _r;
    }
  

    int      Parser::addInstruction(const std::string&k, uint64_t flags, uint64_t args, FNProc fn)
    {
        static int counter  = 0;
        if(fn){
            Repo& _r    = repo();
            _r.kIMap[k]    = new Instruction{ .ins=k, .flags=flags, .args=args, .proc=fn};
            _r.keys << k;
        }
        return ++counter;
    }    

    const StringSet& Parser:: commandList()
    {
        return repo().keys;
    }

    ///////////////////////////////////////

    const std::filesystem::path&    Parser::file() const
    {
        static const std::filesystem::path& s_blank("(bad file)");
        const File* f   = top();
        if(!f)
            return s_blank;
        return f->file;
    }

    void            Parser::gripe(std::string_view)
    {
    }

    Parser::File*           Parser::top() 
    {
        if(m_files.empty())
            return nullptr;
        return m_files.top();
    }
    
    const Parser::File*     Parser::top() const 
    {
        if(m_files.empty())
            return nullptr;
        return m_files.top();
    }
}
