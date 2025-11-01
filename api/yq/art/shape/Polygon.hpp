////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/art/shape/Vertices.hpp>

namespace yq::art {
    class Polygon : public Vertices {
        YQ_OBJECT_DECLARE(Polygon, Vertices)
    public:
        
        static void init_meta();
        
        Polygon(Doc&);
        ~Polygon();
        
        virtual size_t          vertex(count_k, minimum_k) const override { return 3; }
    };
}
