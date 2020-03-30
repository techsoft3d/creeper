#include <Types.h>
#include <tree/ExchangeConfigurationTreeItem.h>

ts3d::ExchangeConfigurationTreeItem::ExchangeConfigurationTreeItem( AbstractTreeItem const *parent, HPS::Exchange::Configuration config )
    : AbstractTreeItem( parent ),
    _configuration( config ) {
}

ts3d::ExchangeConfigurationTreeItem::~ExchangeConfigurationTreeItem( void ) {

}

QVariant ts3d::ExchangeConfigurationTreeItem::data( int role ) const {
    switch(role) {
    case Qt::DisplayRole:
        return QString( "%1 [%2]" ).arg( QString( _configuration.GetName() ) ).arg( Types::toString( _configuration.Type() ) );
        break;
    default:
        break;
    }
    return QVariant();
}

// virtual
int ts3d::ExchangeConfigurationTreeItem::childCount( void ) const {
    return static_cast<int>(_configuration.GetSubconfigurations().size());
}

// virtual
QVector<ts3d::AbstractTreeItem*> ts3d::ExchangeConfigurationTreeItem::createChildrenImpl( void ) const {
    QVector<ts3d::AbstractTreeItem*> children;
    for(auto configuration : _configuration.GetSubconfigurations()) {
        children.append( new ExchangeConfigurationTreeItem( this, configuration ) );
    }
    return children;
}

