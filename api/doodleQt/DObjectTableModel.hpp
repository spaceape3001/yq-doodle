////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/typedef/id.hpp>
#include <QAbstractTableModel>

namespace yq::doodle {
    class DObjectTableModel : public QAbstractTableModel {
        Q_OBJECT
    public:
    
        DObjectTableModel(Project&, std::function<IDVector()>&&, QObject*parent=nullptr);
    };
}
