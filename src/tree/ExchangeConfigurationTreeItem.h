#pragma once

#include <tree/AbstractTreeItem.h>

namespace ts3d {
    class ExchangeConfigurationTreeItem : public AbstractTreeItem {
    public:
        ExchangeConfigurationTreeItem( AbstractTreeItem const *parent, HPS::Exchange::Configuration config );
        virtual ~ExchangeConfigurationTreeItem( void );

        virtual QVariant data( int role ) const override;
        virtual int childCount( void ) const override;

    private:
        virtual QVector<AbstractTreeItem*> createChildrenImpl( void ) const override;

        HPS::Exchange::Configuration _configuration;
    };
}
