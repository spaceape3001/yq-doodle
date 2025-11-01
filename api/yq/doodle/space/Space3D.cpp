////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Space3D.hpp"
#include "Space3D.hxx"
#include "Space3DMetaWriter.hpp"
#include <yq/doodle/utility.hpp>

YQ_OBJECT_IMPLEMENT(yq::doodle::Space3D)

#ifdef NAN
#undef NAN
#endif

namespace yq::doodle {
    Space3DMeta::Space3DMeta(std::string_view zName, SpaceMeta& base, const std::source_location& sl) : SpaceMeta(zName, base, sl)
    {
        set(Flag::SPACE);
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    void Space3D::init_meta()
    {
        auto w = writer<Space3D>();
        w.description("Space in 3D");
        w.property("hard", &Space3D::m_hard);
        w.property("soft", &Space3D::m_soft);
    }

    Space3D::Space3D(Project&prj) : Space(prj)
    {
    }
    
    Space3D::Space3D(CopyAPI&api, const Space3D&cp) : Space(api, cp),
        m_hard(cp.m_hard), m_soft(cp.m_soft)
    {
    }

    Space3D::~Space3D()
    {
    }


    //! Remap IDs/pointers appropriately
    void        Space3D::remap(const Remapper&rMap)
    {
        Space::remap(rMap);
    }

    bool        Space3D::valid(hard_k, const Vector3D&pt) const
    {
        return 
            within(pt.x, m_hard.lo.x, m_hard.hi.x) &&
            within(pt.y, m_hard.lo.y, m_hard.hi.y) &&
            within(pt.z, m_hard.lo.z, m_hard.hi.z)
        ;
    }
    
    bool        Space3D::valid(soft_k, const Vector3D&pt) const
    {
        return 
            within(pt.x, m_soft.lo.x, m_soft.hi.x) &&
            within(pt.y, m_soft.lo.y, m_soft.hi.y) &&
            within(pt.z, m_soft.lo.z, m_soft.hi.z)
        ;
    }
}

