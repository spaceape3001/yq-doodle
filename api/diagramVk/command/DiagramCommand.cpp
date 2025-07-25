////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <diagramVk/command/DiagramCommand.hpp>

#include <tachyon/api/CommandMetaWriter.hpp>

YQ_OBJECT_IMPLEMENT(yq::diagram::DiagramCommand)

namespace yq::diagram {
    DiagramCommand::DiagramCommand(const Header&h) : tachyon::Command(h)
    {
    }

    DiagramCommand::DiagramCommand(const DiagramCommand& cp, const Header& h) : tachyon::Command(cp, h)
    {
    }
    
    DiagramCommand::~DiagramCommand()
    {
    }
    
    ////////////////////////////////////////////////////////////////////////////

    void DiagramCommand::init_meta()
    {
        auto w = writer<DiagramCommand>();
        w.description("Diagram command base class");
    }
}
