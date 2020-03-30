#include <tree/GroupTreeItem.h>

ts3d::GroupTreeItem::GroupTreeItem( AbstractTreeItem const *parent, QString const &s )
    : StringTreeItem( parent, s ) {
}

// virtual
ts3d::GroupTreeItem::~GroupTreeItem( void ) {
}

void ts3d::GroupTreeItem::setChildren( QVector<AbstractTreeItem*> const &children ) {
    _children = children;
    _childrenCreated = true;
}
