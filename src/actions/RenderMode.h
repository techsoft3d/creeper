#pragma once

namespace ts3d {
    class RenderMode : public QAction {
            Q_OBJECT;
    public:
        static QString getRenderModeName( HPS::Rendering::Mode mode );
        RenderMode( QObject *owner, HPS::Rendering::Mode mode );
        virtual ~RenderMode( void );
    };
}