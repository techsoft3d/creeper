#pragma once

namespace ts3d {
    class AbstractTreeItem;
    class AbstractTreeItemModel : public QAbstractItemModel {
        Q_OBJECT;
    public:
        AbstractTreeItemModel( QObject *parent, AbstractTreeItem *root );
        virtual ~AbstractTreeItemModel( void );

        virtual QVariant data( QModelIndex const &index, int role ) const override;
        virtual Qt::ItemFlags flags( QModelIndex const &index ) const override;
        virtual QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const override;
        virtual QModelIndex index( int row, int column, QModelIndex const &parent = QModelIndex() ) const override;
        virtual QModelIndex parent( QModelIndex const &index ) const override;
        virtual int rowCount( QModelIndex const &parent = QModelIndex() ) const override;
        virtual int columnCount( QModelIndex const &parent = QModelIndex() ) const override;
    
    private:
        AbstractTreeItem *_rootItem;
    };
}