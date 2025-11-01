////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/tachyon/api/Command.hpp>

namespace yq::doodle {
    class Doodle;

    class DoodleCommand : public tachyon::Command {
        YQ_OBJECT_DECLARE(DoodleCommand, tachyon::Command)
    public:

        static void init_meta();

    protected:
        DoodleCommand(const Header&);
        DoodleCommand(const DoodleCommand&, const Header& h);
        virtual ~DoodleCommand();
        
    private:
        DoodleCommand(const DoodleCommand&) = delete;
        DoodleCommand(DoodleCommand&&) = delete;
        DoodleCommand& operator=(const DoodleCommand&) = delete;
        DoodleCommand& operator=(DoodleCommand&&) = delete;
    };
}
