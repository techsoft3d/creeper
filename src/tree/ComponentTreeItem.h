#pragma once

#include <tree/AbstractTreeItem.h>

namespace ts3d {
    class ComponentTreeItem : public AbstractTreeItem {
    public:
        ComponentTreeItem( AbstractTreeItem const *parent, HPS::Component const component );
        virtual ~ComponentTreeItem( void );

        virtual QVariant data( int role ) const override;
        virtual int childCount( void ) const override;

        HPS::Component getComponent( void ) const;
    
    protected:
        virtual QVector<AbstractTreeItem*> createChildrenImpl( void ) const override;
    
    private:
        HPS::Component const _component;
    };

}
