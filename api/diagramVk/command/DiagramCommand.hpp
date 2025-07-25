////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <tachyon/api/Command.hpp>

namespace yq::diagram {
    class Diagram;

    class DiagramCommand : public tachyon::Command {
        YQ_OBJECT_DECLARE(DiagramCommand, tachyon::Command)
    public:

        static void init_meta();

    protected:
        DiagramCommand(const Header&);
        DiagramCommand(const DiagramCommand&, const Header& h);
        virtual ~DiagramCommand();
        
    private:
        DiagramCommand(const DiagramCommand&) = delete;
        DiagramCommand(DiagramCommand&&) = delete;
        DiagramCommand& operator=(const DiagramCommand&) = delete;
        DiagramCommand& operator=(DiagramCommand&&) = delete;
    };
}
