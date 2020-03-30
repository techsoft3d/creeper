#include <MainWindow.h>
#include <actions/CameraOrientation.h>
#include <HPSWidget.h>
#include <cmath>

ts3d::CameraOrientation::CameraOrientation( QObject *owner , const QString &name, HPS::Vector front, HPS::Vector up)
        : QAction( name , owner ) {
    setStatusTip( tr( "Change Camera Orientation", "Camera Orientation action status tip" ) );
    setToolTip( tr( "Change Camera Orientation", "Camera Orientation action tool tip text" ) );

    connect( this, &QAction::triggered, [name, front, up] {
        QSettings settings;
        auto const dir = settings.value( "CameraOrientation",  QVariant(name));

        auto hps_widget = ts3d::MainWindow::instance()->getCurrentHPSWidget();
        auto camera = hps_widget->getView().GetSegmentKey().GetCameraControl();

        auto camPos = HPS::Point();
        auto camTarget = HPS::Point();
        auto cameraFront = HPS::Vector();
        //auto cameraUp = HPS::Vector();

        camera.ShowPosition(camPos);
        camera.ShowTarget(camTarget);

        cameraFront.x = camPos.x - camTarget.x;
        cameraFront.y = camPos.y - camTarget.y;
        cameraFront.z = camPos.z - camTarget.z;

        auto camDist = sqrt(cameraFront.x*cameraFront.x + cameraFront.y*cameraFront.y + cameraFront.z*cameraFront.z);

        auto newPosition = HPS::Point(camTarget.x+camDist*front.x, camTarget.y+camDist*front.y, camTarget.z+camDist*front.z);

        camera.SetPosition(newPosition);
        camera.SetUpVector(up);

        hps_widget->getCanvas().Update();

    });

}

// virtual
ts3d::CameraOrientation::~CameraOrientation( void ) {
}
