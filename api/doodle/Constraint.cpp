////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Constraint.hpp"
#include "ConstraintMetaWriter.hpp"

YQ_OBJECT_IMPLEMENT(yq::doodle::Constraint)

namespace yq::doodle {
    ConstraintMeta::ConstraintMeta(std::string_view zName, DObjectMeta& base, const std::source_location& sl) : DObjectMeta(zName, base, sl)
    {
        set(Flag::CONSTRAINT);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    void Constraint::init_meta()
    {
        auto w = writer<Constraint>();
        w.description("Constraint");
    }

    Constraint::Constraint(Project&prj) : DObject(prj)
    {
    }
    
    Constraint::Constraint(CopyAPI& api, const Constraint& cp) : DObject(api, cp)
    {
    }
    
    Constraint::~Constraint()
    {
    }


    void        Constraint::remap(const Remapper&rMap)
    {
        DObject::remap(rMap);
    }
}

