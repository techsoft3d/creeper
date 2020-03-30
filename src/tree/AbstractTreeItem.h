#pragma once
namespace ts3d {

    class AbstractTreeItem {
    public:
        AbstractTreeItem( AbstractTreeItem const *parent );
        virtual ~AbstractTreeItem( void );

        virtual int childCount( void ) const;

        AbstractTreeItem *child( int row ) const;
        AbstractTreeItem const *parent( void ) const;

        virtual QVariant data( int role ) const = 0;

        int row( void ) const;

    protected:
        void createChildren( void ) const;
        virtual QVector<AbstractTreeItem*> createChildrenImpl( void ) const;

        AbstractTreeItem const *_parent;
        mutable bool _childrenCreated;
        mutable QVector<AbstractTreeItem*> _children;
    };
}