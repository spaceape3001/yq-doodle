////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/art/obj/Obj.hpp>

namespace yq::art {

    //! Reference to another object (whether it's an active object or a template)
    class Instance : public Obj {
        YQ_OBJECT_DECLARE(Instance, Obj)
    public:
        Instance(Doc&);
        ~Instance();
        
        const reference_t& reference() const { return m_reference; }
        
    private:
        reference_t     m_reference;
    };
}
