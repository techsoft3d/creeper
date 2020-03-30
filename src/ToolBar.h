#pragma once

namespace ts3d {
    class FileToolBar : public QToolBar {
        Q_OBJECT;
    public:
        FileToolBar( QWidget *parent );
        virtual ~FileToolBar( void );

    };
}