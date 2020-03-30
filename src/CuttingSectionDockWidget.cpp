#include <MainWindow.h>
#include <HPSMdiSubWindow.h>
#include <HPSWidget.h>
#include <CuttingSectionDockWidget.h>
#include <QDebug>

ts3d::CuttingSectionDockWidget::CuttingSectionDockWidget( QWidget *parent )
: QDockWidget( tr("Cutting Section", "Cutting Section dock widget title"), parent ) {
    setObjectName( "CuttingSectionDockWidget" );

    _cuttingSectionSlots = new CuttingSectionSlots();

    // Layout
    QWidget* multiWidget = new QWidget();
    QVBoxLayout *vLayout = new QVBoxLayout();

    QGridLayout *gLayout = new QGridLayout();
    gLayout->addWidget( _planeButtonX = new QPushButton( _addPlaneLabel.arg( "X" ) ), 0, 0, Qt::AlignRight );
    _planeButtonX->setCheckable( true );
    _planeButtonX->setChecked( false );
    connect( _planeButtonX, SIGNAL( toggled( bool ) ), this, SLOT( onPlaneX( bool ) ) );

    gLayout->addWidget( _planeButtonY = new QPushButton( _addPlaneLabel.arg( "Y" ) ), 1, 0, Qt::AlignRight );
    _planeButtonY->setCheckable( true );
    _planeButtonY->setChecked( false );
    connect( _planeButtonY, SIGNAL( toggled( bool ) ), this, SLOT( onPlaneY( bool ) ) );

    gLayout->addWidget(_planeButtonZ = new QPushButton( _addPlaneLabel.arg( "Z" ) ), 2, 0, Qt::AlignRight );
    _planeButtonZ->setCheckable( true );
    _planeButtonZ->setChecked( false );
    connect( _planeButtonZ, SIGNAL( toggled( bool ) ), this, SLOT( onPlaneZ( bool ) ) );

    gLayout->addWidget(_invertButtonX = new QCheckBox( _invertLabel), 0, 1, Qt::AlignLeft);
    connect( _invertButtonX, SIGNAL( toggled( bool ) ), _cuttingSectionSlots, SLOT( onInvertX( bool ) ) );

    gLayout->addWidget(_invertButtonY = new QCheckBox(_invertLabel), 1, 1, Qt::AlignLeft);
    connect( _invertButtonY, SIGNAL( toggled( bool ) ), _cuttingSectionSlots, SLOT( onInvertY( bool ) ) );

    gLayout->addWidget(_invertButtonZ = new QCheckBox(_invertLabel), 2, 1, Qt::AlignLeft);
    connect( _invertButtonZ, SIGNAL( toggled( bool ) ), _cuttingSectionSlots, SLOT( onInvertZ( bool ) ) );

    vLayout->addLayout( gLayout );

    QHBoxLayout *hLayoutSection = new QHBoxLayout();
    hLayoutSection->addStretch();
    hLayoutSection->addWidget( _setUnsetSectioningButton = new QPushButton( _setSectioningLabel ) );
    _setUnsetSectioningButton->setCheckable( true );
    _setUnsetSectioningButton->setChecked( false );
    connect( _setUnsetSectioningButton, SIGNAL( toggled( bool ) ), this, SLOT( onSetUnsetSectioning( bool ) ) );
    hLayoutSection->addStretch();
    vLayout->addLayout( hLayoutSection );

    QHBoxLayout *hLayoutHide = new QHBoxLayout();
    hLayoutHide->addStretch();
    hLayoutHide->addWidget( _showHidePlaneButton = new QPushButton( _hidePlanesLabel ) );
    _showHidePlaneButton->setCheckable( true );
    _showHidePlaneButton->setChecked( true );
    connect( _showHidePlaneButton, SIGNAL( toggled( bool ) ), this, SLOT( onShowHidePlanes( bool ) ) );
    hLayoutHide->addStretch();
    vLayout->addLayout( hLayoutHide );

    vLayout->addStretch();

    QHBoxLayout *hLayout2 = new QHBoxLayout();
    hLayout2->addStretch();
    hLayout2->addWidget( _cancelButton = new QPushButton( _cancelLabel ) );
    connect( _cancelButton, SIGNAL(clicked() ), this, SLOT( onCancel()) );
    hLayout2->addStretch();
    vLayout->addLayout( hLayout2 );

    vLayout->addStretch();

    multiWidget->setLayout( vLayout );
    setWidget( multiWidget );
}

