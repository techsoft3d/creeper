#include <tree/TreeItem.h>

ts3d::TreeItem::TreeItem( AbstractTreeItem const *parent,
    std::function<QVariant( int )> data,
    std::function<int()> child_count,
    std::function<QVector<AbstractTreeItem*>( AbstractTreeItem const* )> create_children )
: AbstractTreeItem( parent ),
_data( data ),
_child_count( child_count ),
_create_children( create_children ) {
}

// virtual 
ts3d::TreeItem::~TreeItem( void ) {

}

// virtual 
QVariant ts3d::TreeItem::data( int role ) const {
    return _data( role );
}

// virtual 
int ts3d::TreeItem::childCount( void ) const {
    return _child_count();
}

// virtual 
QVector<ts3d::AbstractTreeItem*> ts3d::TreeItem::createChildrenImpl( void ) const {
    return _create_children(this);
}

