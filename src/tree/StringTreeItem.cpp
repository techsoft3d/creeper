#include <tree/StringTreeItem.h>

ts3d::StringTreeItem::StringTreeItem( AbstractTreeItem const *parent, QString const &s )
    : AbstractTreeItem( parent ),
    _value( s ) {
}

// virtual
ts3d::StringTreeItem::~StringTreeItem( void ) {
}

// virtual
QVariant ts3d::StringTreeItem::data( int role ) const {
    switch(role) {
    case Qt::DisplayRole:
        return _value;
    default:
        return QVariant();
    }
}
