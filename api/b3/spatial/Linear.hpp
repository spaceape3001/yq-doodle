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
    
    #if 0
        Linear(const Param&);
        ~Linear();
        
        virtual void calc_points() override;
    #endif
    
    protected:
        Vector3D        m_focus = NAN;
        
    private:
        Tensor33D       m_matrix    = NAN;
        Tensor33D       m_inverse   = NAN;
        Vector3D        m_shift     = NAN;
        Point*          m_orign     = nullptr;
    };
}
