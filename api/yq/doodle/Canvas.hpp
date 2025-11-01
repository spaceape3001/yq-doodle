////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq::doodle {
    class Project;
    struct DObjectCopyAPI;
    
    class Canvas {
    public:
    
    protected:
        Canvas(const Project&);
        Canvas(const DObjectCopyAPI&, const Canvas&);
        virtual ~Canvas();
    };
}
