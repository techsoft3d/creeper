#pragma once

#include <tree/AbstractTreeItem.h>

namespace ts3d {
    class StringTreeItem : public AbstractTreeItem {
    public:
        StringTreeItem( AbstractTreeItem const *parent, QString const &s );
        virtual ~StringTreeItem( void );
        virtual QVariant data( int role ) const;
    private:
        QString _value;
    };

}
