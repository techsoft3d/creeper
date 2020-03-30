#pragma once

#include <tree/CadModelTreeItem.h>

namespace ts3d {
    class ExchangeCadModelTreeItem : public CadModelTreeItem {
    public:
        ExchangeCadModelTreeItem( AbstractTreeItem const *parent, HPS::Exchange::CADModel const cadModel );
        virtual ~ExchangeCadModelTreeItem( void );

        virtual QVariant data( int role ) const override;
        virtual int childCount( void ) const override;

        HPS::Exchange::CADModel getExchangeCADModel( void ) const;
    private:
        virtual QVector<AbstractTreeItem*> createChildrenImpl( void ) const override;
    };
}
