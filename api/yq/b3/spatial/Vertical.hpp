////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <b3/spatial/PointLine.hpp>

namespace yq::b3 {

    //! Used to denote a vertical feature (ie, wall)
    class Vertical : public PointLine {
    public:
        Vertical(Frame*, const ArgList& pts=ArgList());
        virtual ~Vertical();
    };
}
