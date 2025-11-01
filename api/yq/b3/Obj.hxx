////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/b3/Obj.hpp>
#include <yq/b3/Frame.hpp>

namespace yq::b3 {
    template <typename O>
    O* Obj::ancestor_as()
    {
        for(Frame* f = frame(); f; f=f->frame()){
            O*  a   = dynamic_cast<O*>(f);
            if(a)
                return a;
        }
        return nullptr;
    }

    template <typename O>
    const O* Obj::ancestor_as() const
    {
        return const_cast<Obj*>(this)->ancestor_as<O>();
    }
}
