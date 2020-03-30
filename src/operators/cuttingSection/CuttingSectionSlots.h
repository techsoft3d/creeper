#pragma once
#include <MainWindow.h>
#include <operators/cuttingSection/CuttingSectionCommands.h>

namespace ts3d {
    class CuttingSectionSlots : public QObject {
        Q_OBJECT;
    public:
        CuttingSectionSlots( void );
        virtual ~CuttingSectionSlots( void );

        void getCurrentHPSWidget( void );
        void addErasePlaneX( bool on );
        void addErasePlaneY( bool on );
        void addErasePlaneZ( bool on );
        void setUnsetSectioning( bool set );
        void showHidePlanes( bool show );
        void cancelCuttingSection(void);

    public slots:
        void onInvertX( bool checked );
        void onInvertY( bool checked );
        void onInvertZ( bool checked );

        void getCurrentStatus( bool &planeX, bool &invertX, bool &planeY, bool &invertY, bool &planeZ, bool &invertZ, bool &setSectioning, bool &showPlanes );

    private:
        ts3d::HPSWidget *_hpsWidget;
        CuttingSectionCommands *_cuttingSectionCommands;

        bool _invertX;
        bool _invertY;
        bool _invertZ;
        bool _sectioning;
    };
}
