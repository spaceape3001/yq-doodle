////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/container/forward.hpp>
#include <yq/text/IgCase.hpp>
#include <yq/typedef/vector2.hpp>
#include <yq/typedef/vector3.hpp>

namespace yq {
    template <typename> struct AxCorners2;
    template <typename> struct AxCorners3;
    template <typename> class Ref;
}

namespace yq::b3 {
    enum class PenStyle {
        Solid,
        Dash,
        Dot,
        DashDot
    };

    using IntegerSet    = Set<int>;

    struct Color;

    struct CoordN;
    struct CountN;
    struct Brush;
    struct Pen;
    struct Font;
    struct PointN;
    struct SizeN;
    struct VectorN;
    
    class Style;
    
    struct Doc;
    struct Frame;
    struct Obj;
    struct Point;
    struct Terrain;
    
    class TerPage;
    using TerPagePtr        = Ref<TerPage>;
    using TerPageCPtr       = Ref<const TerPage>;
    
    using ObjMap            = Map<std::string,Obj*,IgCase>;
    using ObjMMap           = MultiMap<std::string,Obj*,IgCase>;
    using DoubleMap         = Map<std::string,double,IgCase>;
    using StyleMap          = Map<std::string,Style*,IgCase>;
    
    
    using AxCorners23D          = AxCorners2<Vector3D>;
    using AxCorners33D          = AxCorners3<Vector3D>;

    class Context;
    extern thread_local Context*    g_context;
}

#define YQ_B3_INTERNAL_CMD_NAME2(a)    reg_##a
#define YQ_B3_INTERNAL_CMD_NAME(a)    YQ_B3_INTERNAL_CMD_NAME2(a)
