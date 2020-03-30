#pragma once

#include <tree/ComponentTreeItem.h>

namespace ts3d {
    class CadModelTreeItem : public ComponentTreeItem {
    public:
        CadModelTreeItem( AbstractTreeItem const *parent, HPS::CADModel const cadModel );
        virtual ~CadModelTreeItem( void );

        virtual QVariant data( int role ) const override;
        virtual int childCount( void ) const override;

        HPS::CADModel getCADModel( void ) const;
    protected:
        virtual QVector<AbstractTreeItem*> createChildrenImpl( void ) const override;
    };
}
