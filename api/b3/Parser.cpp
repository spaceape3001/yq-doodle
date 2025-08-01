////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Parser.hpp"

#include <b3/logging.hpp>
#include <b3/Doc.hpp>
#include <b3/Frame.hpp>
#include <b3/util/parse.hpp>
#include <yq/container/Map.hpp>
#include <yq/container/Set.hpp>
#include <yq/text/chars.hpp>
#include <yq/text/IgCase.hpp>
#include <yq/text/transform.hpp>
#include <yq/typedef/string_sets.hpp>
#include <yq/util/Safety.hpp>

#include <format>
#include <fstream>
#include <regex>

namespace yq::b3 {
    namespace {
        static std::string_view parseCode(std::regex_constants::error_type etype) 
        {
            switch (etype) {
            case std::regex_constants::error_collate:
                return "error_collate: invalid collating element request";
            case std::regex_constants::error_ctype:
                return "error_ctype: invalid character class";
            case std::regex_constants::error_escape:
                return "error_escape: invalid escape character or trailing escape";
            case std::regex_constants::error_backref:
                return "error_backref: invalid back reference";
            case std::regex_constants::error_brack:
                return "error_brack: mismatched bracket([ or ])";
            case std::regex_constants::error_paren:
                return "error_paren: mismatched parentheses(( or ))";
            case std::regex_constants::error_brace:
                return "error_brace: mismatched brace({ or })";
            case std::regex_constants::error_badbrace:
                return "error_badbrace: invalid range inside a { }";
            case std::regex_constants::error_range:
                return "erro_range: invalid character range(e.g., [z-a])";
            case std::regex_constants::error_space:
                return "error_space: insufficient memory to handle this regular expression";
            case std::regex_constants::error_badrepeat:
                return "error_badrepeat: a repetition character (*, ?, +, or {) was not preceded by a valid regular expression";
            case std::regex_constants::error_complexity:
                return "error_complexity: the requested match is too complex";
            case std::regex_constants::error_stack:
                return "error_stack: insufficient memory to evaluate a match";
            default:
                return "";
            }
        }

#if 0
        size_t     leadingWhitespaceCount(std::string_view text)
        {
            size_t     n=0, sz=text.size();
            for(; (n < sz) && is_space(text[n]); ++n)
                ;
            return n;
        }
#endif
        
        ssize_t    endsSlash(std::string_view text)
        {
            ssize_t     j   = 1;
            for(auto i = text.rbegin(); i!=text.rend(); ++i, ++j){
                if(is_space(*i))
                    continue;
                if( *i == '\\')
                    return j;
                if( *i != '\\')
                    return -1;
            }
            return j;
        }
        
        bool    isEmptyOrComment(std::string_view text)
        {
            for(auto i : text){
                if(i == '#')
                    return true;
                if(!is_space(i))
                    return false;
            }
            return true;
        }
    }


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
        std::string             ins;
        std::string             desc;
        uint64_t                flags = 0;
        size_t                  args  = 0;   //!< minimum  number of arguments (unless ifArgExact is set)
        FNProc                  proc  = nullptr;
        std::source_location    sl;
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
  

    int      Parser::add_instruction(const std::string&k, uint64_t flags, size_t args, FNProc fn)
    {
        static int counter  = 0;
        if(fn){
            Repo& _r    = repo();
            _r.kIMap[k]    = new Instruction{ .ins=k, .flags=flags, .args=args, .proc=fn};
            _r.keys << k;
        }
        return ++counter;
    }    

    const StringSet& Parser:: command_list()
    {
        return repo().keys;
    }

    ///////////////////////////////////////

    Parser::Parser(Doc* _doc) : m_doc(_doc)
    {
    }
    
    std::string     Parser::eval_value(const std::string&v, const std::string& def) const
    {
        if(v.empty())
            return def;
        if(v[0] == '\\')
            return v.substr(1);
        if(v[0] != '$')
            return v;
        if(!m_last)
            return def;
        return std::string(m_last->attr(v, def));
    }

    bool    Parser::eval_bool(std::string_view x, bool def) const
    {
        auto y  = eval_value(std::string(x));
        return parse::boolean(y, def);
    }

    bool    Parser::execute(const ArgList&pArgs, const ArgMap&nArgs)
    {
        static const Repo&  _r  = repo();

        if(pArgs.empty()){
            gripe("Need a command!");
            return false;
        }
        
        
        std::string    cmd(pArgs.value(0));
        Instruction* i  = _r.kIMap.get(cmd, nullptr);
        if(!i || !i->proc){
            gripe(std::format("Unrecognized command '{}'", cmd));
            return false;
        }

        if(pArgs.size() <= i->args){
            gripe("Insufficient arguments!");
            return false;
        }
        
        ArgList    subArgs = pArgs.subarg(1);
        return i->proc(*this, subArgs, nArgs);
    }


