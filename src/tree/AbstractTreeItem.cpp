#include <tree/AbstractTreeItem.h>

ts3d::AbstractTreeItem::AbstractTreeItem( AbstractTreeItem const *parent ) 
: _parent( parent ),
_childrenCreated( false ) {
}
// virtual
ts3d::AbstractTreeItem::~AbstractTreeItem( void ) {
    qDeleteAll( _children );
}

// virtual
int ts3d::AbstractTreeItem::childCount( void ) const {
    createChildren();
    return _children.size();
}

ts3d::AbstractTreeItem *ts3d::AbstractTreeItem::child( int row ) const {
    createChildren();
    return row < _children.size() ? _children[row] : nullptr;
}

ts3d::AbstractTreeItem const *ts3d::AbstractTreeItem::parent( void ) const {
    return _parent;
}

QVariant ts3d::AbstractTreeItem::data( int ) const {
    return QVariant();
}

int ts3d::AbstractTreeItem::row( void ) const {
    return _parent ? _parent->_children.indexOf( const_cast<AbstractTreeItem*>( this ) ) : 0;
}

void ts3d::AbstractTreeItem::createChildren( void ) const {
    if(_childrenCreated) {
        return;
    }
    _children = createChildrenImpl();
    _childrenCreated = true;
}

// virtual
QVector<ts3d::AbstractTreeItem*> ts3d::AbstractTreeItem::createChildrenImpl( void ) const {
    return QVector<AbstractTreeItem*>();
}

