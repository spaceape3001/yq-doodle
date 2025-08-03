////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <b3/logging.hpp>
#include <b3/Doc.hpp>
#include <yq/container/StringMap.hpp>
#include <yq/container/StringVector.hpp>
#include <yq/core/BasicApp.hpp>
#include <yq/core/Logging.hpp>
#include <yq/file/FileUtils.hpp>
#include <yq/meta/Meta.hpp>
#include <yq/process/PluginLoader.hpp>
#include <yq/text/split.hpp>

using namespace yq;
using namespace yq::b3;


void    print_help(const char* arg0)
{
    std::cerr   << "USAGE: " << arg0 << " [in-file] [command] arg=...\n";
    std::cerr << '\n';
    std::cerr << "Commands:\n";
    auto& handlers   = Doc::handlers();
    size_t n = 0;
    for(auto& k : handlers)
        n   = std::max(n, k.size());
    
    for(auto& k : handlers){
        std::cerr << "    ";
        std::cerr.width(n);
        std::cerr.setf(std::ios::left);
        std::cerr << k;
        std::cerr.width(1);
        std::cerr << " := " << Doc::description(k) << "\n";
    }
}

std::pair<ArgMap, ArgList>    parse_cmdline(int argc, char* argv[])
{
    ArgMap      attrs;
    ArgList     args;

    int n;
    for(n=3; n<argc; ++n){
        std::string arg(argv[n]);
        if(arg == "--")
            break;
        
        auto bits   = split(arg, '=');
        if(bits.empty())
            continue;
            
        if(bits.size() > 3){
            b3Warning << "Arguments are of [name]=[value]... extra after second '=' will be ignored";
        }
        
        std::string     k(bits[0]);
        
        if(bits.size() == 1){
            attrs.attrs[k]  = "true";
        } else {
            attrs.attrs[k]  = std::string(bits[1]);
        }
    }
    while(++n < argc)
        args.values << std::string(argv[n]);
    
    return {attrs, args};
}

int main(int argc, char* argv[])
{
    if(argc < 3){
        print_help(argv[0]);
        return -1;
    }
    
    std::filesystem::path   file(argv[1]);
    if(!file_exists(file)){
        std::cerr << argv[0] << ": missing file '" << argv[1] << "'\n";
        return -1;
    }

    std::string     cmd(argv[2]);

    log_to_std_error();
    BasicApp    app(argc, argv);
    Meta::init();
    load_plugin_dir(BasicApp::app_dir() / "plugin" / "b3");
    Meta::freeze();

    auto handler        = Doc::handler(cmd);
    if(!handler){
        std::cerr << argv[0] << ": invalid command\n";
        return -1;
    }

    //  TODO
    auto [attrs, args]  = parse_cmdline(argc, argv);
    attrs.attrs["cmd"]  = cmd;
    attrs.attrs[cmd] = "true";
    attrs.attrs["__" + cmd + "__"] = "true";
    
    {
        Doc doc({.args=args, .attrs=attrs});
        if(!doc.parse_file(file)){
            b3Error << "Parsing failure";
            return -1;
        }
        
        handler(doc);
    }

    if(int cnt = Obj::net_allocations()){
        b3Alert << "Net allocations is not zero, it's " << cnt;
    }
    
    return 0;
}
