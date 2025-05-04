////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Space4D.hpp"
#include <yq/math/Range.hpp>

namespace yq::doodle {
    constexpr RangeD    Space4D::bounds(hard_k, x_k) const
    {
        return { m_hard.lo.x, m_hard.hi.x };
    }
    
    constexpr RangeD    Space4D::bounds(hard_k, y_k) const
    {
        return { m_hard.lo.y, m_hard.hi.y };
    }
    
    constexpr RangeD    Space4D::bounds(hard_k, z_k) const
    {
        return { m_hard.lo.z, m_hard.hi.z };
    }
    
    constexpr RangeD    Space4D::bounds(hard_k, w_k) const
    {
        return { m_hard.lo.w, m_hard.hi.w };
    }
    
    constexpr double    Space4D::bounds(hard_k, low_k, x_k) const
    {
        return m_hard.lo.x;
    }
    
    constexpr double    Space4D::bounds(hard_k, low_k, y_k) const
    {
        return m_hard.lo.y;
    }
    
    constexpr double    Space4D::bounds(hard_k, low_k, z_k) const
    {
        return m_hard.lo.z;
    }
    
    constexpr double    Space4D::bounds(hard_k, low_k, w_k) const
    {
        return m_hard.lo.w;
    }

    constexpr double    Space4D::bounds(hard_k, high_k, x_k) const
    {
        return m_hard.hi.x;
    }
    
    constexpr double    Space4D::bounds(hard_k, high_k, y_k) const
    {
        return m_hard.hi.y;
    }
    
    constexpr double    Space4D::bounds(hard_k, high_k, z_k) const
    {
        return m_hard.hi.z;
    }
    
    constexpr double    Space4D::bounds(hard_k, high_k, w_k) const
    {
        return m_hard.hi.w;
    }
    
    constexpr RangeD    Space4D::bounds(soft_k, x_k) const
    {
        return { m_soft.lo.x, m_soft.hi.x };
    }
    
    constexpr RangeD    Space4D::bounds(soft_k, y_k) const
    {
        return { m_soft.lo.y, m_soft.hi.y };
    }
    
    constexpr RangeD    Space4D::bounds(soft_k, z_k) const
    {
        return { m_soft.lo.z, m_soft.hi.z };
    }
    
    constexpr RangeD    Space4D::bounds(soft_k, w_k) const
    {
        return { m_soft.lo.w, m_soft.hi.w };
    }
    
    constexpr double    Space4D::bounds(soft_k, low_k, x_k) const
    {
        return m_soft.lo.x;
    }
    
    constexpr double    Space4D::bounds(soft_k, low_k, y_k) const
    {
        return m_soft.lo.y;
    }
    
    constexpr double    Space4D::bounds(soft_k, low_k, z_k) const
    {
        return m_soft.lo.z;
    }
    
    constexpr double    Space4D::bounds(soft_k, low_k, w_k) const
    {
        return m_soft.lo.w;
    }

    constexpr double    Space4D::bounds(soft_k, high_k, x_k) const
    {
        return m_soft.hi.x;
    }
    
    constexpr double    Space4D::bounds(soft_k, high_k, y_k) const
    {
        return m_soft.hi.x;
    }
    
    constexpr double    Space4D::bounds(soft_k, high_k, z_k) const
    {
        return m_soft.hi.x;
    }
    
    constexpr double    Space4D::bounds(soft_k, high_k, w_k) const
    {
        return m_soft.hi.x;
    }
}