    const std::filesystem::path&    Parser::file() const
    {
        static const std::filesystem::path& s_blank("(bad file)");
        const File* f   = top();
        if(!f)
            return s_blank;
        return f->file;
    }

    Frame*          Parser::frame()
    {
        if(m_frames.empty())
            return nullptr;
        return m_frames.top();
    }

    void            Parser::frame_pop()
    {
        if(!m_frames.empty())
            m_frames.pop() -> end_frame();
    }

    void            Parser::frame_push(Frame*f)
    {
        if(!f)
            return;
        m_frames << f;
        m_last      = f;
    }


    void            Parser::gripe(const std::string& msg)
    {
        if(File*f = top()){
            b3Error << "Error (" << f->file << '@' << f->line << "): " << msg;
        } else {
            b3Error << "Error: " << msg;
        }
    }

    bool            Parser::read_file(const std::filesystem::path& cand, bool fSkipIfAlreadyDone)
    {
        if(m_files.empty()){
            m_frames.clear();
            m_frames << m_doc;
            m_last      = m_doc;
        }
        
        std::filesystem::path   toOpen;
        
        if(File* f = top()){
            if(cand.is_relative()){
                std::filesystem::path   pp  = f->file.parent_path();
                toOpen  = pp / cand;
            }
        }
        
        if(toOpen.empty())
            toOpen  = cand;
        if(fSkipIfAlreadyDone && m_included.contains(toOpen))
            return true;
        m_included << toOpen;
        
        File    file;
        m_files << &file;
        auto xpop = safety([&](){ m_files.pop(); });
        if(!file.open(toOpen))
            return false;
            
        std::string_view    error;

        bool    success = true;

        //  In theory, this should match all components......    
        try {
            
                /*
            In future, want something like.... (however, for now, keep old syntax)
            
                rbox:easter jcloset.se 3m 3m
                    autowall = true
                    label    = "Easter's Bedroom" 
                    fill     = lavender_pink
                    
                    wall sw se 
                        win uc=150 uw=2m
                    wall nw ne
                        door uc=50cm uw=80cm
            
                
                */
                

            // Regex expressions are such a pain....
            std::regex  bit("(\\S+=\"[^\"]*\"|\\S+=\\S+|\"[^\"]*\"|\\S+)");
            std::regex  arg1("(\\S+)=\"([^\"]*)\"");
            std::regex  arg2("(\\S+)=(\\S+)");
            std::regex  quoted("\"([^\"]*)\"");
        
            auto readline = [&]() -> std::string {
                if(file.io.eof() || file.io.bad())
                    return {};
                    
                ++file.line;
                char        text[1024];
                file.io.getline(text, sizeof(text)-1);
                text[sizeof(text)-1] = '\0';
                return text;
            };
            
        
            //std::regex  bit("(\\w\\S*=\"[^\"]*\"|\\S+=\\S+|\"([^\"]*\"|\\S+)");
            //std::regex  arg("\\w\\S+=\"([^\"]*)\"|\\S+=\\S+");

            //  Eventually, we'll be fancy... in the meanwhile....
            while(file.io.good() && !file.io.eof()){
                std::string fline   = readline();
                do {
                    ssize_t q   = endsSlash(fline);
                    if(q < 0)
                        break;
                    fline       = fline.substr(0,fline.size()-q) + readline();
                } while(file.io.good() && !file.io.eof());
                    
                if(isEmptyOrComment(fline))
                    continue;

                //size_t     ws  = leadingWhitespaceCount(fline);
                std::string    qline(trimmed(fline));

                Vector<std::string>     toks;
                std::sregex_token_iterator i(qline.begin(), qline.end(), bit, 1);
                std::sregex_token_iterator j;
                while(i != j)
                {
                    toks << (*i++);
                }

                
                ArgList     pArgs;
                ArgMap      nArgs;
                
                int     n   = 0;
                for(const std::string &tok : toks){
                    ++n;
                    std::smatch sm;
                    if(std::regex_match(tok, sm, arg1) || 
                        std::regex_match(tok, sm, arg2)
                    ){
                        nArgs.attrs[sm[1]] = sm[2];
                    } else if(std::regex_match(tok, sm, quoted)){
                        pArgs.values << sm[1];
                    } else {
                        pArgs.values << tok;
                    }
                }
                
                success = execute(pArgs, nArgs) && success;
                
            }
        }
        catch(std::regex_error& ex)   // just to swallow...
        {
            error   = parseCode(ex.code());
        }
    
        if(!error.empty()){
            b3Error << "Syntax error (" << file.file << "@" << file.line << "): " << error;
            return false;
        }
        return success;
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
