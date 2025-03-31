////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/typedef/id.hpp>
#include <doodle/bit/ID.hpp>
#include <gluon/model/RowTableModel.hpp>

namespace yq::doodle {
    class Project;
    
    class DObjectTableModel : public gluon::RowTableModel<ID,Project&> {
        Q_OBJECT
    public:
    
        using table_t = gluon::RowTableModel<ID,Project&>;
    
    
        DObjectTableModel(Project&, IDProvider&&, QObject*parent=nullptr);
        ~DObjectTableModel();
        
        void    setRoot(ID);
        
        
    private:
        void            update();
        
        bool            fetch(IDVector&) const;
    
        Project&        m_project;
        IDProvider      m_provider;
        ID              m_root;
    };
}
