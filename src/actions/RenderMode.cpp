#include <MainWindow.h>
#include <actions/RenderMode.h>
#include <HPSWidget.h>

QString ts3d::RenderMode::getRenderModeName( HPS::Rendering::Mode mode ) {

        switch (mode) {
            case HPS::Rendering::Mode::Gouraud:
                return tr("Gouraud", "Rendering Mode");
                break;
            case HPS::Rendering::Mode::GouraudWithLines:
                return tr("Gouraud With Lines", "Rendering Mode");
                break;
            case HPS::Rendering::Mode::Flat:
                return tr("Flat", "Rendering Mode");
                break;
            case HPS::Rendering::Mode::FlatWithLines:
                return tr("Flat With Lines", "Rendering Mode");
                break;
            case HPS::Rendering::Mode::Phong:
                return tr("Phong", "Rendering Mode");
                break;
            case HPS::Rendering::Mode::PhongWithLines:
                return tr("Phong With Lines", "Rendering Mode");
                break;
            case HPS::Rendering::Mode::HiddenLine:
                return tr("Hidden Line", "Rendering Mode");
                break;
            case HPS::Rendering::Mode::FastHiddenLine:
                return tr("Fast Hidden Line", "Rendering Mode");
                break;
            case HPS::Rendering::Mode::Wireframe:
                return tr("Wireframe", "Rendering Mode");
                break;
            default:
                return "";
        }

    }

ts3d::RenderMode::RenderMode( QObject *owner , HPS::Rendering::Mode mode)
        : QAction( getRenderModeName(mode), owner ) {
    setStatusTip( tr( "Change Render Mode", "Render Mode Change action status tip" ) );
    setToolTip( tr( "Change Render Mode", "Change Render Mode action tool tip text" ) );

    connect( this, &QAction::triggered, [mode] {
        QSettings settings;
        auto const dir = settings.value( "RenderMode",  QVariant(getRenderModeName(mode)));

        auto hps_widget = ts3d::MainWindow::instance()->getCurrentHPSWidget();
        hps_widget->getView().SetRenderingMode( mode );
        hps_widget->getCanvas().Update();

    });

}

// virtual
ts3d::RenderMode::~RenderMode( void ) {
}
