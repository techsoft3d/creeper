#pragma once

namespace ts3d {
    class CameraOrientation : public QAction {
            Q_OBJECT;
        public:
            CameraOrientation( QObject *owner, const QString &name, HPS::Vector front, HPS::Vector up );
            virtual ~CameraOrientation( void );
    };
}
