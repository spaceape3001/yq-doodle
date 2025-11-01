////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <gluon/model/ColumnModel.hxx>
#include <gluon/model/RowTableModel.hxx>

#include "DObjectTableModel.hpp"
#include <yq/algorithm/DiffEngine.hpp>
#include <yq/container/reverse.hpp>

namespace yq::doodle {
    DObjectTableModel::DObjectTableModel(Project& prj, IDProvider&&fn, QObject*parent) : 
        table_t(parent,prj), m_project(prj), m_provider(std::move(fn))
    {
    }
    
    DObjectTableModel::~DObjectTableModel()
    {
    }

    bool    DObjectTableModel::fetch(IDVector&result) const
    {
        if(auto p = std::get_if<IDProviderV>(&m_provider)){
            result = (*p)();
            return true;
        } else if(auto p = std::get_if<IDProviderP>(&m_provider)){
            result = (*p)(m_project);
            return true;
        } else if(auto p = std::get_if<IDProviderPI>(&m_provider)){
            result = (*p)(m_project, m_root);
            return true;
        } else {
            return false;
        }
    }

    void    DObjectTableModel::setRoot(ID i)
    {
        m_root  = i;
        update();
    }

    void    DObjectTableModel::update()
    {
        IDVector current;
        if(!fetch(current))
            return ;
        updateRows(current);
    }
}

#include "moc_DObjectTableModel.cpp"
