////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <art/shape/Vertices.hpp>

namespace yq::art {
    class Polyline : public Vertices {
        YQ_OBJECT_DECLARE(Polyline, Vertices)
    public:
        
        static void init_meta();
        
        Polyline(Doc&);
        ~Polyline();
        
        virtual size_t          vertex(count_k, minimum_k) const override { return 2; }
    };
}
