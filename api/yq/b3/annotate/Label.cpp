////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Label.hpp"
#include <yq/b3/ObjMetaWriter.hpp>
#include <yq/text/join.hpp>

YQ_OBJECT_IMPLEMENT(yq::b3::Label)

namespace yq::b3 {
    Label::Label(const Param& p) : Obj(p)
    {
        m_position.x    = p.args.length(0);
        m_position.y    = p.args.length(1);
        auto subargs    = p.args.subarg(2);
        m_message       = join(subargs.values, ' ');
    }
    
    Label::~Label()
    {
    }
}

