////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Space2D.hpp"
#include "Space2D.hxx"
#include "Space2DMetaWriter.hpp"
#include <doodle/utility.hpp>

YQ_OBJECT_IMPLEMENT(yq::doodle::Space2D)

namespace yq::doodle {
    Space2DMeta::Space2DMeta(std::string_view zName, SpaceMeta& base, const std::source_location& sl) : SpaceMeta(zName, base, sl)
    {
        set(Flag::SPACE);
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    void Space2D::init_meta()
    {
        auto w = writer<Space2D>();
        w.description("Space in 2D");
        w.property("hard", &Space2D::m_hard);
        w.property("soft", &Space2D::m_soft);
    }

    Space2D::Space2D(Project&prj) : Space(prj)
    {
    }
    
    Space2D::Space2D(CopyAPI&api, const Space2D&cp) : Space(api, cp), m_hard(cp.m_hard), m_soft(cp.m_soft)
    {
    }

    Space2D::~Space2D()
    {
    }


    //! Remap IDs/pointers appropriately
    void        Space2D::remap(const Remapper&rMap)
    {
        Space::remap(rMap);
    }

    bool        Space2D::valid(hard_k, const Vector2D&pt) const
    {
        return 
            within(pt.x, m_hard.lo.x, m_hard.hi.x) &&
            within(pt.y, m_hard.lo.y, m_hard.hi.y)
        ;
    }
    
    bool        Space2D::valid(soft_k, const Vector2D&pt) const
    {
        return 
            within(pt.x, m_soft.lo.x, m_soft.hi.x) &&
            within(pt.y, m_soft.lo.y, m_soft.hi.y)
        ;
    }
}

