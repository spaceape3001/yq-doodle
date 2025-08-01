////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <b3/spatial/PointLine.hpp>

namespace yq::b3 {

    //! Used to denote a vertical feature (ie, wall)
    class Areal : public PointLine {
    public:
        Areal(Frame*, const ArgList& pts=ArgList());
        virtual ~Areal();
    };
}
