#include <Application.h>
#include <HPSWidget.h>
#include <HPSMdiSubWindow.h>

ts3d::HPSMdiSubWindow::HPSMdiSubWindow( QWidget *parent, HPS::CADModel const model, QSize const &initialSize )
    : QMdiSubWindow( parent ),
    _cadModel( model ),
    _isCadModelValid( true ),
    _widget( createHPSWidget() ) {

    setWidget( _widget );
    resize( initialSize );
    _widget->getView().AttachModel( model.GetModel() );
    _widget->getView().FitWorld();
}

ts3d::HPSMdiSubWindow::HPSMdiSubWindow( QWidget *parent, HPS::Model const model, QSize const &initialSize )
    : QMdiSubWindow( parent ),
    _isCadModelValid( false ),
    _widget( createHPSWidget() ) {

    setWidget( _widget );
    resize( initialSize );
    _widget->getView().AttachModel( model );
    _widget->getView().FitWorld();
}

HPS::View ts3d::HPSMdiSubWindow::getView( void ) const {
    return _widget ? _widget->getView() : HPS::View();
}

HPS::Canvas ts3d::HPSMdiSubWindow::getCanvas( void ) const {
    return _widget ? _widget->getCanvas() : HPS::Canvas();
}

HPS::Model ts3d::HPSMdiSubWindow::getModel( void ) const {
    return getView().GetAttachedModel();
}

HPS::CADModel ts3d::HPSMdiSubWindow::getCADModel( void ) const {
    return _cadModel;
}

bool ts3d::HPSMdiSubWindow::isCADModelValid( void ) const {
    return _isCadModelValid;
}

// virtual 
void ts3d::HPSMdiSubWindow::closeEvent( QCloseEvent *event ) {
    emit closed();
    QMdiSubWindow::closeEvent( event );
}


ts3d::HPSWidget *ts3d::HPSMdiSubWindow::createHPSWidget( void ) {
    auto hps_widget = new HPSWidget( this );
    hps_widget->getView().GetSegmentKey().InsertDistantLight( HPS::DistantLightKit().SetDirection( HPS::Vector( 1, 0, -1.5f ) ).SetCameraRelative( true ) );
    hps_widget->getView().GetAxisTriadControl().SetVisibility( true ).SetInteractivity( true );
    hps_widget->getView().GetNavigationCubeControl().SetVisibility( true ).SetInteractivity( true );
    hps_widget->getCanvas().GetWindowKey().GetPortfolioControl().Push( Application::instance()->getPortfolioKey() );
    return hps_widget;
}
