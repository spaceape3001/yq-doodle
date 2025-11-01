////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/b3/Doc.hpp>
#include <yq/b3/Parser.hpp>
#include <yq/b3/util/parse.hpp>
#include <yq/text/chars.hpp>
#include <yq/text/transform.hpp>
#include <iostream>

using namespace yq;
using namespace yq::b3;

////////////////////////////////////////////////////////////////////////////////

static bool cmdIf(Parser& p, const ArgList&pArgs, const ArgMap&nArgs) 
{
    if(p.eval_bool(pArgs.value(0), true)){
        return p.execute(pArgs.subarg(1), nArgs);
    } else {
        return true;
    }
}

YQ_B3_COMMAND("?", ifSubcommand, 1, cmdIf);

////////////////////////////////////////////////////////////////////////////////

static bool cmdIfNot(Parser& p, const ArgList&pArgs, const ArgMap&nArgs) 
{
    if(!p.eval_bool(pArgs.value(0), false)){
        return p.execute(pArgs.subarg(1), nArgs);
    } else {
        return true;
    }
}

YQ_B3_COMMAND("?!", ifSubcommand, 1, cmdIfNot);

////////////////////////////////////////////////////////////////////////////////

static bool cmdCommands(Parser&, const ArgList&, const ArgMap&)
{
    std::cout << "COMMANDS:\n";
    for(auto& s : Parser::command_list())
        std::cout << "  " << s << '\n';
    return true;
}

YQ_B3_COMMAND("cmds", ifNone, 0, cmdCommands);

////////////////////////////////////////////////////////////////////////////////

static bool cmdColor(Parser& p, const ArgList&pArgs, const ArgMap&nArgs) 
{
    if(pArgs.size() < 2){
        p.gripe("Too few arguments!");
        return false;
    }
    p.doc()->color(pArgs.values[0], pArgs.values[1]);
    return true;
}

YQ_B3_COMMAND("color", ifNone, 0, cmdColor);

////////////////////////////////////////////////////////////////////////////////


static bool cmdEcho(Parser&, const ArgList&pArgs, const ArgMap&)
{
    bool    first   = true;
    for(auto& v : pArgs.values){
        if(first)
            first = false;
        else
            std::cout << ' ';
        std::cout << v;
    }

    std::cout << '\n';
    return true;
}

YQ_B3_COMMAND("echo", ifArgExact, 1, cmdEcho);

////////////////////////////////////////////////////////////////////////////////

static bool cmdHide(Parser& p, const ArgList&pArgs, const ArgMap&)
{
    if(Obj* obj = p.last())
        obj->hide();
    return true;
}

YQ_B3_COMMAND("hide", ifNone, 0, cmdHide);


////////////////////////////////////////////////////////////////////////////////

static bool cmdInclude(Parser& p, const ArgList&pArgs, const ArgMap&)
{
    bool    success = true;
    for(const std::string& f : pArgs.values)
        success =  p.read_file(p.resolve(f), false) && success;
    return success;
}

YQ_B3_COMMAND("inc", ifNone, 1, cmdInclude);

////////////////////////////////////////////////////////////////////////////////

static bool cmdIncludeOnce(Parser& p, const ArgList&pArgs, const ArgMap&)
{
    bool    success = true;
    for(const std::string& f : pArgs.values)
        success =  p.read_file(p.resolve(f), true) && success;
    return success;
}

YQ_B3_COMMAND("inc?", ifNone, 1, cmdIncludeOnce);

////////////////////////////////////////////////////////////////////////////////


static bool cmdSet(Parser& p, const ArgList&, const ArgMap&nArgs)
{
    if(Obj* obj   = p.last()){
        for(auto &itr : nArgs.attrs)
            obj->attr(itr.first, SET, itr.second);
    }
    return true;
}
YQ_B3_COMMAND("set", ifNone, 0, cmdSet);


////////////////////////////////////////////////////////////////////////////////


static bool cmdSetIfNotPresent(Parser& p, const ArgList&, const ArgMap&nArgs)
{
    if(Obj* obj   = p.last()){
        for(auto &itr : nArgs.attrs)
            if(!obj->has_local_attribute(itr.first))
                obj->attr(itr.first, SET, itr.second);
    }
    return true;
}
YQ_B3_COMMAND("set?", ifNone, 0, cmdSetIfNotPresent);


////////////////////////////////////////////////////////////////////////////////

static bool cmdUnit(Parser& p, const ArgList& pArgs, const ArgMap&)
{
    if(pArgs.size() < 2){
        p.gripe("Needs two arguments unit <symbol> <value>");
        return false;
    }
    double  v   = pArgs.real(1., NAN);
    if(is_nan(v))
        return false;
    
    p.doc()->unit(pArgs.values[0], v);
    return true;
}

YQ_B3_COMMAND("unit", ifNone, 0, cmdUnit);

////////////////////////////////////////////////////////////////////////////////


static bool cmdVar(Parser& p, const ArgList&pArgs, const ArgMap&)
{
    if(Obj* obj = p.last()){
        size_t  n   = 0;
        StringSet   ordered;
        for(const std::string& z : pArgs.values){
            n   = std::max(n, z.size());
            ordered << z;
        }
    
        for(const std::string& z : ordered){
            std::cout.width(n);
            std::cout.setf(std::ios::left);
            std::cout << z;
            std::cout.width(1);
            std::cout << " := ";
            std::cout << obj->attr(z);
            std::cout << '\n';
        }
    }
    return true;
}

YQ_B3_COMMAND("var", ifNone, 1, cmdVar);

////////////////////////////////////////////////////////////////////////////////

