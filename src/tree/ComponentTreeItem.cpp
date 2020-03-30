#include <Types.h>
#include <tree/ComponentTreeItem.h>

ts3d::ComponentTreeItem::ComponentTreeItem( AbstractTreeItem const *parent, HPS::Component const component )
    : AbstractTreeItem( parent ),
    _component( component ) {
}

// virtual
ts3d::ComponentTreeItem::~ComponentTreeItem( void ) {
}

// virtual
QVariant ts3d::ComponentTreeItem::data( int role ) const {
    switch(role) {
    case Qt::DisplayRole:
        return QString( "%1 [HPS::Type::%2]" ).arg( QString(_component.GetName()) ).arg( Types::toString( _component.Type() ) );
    default:
        return QVariant();
    }
}

// virtual 
int ts3d::ComponentTreeItem::childCount( void ) const {
    return static_cast<int>(_component.GetSubcomponents().size());
}

HPS::Component ts3d::ComponentTreeItem::getComponent( void ) const {
    return _component;
}

// virtual
QVector<ts3d::AbstractTreeItem*> ts3d::ComponentTreeItem::createChildrenImpl( void ) const {
    QVector<AbstractTreeItem*> children;
    for(auto subcomponent : _component.GetSubcomponents()) {
        children.push_back( new ComponentTreeItem( this, subcomponent ) );
    }
    return children;
}
