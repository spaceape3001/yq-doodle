////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Space4D.hpp"
#include "Space4D.hxx"
#include "Space4DMetaWriter.hpp"
#include <yq/math/Range.hpp>
#include <yq/shape/AxBox4.hpp>
#include <yq/shape/AxBox4.hxx>
#include <yq/doodle/utility.hpp>

YQ_OBJECT_IMPLEMENT(yq::doodle::Space4D)

namespace yq::doodle {
    Space4DMeta::Space4DMeta(std::string_view zName, SpaceMeta& base, const std::source_location& sl) : SpaceMeta(zName, base, sl)
    {
        set(Flag::SPACE);
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    void Space4D::init_meta()
    {
        auto w = writer<Space4D>();
        w.description("Space in 4D");
        w.property("hard", &Space4D::m_hard);
        w.property("soft", &Space4D::m_soft);
    }

    Space4D::Space4D(Project&prj) : Space(prj)
    {
    }
    
    Space4D::Space4D(CopyAPI&api, const Space4D&cp) : Space(api, cp), 
        m_hard(cp.m_hard), m_soft(cp.m_soft)
    {
    }

    Space4D::~Space4D()
    {
    }

    //! Remap IDs/pointers appropriately
    void        Space4D::remap(const Remapper&rMap)
    {
        Space::remap(rMap);
    }

    bool        Space4D::valid(hard_k, const Vector4D&pt) const
    {
        return 
            within(pt.x, m_hard.lo.x, m_hard.hi.x) &&
            within(pt.y, m_hard.lo.y, m_hard.hi.y) &&
            within(pt.z, m_hard.lo.z, m_hard.hi.z) &&
            within(pt.w, m_hard.lo.w, m_hard.hi.w)
        ;
    }
    
    bool        Space4D::valid(soft_k, const Vector4D&pt) const
    {
        return 
            within(pt.x, m_soft.lo.x, m_soft.hi.x) &&
            within(pt.y, m_soft.lo.y, m_soft.hi.y) &&
            within(pt.z, m_soft.lo.z, m_soft.hi.z) &&
            within(pt.w, m_soft.lo.w, m_soft.hi.w)
        ;
    }
}

