////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/DObject.hpp>

namespace yq::doodle {
    class ConstraintInfo : public DObjectInfo {
    public:
        template <typename T> class Writer;
        ConstraintInfo(std::string_view zName, DObjectInfo& base, const std::source_location& sl=std::source_location::current());
    };
    

    /*! \brief A constraint

        A constraint is something that spaces... could be distance, organization, etc.
    */
    class Constraint : public DObject {
        YQ_OBJECT_INFO(ConstraintInfo)
        YQ_DOODLE_DECLARE(Constraint, DObject)
    public:
    
        static void init_info();
    
    protected:
        Constraint(Project&);
        Constraint(CopyAPI&, const Constraint&);
        ~Constraint();

        //! Remap IDs/pointers appropriately
        virtual void        remap(const Remapper&) = 0;
        
        
    private:
        Constraint(Constraint&&) = delete;
        Constraint(const Constraint&) = delete;
        Constraint& operator=(const Constraint&) = delete;
        Constraint& operator=(Constraint&&) = delete;
    };
}
