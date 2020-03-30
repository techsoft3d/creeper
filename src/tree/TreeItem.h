#pragma once

#include <tree/AbstractTreeItem.h>

namespace ts3d {
    class TreeItem : public AbstractTreeItem {
    public:
        TreeItem( AbstractTreeItem const *parent,
            std::function<QVariant(int)> data,
            std::function<int()> child_count,
            std::function<QVector<AbstractTreeItem*>(AbstractTreeItem const*)> create_children );
        virtual ~TreeItem( void );

        virtual QVariant data( int role ) const override;
        virtual int childCount( void ) const override;

    private:
        virtual QVector<AbstractTreeItem*> createChildrenImpl( void ) const override;

        std::function<QVariant( int )> _data;
        std::function<int()> _child_count;
        std::function<QVector<AbstractTreeItem*>( AbstractTreeItem const* )> _create_children;

    };

}
