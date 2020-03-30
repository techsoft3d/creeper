#pragma once

namespace ts3d {
    class ExitAction : public QAction {
        Q_OBJECT;
    public:
        ExitAction( QObject *owner );
        virtual ~ExitAction( void );
    };
}