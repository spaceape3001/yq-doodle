////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/DObject.hpp>

namespace yq::doodle {
    class PyMeta : public DObjectMeta {
    public:
        template <typename T> class Writer;
        PyMeta(std::string_view zName, DObjectMeta& base, const std::source_location& sl=std::source_location::current());
    };
    

    /*! A physical object
    
        This represents a physical object, the number represents the number of 
        coordinates needed to describe it.

        ## Attributes
    
        | Key | What                                    | Default                   |
        +-----+-----------------------------------------+---------------------------+
        | a   | CCW angle from +x axis (in degrees)     | atan2d(y,x)               |
        | ang | CCW angle from +x axis (in degrees)     | atan2d(y,x)               |
        | az  | CW angle from +y axis (in degrees)      | atan2d(x,y)               |
        | el  | angle upward (+z) from xy plane         | atan2d(z, sqrt(x^2+y^2))  |
        | r   | distance from origin                    | ...                       |
        | th  | CCW angle from +x axis (in radians)     | atan2(y,x)                |
        | x   | X-value (this will OVERRIDE the trig)   | ...                       |
        | y   | Y-value (this will OVERRIDE the trig)   | ...                       |
        | z   | Z-value (this will OVERRIDE the trig)   | ...                       |
        
        For radius, the default assesses the number of dimensions, returns the 
        relevant geometric mean of x, y, and z.
        
        For x, y, z; the values are checked first and used.  
        If those are missing AND radius "r" is present, the default will return
        the appropriate trigonometry based function leveraging the present angle 
        attributes.
    */
    class Py : public DObject {
        YQ_OBJECT_META(PyMeta)
        YQ_OBJECT_DECLARE(Py, DObject)
    public:
    
        virtual bool    supports(dimensions_k, uint8_t) const;
    
        /*! \brief Measure of dimensionality to the object
        
            \note this may be expensive, so cache the result!
        */
        virtual uint8_t dimensions(count_k) const = 0;
    
        static void init_meta();

        // Should always be valid (if defined), will default to empty otherwise
        std::string_view  rz() const;

        // Should always be valid (if defined), will default to empty otherwise
        std::string_view  x() const;

        // Should always be valid (if defined), will default to empty otherwise
        std::string_view  y() const;

        // Should always be valid (if defined), will default to empty otherwise
        std::string_view  z() const;
    
    protected:
        Py(Project&);
        Py(CopyAPI&, const Py&);
        ~Py();

        //! Remap IDs/pointers appropriately
        virtual void        remap(const Remapper&);
        
    private:
        Py(const Py&) = delete;
        Py(Py&&) = delete;
        Py& operator=(const Py&) = delete;
        Py& operator=(Py&&) = delete;
    };
}
