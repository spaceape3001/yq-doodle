////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <b3/Frame.hpp>
#include <yq/tensor/Tensor33.hpp>
#include <yq/vector/Vector3.hpp>

#ifdef NAN
    #undef NAN
#endif

namespace yq::b3 {
    class Linear : public Frame {
        YQ_OBJECT_DECLARE(Linear, Frame)
    public:
    
        Linear(const Param&);
        ~Linear();
        
        virtual void calc_points() override;

        virtual Vector3D        to_frame(const Vector3D&) const override;
        virtual Vector3D        to_parent(const Vector3D&) const override;
    
        void    set_focus(const Vector3D&);
        
        const Vector3D& focus() const { return m_focus; }
        const Tensor33D& matrix() const { return m_matrix; }
        const Tensor33D& inverse() const { return m_inverse; }
        const Vector3D& shift() const { return m_shift; }
    
    protected:
        Vector3D        m_focus     = NAN;
        
    private:
        Tensor33D       m_matrix    = NAN;
        Tensor33D       m_inverse   = NAN;
        Vector3D        m_shift     = NAN;
        Point*          m_origin    = nullptr;
    };
}