ts3d::CuttingSectionDockWidget::~CuttingSectionDockWidget( void ) {
}

void ts3d::CuttingSectionDockWidget::onActiveMdiSubWindowChanged( void ) {
    _cuttingSectionSlots->getCurrentHPSWidget();
    updateWidgets();
}

void ts3d::CuttingSectionDockWidget::updateWidgets( void ) {
    bool planeX = false;
    bool planeY = false;
    bool planeZ = false;
    bool invertX = false;
    bool invertY = false;
    bool invertZ = false;
    bool setSectioning = false;
    bool showPlanes = true;
    _cuttingSectionSlots->getCurrentStatus( planeX, invertX, planeY, invertY, planeZ, invertZ, setSectioning ,showPlanes );

    _planeButtonX->blockSignals( true );
    _planeButtonX->setChecked( planeX );
    _planeButtonX->setText( planeX ? _erasePlaneLabel.arg( "X" ) : _addPlaneLabel.arg( "X" ) );
    _planeButtonX->blockSignals( false );

    _planeButtonY->blockSignals( true );
    _planeButtonY->setChecked( planeY );
    _planeButtonY->setText( planeY ? _erasePlaneLabel.arg( "Y" ) : _addPlaneLabel.arg( "Y" ) );
    _planeButtonY->blockSignals( false );

    _planeButtonZ->blockSignals( true );
    _planeButtonZ->setChecked( planeZ );
    _planeButtonZ->setText( planeZ ? _erasePlaneLabel.arg( "Z" ) : _addPlaneLabel.arg( "Z" ) );
    _planeButtonZ->blockSignals( false );

    _invertButtonX->blockSignals( true );
    _invertButtonX->setChecked( invertX );
    _invertButtonX->blockSignals( false );

    _invertButtonY->blockSignals( true );
    _invertButtonY->setChecked( invertY );
    _invertButtonY->blockSignals( false );

    _invertButtonZ->blockSignals( true );
    _invertButtonZ->setChecked( invertZ );
    _invertButtonZ->blockSignals( false );

    _setUnsetSectioningButton->blockSignals( true );
    _setUnsetSectioningButton->setChecked( setSectioning );
    _setUnsetSectioningButton->setText( setSectioning ? _unsetSectioningLabel : _setSectioningLabel );
    _setUnsetSectioningButton->blockSignals( false );

    _showHidePlaneButton->setChecked( false );
    _showHidePlaneButton->setChecked( true );

}

void ts3d::CuttingSectionDockWidget::onPlaneX( bool on ) {
    _planeButtonX->setText( on ? _erasePlaneLabel.arg( "X" ) : _addPlaneLabel.arg( "X" ) );
    _cuttingSectionSlots->addErasePlaneX( on );
}

void ts3d::CuttingSectionDockWidget::onPlaneY( bool on ) {
    _planeButtonY->setText( on ? _erasePlaneLabel.arg( "Y" ) : _addPlaneLabel.arg( "Y" ) );
    _cuttingSectionSlots->addErasePlaneY( on );
}

void ts3d::CuttingSectionDockWidget::onPlaneZ( bool on ) {
    _planeButtonZ->setText( on ? _erasePlaneLabel.arg( "Z" ) : _addPlaneLabel.arg( "Z" ) );
    _cuttingSectionSlots->addErasePlaneZ( on );
}

void ts3d::CuttingSectionDockWidget::onSetUnsetSectioning( bool set ) {
    _setUnsetSectioningButton->setText( set ? _unsetSectioningLabel : _setSectioningLabel );
    _cuttingSectionSlots->setUnsetSectioning( set );
}

void ts3d::CuttingSectionDockWidget::onShowHidePlanes( bool show ) {
    _showHidePlaneButton->setText( show ? _hidePlanesLabel : _showPlaneLabel );
    _cuttingSectionSlots->showHidePlanes( show );
}

void ts3d::CuttingSectionDockWidget::onCancel() {
    _cuttingSectionSlots->cancelCuttingSection();
    updateWidgets();
}
