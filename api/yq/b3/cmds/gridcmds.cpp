////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <b3/Doc.hpp>
#include <b3/Parser.hpp>
#include <b3/grid/HexGrid.hpp>
#include <b3/grid/PieGrid.hpp>
#include <b3/grid/RectGrid.hpp>
#include <b3/grid/TriGrid.hpp>
#include <yq/text/match.hpp>

using namespace yq;
using namespace yq::b3;

////////////////////////////////////////////////////////////////////////////////

static bool cmdGrid(Parser& p, const ArgList& pArgs, const ArgMap& nArgs)
{
    auto type   = pArgs.value(0);
    
    if(is_similar(type, "hex")){
        p << new HexGrid({.args=pArgs, .attrs=nArgs, .frame=p.frame()});
    } else if(is_similar(type, "pie")){
        p << new PieGrid({.args=pArgs, .attrs=nArgs, .frame=p.frame()});
    } else if(is_similar(type, "tri")){
        p << new TriGrid({.args=pArgs, .attrs=nArgs, .frame=p.frame()});
    } else
        p << new RectGrid({.args=pArgs, .attrs=nArgs, .frame=p.frame()});
    return true;
}
YQ_B3_COMMAND("grid", ifNone, 1, cmdGrid);
