#include <MainWindow.h>
#include <actions/ProjectionMode.h>
#include <HPSWidget.h>

QString ts3d::ProjectionMode::getProjectionModeName( HPS::Camera::Projection mode ) {

    switch (mode) {
        case HPS::Camera::Projection::Perspective:
            return tr("Perspective", "Projection Mode");
            break;
        case HPS::Camera::Projection::Orthographic:
            return tr("Orthographic", "Projection Mode");
            break;
        case HPS::Camera::Projection::Stretched:
            return tr("Stretched", "Projection Mode");
            break;
        default:
            return "";
    }
}

ts3d::ProjectionMode::ProjectionMode( QObject *owner , HPS::Camera::Projection mode)
        : QAction( getProjectionModeName(mode), owner ) {
    setStatusTip( tr( "Change Projection Mode", "Projection Mode Change action status tip" ) );
    setToolTip( tr( "Change Projection Mode", "Change Projection Mode action tool tip text" ) );

    connect( this, &QAction::triggered, [mode] {
        QSettings settings;
        auto const dir = settings.value( "ProjectionMode",  QVariant(getProjectionModeName(mode)));

        if(auto hps_widget = ts3d::MainWindow::instance()->getCurrentHPSWidget()) {
            auto viewKey = hps_widget->getView().GetSegmentKey();
            viewKey.GetCameraControl().SetProjection( mode );
            hps_widget->getCanvas().Update();
        }
    });

}

// virtual
ts3d::ProjectionMode::~ProjectionMode( void ) {
}
