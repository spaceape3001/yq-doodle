////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Space2D.hpp"
#include <yq/math/Range.hpp>

namespace yq::doodle {
    constexpr RangeD    Space2D::bounds(hard_k, x_k) const
    {
        return { m_hard.lo.x, m_hard.hi.x };
    }
    
    constexpr RangeD    Space2D::bounds(hard_k, y_k) const
    {
        return { m_hard.lo.y, m_hard.hi.y };
    }
    
    constexpr double    Space2D::bounds(hard_k, low_k, x_k) const
    {
        return m_hard.lo.x;
    }
    
    constexpr double    Space2D::bounds(hard_k, low_k, y_k) const
    {
        return m_hard.lo.y;
    }
    
    constexpr double    Space2D::bounds(hard_k, high_k, x_k) const
    {
        return m_hard.hi.x;
    }
    
    constexpr double    Space2D::bounds(hard_k, high_k, y_k) const
    {
        return m_hard.hi.y;
    }
    
    constexpr RangeD    Space2D::bounds(soft_k, x_k) const
    {
        return { m_soft.lo.x, m_soft.hi.x };
    }
    
    constexpr RangeD    Space2D::bounds(soft_k, y_k) const
    {
        return { m_soft.lo.y, m_soft.hi.y };
    }
    
    constexpr double    Space2D::bounds(soft_k, low_k, x_k) const
    {
        return m_soft.lo.x;
    }
    
    constexpr double    Space2D::bounds(soft_k, low_k, y_k) const
    {
        return m_soft.lo.y;
    }
    
    constexpr double    Space2D::bounds(soft_k, high_k, x_k) const
    {
        return m_soft.hi.x;
    }
    
    constexpr double    Space2D::bounds(soft_k, high_k, y_k) const
    {
        return m_soft.hi.x;
    }
}

