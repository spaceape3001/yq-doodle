////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/doodleVk/command/DoodleCommand.hpp>

#include <yq/tachyon/api/CommandMetaWriter.hpp>

YQ_OBJECT_IMPLEMENT(yq::doodle::DoodleCommand)

namespace yq::doodle {
    DoodleCommand::DoodleCommand(const Header&h) : tachyon::Command(h)
    {
    }

    DoodleCommand::DoodleCommand(const DoodleCommand& cp, const Header& h) : tachyon::Command(cp, h)
    {
    }
    
    DoodleCommand::~DoodleCommand()
    {
    }
    
    ////////////////////////////////////////////////////////////////////////////

    void DoodleCommand::init_meta()
    {
        auto w = writer<DoodleCommand>();
        w.description("Doodle command base class");
    }
}
