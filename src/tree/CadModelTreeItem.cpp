#include <tree/CadModelTreeItem.h>

ts3d::CadModelTreeItem::CadModelTreeItem( AbstractTreeItem const *parent, HPS::CADModel const cadModel ) 
: ComponentTreeItem( parent, cadModel ) {
}

// virtual 
ts3d::CadModelTreeItem::~CadModelTreeItem( void ) {
}

// virtual
QVariant ts3d::CadModelTreeItem::data( int role ) const {
    return ComponentTreeItem::data( role );
}

// virtual 
int ts3d::CadModelTreeItem::childCount( void ) const {
    return ComponentTreeItem::childCount();
}

HPS::CADModel ts3d::CadModelTreeItem::getCADModel( void ) const {
    return HPS::CADModel( getComponent() );
}

// virtual
QVector<ts3d::AbstractTreeItem*> ts3d::CadModelTreeItem::createChildrenImpl( void ) const {
    return ComponentTreeItem::createChildrenImpl();
}
