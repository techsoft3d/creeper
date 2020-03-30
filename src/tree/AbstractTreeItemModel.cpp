#include <tree/AbstractTreeItem.h>
#include <tree/AbstractTreeItemModel.h>

ts3d::AbstractTreeItemModel::AbstractTreeItemModel( QObject *parent, AbstractTreeItem *root )
    : QAbstractItemModel( parent ),
    _rootItem( root ) {
}

// virtual
ts3d::AbstractTreeItemModel::~AbstractTreeItemModel( void ) {
    delete _rootItem;
}

//virtual
QVariant ts3d::AbstractTreeItemModel::data( QModelIndex const &index, int role ) const {
    if(!index.isValid()) {
        return QVariant();
    }

    auto item = static_cast<AbstractTreeItem*>(index.internalPointer());
    return item ? item->data( role ) : QVariant();
}

//virtual 
Qt::ItemFlags ts3d::AbstractTreeItemModel::flags( QModelIndex const &index ) const {
    return index.isValid() ? QAbstractItemModel::flags( index ) : static_cast<Qt::ItemFlags>(0);
}

//virtual 
QVariant ts3d::AbstractTreeItemModel::headerData( int section, Qt::Orientation orientation, int role ) const {
    Q_UNUSED( section );
    return (orientation == Qt::Horizontal && role == Qt::DisplayRole) ?
        _rootItem->data( role ) : QVariant();
}

//virtual 
QModelIndex ts3d::AbstractTreeItemModel::index( int row, int column, QModelIndex const &parent ) const {
    if(!hasIndex( row, column, parent )) {
        return QModelIndex();
    }

    if(auto parentItem = parent.isValid() ? static_cast<AbstractTreeItem*>(parent.internalPointer()) : _rootItem) {
        if(auto childItem = parentItem->child( row )) {
            return createIndex( row, column, childItem );
        }
    }

    return QModelIndex();
}

//virtual 
QModelIndex ts3d::AbstractTreeItemModel::parent( QModelIndex const &index ) const {
    if(!index.isValid()) {
        return QModelIndex();
    }

    auto childItem = static_cast<AbstractTreeItem*>(index.internalPointer());
    auto parentItem = childItem->parent();

    if(nullptr == parentItem || parentItem == _rootItem) {
        return QModelIndex();
    }

    return createIndex( parentItem->row(), 0, const_cast<AbstractTreeItem*>( parentItem ) );
}

//virtual 
int ts3d::AbstractTreeItemModel::rowCount( QModelIndex const &parent ) const {
    if(parent.column() > 0) {
        return 0;
    }

    auto parentItem = parent.isValid() ? static_cast<AbstractTreeItem*>(parent.internalPointer()) : _rootItem;
    return parentItem ? parentItem->childCount() : 0;
}

//virtual 
int ts3d::AbstractTreeItemModel::columnCount( QModelIndex const &parent ) const {
    Q_UNUSED( parent );
    return 1;
    //return parent.isValid() ? 
    //    static_cast<AbstractTreeItem*>(parent.internalPointer())->columnCount() : _rootItem->columnCount();
}

