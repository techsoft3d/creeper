#pragma once

namespace ts3d {
    class ProjectionMode : public QAction {
            Q_OBJECT;
        public:
            static QString getProjectionModeName( HPS::Camera::Projection mode );
            ProjectionMode( QObject *owner, HPS::Camera::Projection mode );
            virtual ~ProjectionMode( void );
    };
}