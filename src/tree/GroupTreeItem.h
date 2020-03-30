#pragma once

#include <tree/StringTreeItem.h>

namespace ts3d {
    class GroupTreeItem : public StringTreeItem {
    public:
        GroupTreeItem( AbstractTreeItem const *parent, QString const &s );
        virtual ~GroupTreeItem( void );

        void setChildren( QVector<AbstractTreeItem*> const &children );
    };
}
