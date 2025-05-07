////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/Py.hpp>
#include <yq/typedef/vector1.hpp>

namespace yq::doodle {
    class Py1DInfo : public PyInfo {
    public:
        template <typename T> class Writer;
        Py1DInfo(std::string_view zName, PyInfo& base, const std::source_location& sl=std::source_location::current());
    };

    struct Vector1S {
        std::string x;
    };
    
    /*! A physical object in 1D
    */
    class Py1D : public Py {
        YQ_OBJECT_INFO(Py1DInfo)
        YQ_DOODLE_DECLARE(Py1D, Py)
    public:
    
        static constexpr const char *szX     = "x";
    
        virtual uint8_t dimensions(count_k) const final { return 1; }

        static void init_info();
        
        std::string_view    x() const;

    protected:
        Py1D(Project&);
        Py1D(Project&, const Py1D&);
        ~Py1D();

        //! Remap IDs/pointers appropriately
        virtual void        remap(const Remapper&);
        
        
    private:
        Py1D(const Py1D&) = delete;
        Py1D(Py1D&&) = delete;
        Py1D& operator=(const Py1D&) = delete;
        Py1D& operator=(Py1D&&) = delete;
    };

}
