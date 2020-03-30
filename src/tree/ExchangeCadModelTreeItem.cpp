#include <tree/TreeItem.h>
#include <tree/ExchangeConfigurationTreeItem.h>
#include <tree/ExchangeCadModelTreeItem.h>

ts3d::ExchangeCadModelTreeItem::ExchangeCadModelTreeItem( AbstractTreeItem const *parent, HPS::Exchange::CADModel const cadModel )
    : CadModelTreeItem( parent, cadModel ) {
}

// virtual 
ts3d::ExchangeCadModelTreeItem::~ExchangeCadModelTreeItem( void ) {
}

// virtual
QVariant ts3d::ExchangeCadModelTreeItem::data( int role ) const {
    return CadModelTreeItem::data( role );
}

// virtual 
int ts3d::ExchangeCadModelTreeItem::childCount( void ) const {
    auto count = CadModelTreeItem::childCount();
    if(getExchangeCADModel().GetConfigurations().size()) {
        count++;
    }

    return count;
}

HPS::Exchange::CADModel ts3d::ExchangeCadModelTreeItem::getExchangeCADModel( void ) const {
    return HPS::Exchange::CADModel( getComponent() );
}

// virtual
QVector<ts3d::AbstractTreeItem*> ts3d::ExchangeCadModelTreeItem::createChildrenImpl( void ) const {
    auto children =  CadModelTreeItem::createChildrenImpl();
    auto e = getExchangeCADModel();
    auto configurations = e.GetConfigurations();
    if(configurations.size()) {
        auto configurationsItem = new TreeItem( this, []( int role ) {
            switch(role) {
            case Qt::DisplayRole:
                return QVariant( "Configurations" );
                break;
            default:
                return QVariant();
            }
        }, [&]() {
            return static_cast<int>(getExchangeCADModel().GetConfigurations().size());
        }, [&]( AbstractTreeItem const *parent ) {
            QVector<AbstractTreeItem*> children;
            for(auto configuration : getExchangeCADModel().GetConfigurations()) {
                children.append( new ExchangeConfigurationTreeItem( parent, configuration ) );
            }
            return children;
        } );
        children.append( configurationsItem );
    }
    return children;
}
