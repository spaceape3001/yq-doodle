////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/b3/Doc.hpp>
#include <yq/b3/Parser.hpp>
#include <yq/b3/spatial/Linear.hpp>

using namespace yq;
using namespace yq::b3;

////////////////////////////////////////////////////////////////////////////////


static bool cmdStartFrame(Parser& p, const ArgList&pArgs, const ArgMap&) 
{
    Frame*      fpush   = dynamic_cast<Frame*>(
                            pArgs.empty() ? p.last() : p.last()->find(pArgs.values[0]) 
                          );
    if(!fpush){
        p.gripe("Frame not found!");
        p.frame_push(p.frame());
        return false;
    }
    
    p.frame_push(fpush);
    return true;
}

YQ_B3_COMMAND("{", ifNone, 0, cmdStartFrame);


////////////////////////////////////////////////////////////////////////////////


static bool cmdStopFrame(Parser& p, const ArgList&, const ArgMap&)
{
    p.frame_pop();
    return true;
}

YQ_B3_COMMAND("}", ifNone, 0, cmdStopFrame);

////////////////////////////////////////////////////////////////////////////////

static bool cmdNewFrame(Parser& p, const ArgList&pArgs, const ArgMap& nArgs)
{
    p << new Linear({.args=pArgs, .attrs=nArgs, .frame=p.frame()});
    return true;
}
YQ_B3_COMMAND("frame", ifNone, 0, cmdNewFrame);


////////////////////////////////////////////////////////////////////////////////
