////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/b3/Doc.hpp>
#include <yq/b3/Parser.hpp>
#include <yq/b3/annotate/Circle.hpp>
#include <yq/b3/annotate/Label.hpp>
#include <yq/b3/annotate/Polyline.hpp>

using namespace yq;
using namespace yq::b3;

////////////////////////////////////////////////////////////////////////////////

static bool cmdCircle(Parser& p, const ArgList& pArgs, const ArgMap& nArgs)
{
    if(pArgs.size() < 3){
        p.gripe("Circle needs arguments!");
        return false;
    }
    p << new Circle({.args=pArgs, .attrs=nArgs, .frame=p.frame()});
    return true;
}

YQ_B3_COMMAND("circle", ifNone, 3, cmdCircle);

////////////////////////////////////////////////////////////////////////////////

static bool cmdLabel(Parser& p, const ArgList& pArgs, const ArgMap& nArgs)
{
    if(pArgs.size() < 3){
        p.gripe("Label needs arguments!");
        return false;
    }

    p << new Label({.args=pArgs, .attrs=nArgs, .frame=p.frame()});
    return true;
}
YQ_B3_COMMAND("label", ifNone, 3, cmdLabel);

////////////////////////////////////////////////////////////////////////////////

static bool cmdPolygon(Parser& p, const ArgList&pArgs, const ArgMap&nArgs) 
{
    p << new Polyline({.args=pArgs, .attrs=nArgs, .frame=p.frame()}, true);
    return true;
}
YQ_B3_COMMAND("pg", ifNone, 0, cmdPolygon);

////////////////////////////////////////////////////////////////////////////////

static bool cmdPolyline(Parser& p, const ArgList&pArgs, const ArgMap&nArgs) 
{
    p << new Polyline({.args=pArgs, .attrs=nArgs, .frame=p.frame()}, false);
    return true;
}
YQ_B3_COMMAND("pl", ifNone, 0, cmdPolyline);

////////////////////////////////////////////////////////////////////////////////
