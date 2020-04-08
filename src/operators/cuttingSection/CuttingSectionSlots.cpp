#include <HPSWidget.h>
#include <operators/cuttingSection/CuttingSectionSlots.h>
#include <QDebug>

ts3d::CuttingSectionSlots::CuttingSectionSlots( void ) {
	_cuttingSectionCommands.reset( new CuttingSectionCommands );
    _hpsWidget = nullptr;

    _invertX = false;
    _invertY = false;
    _invertZ = false;
    _sectioning = false;
}

ts3d::CuttingSectionSlots::~CuttingSectionSlots( void ) {

}

void ts3d::CuttingSectionSlots::getCurrentHPSWidget() {
    _hpsWidget = ts3d::MainWindow::instance()->getCurrentHPSWidget();
    if(nullptr == _hpsWidget) {
        qDebug() << "No current HPS widget";
        return;
    }

    if ( !_cuttingSectionCommands->setCanvas(_hpsWidget->getCanvas()) ) {
        _invertX = false;
        _invertY = false;
        _invertZ = false;
        _sectioning = false;
    }
}

void ts3d::CuttingSectionSlots::addErasePlaneX( bool on ) {
    if ( nullptr == _hpsWidget)
        return;

    HPS::Vector planeVector = HPS::Vector().XAxis();
    if ( _invertX )
        planeVector.operator*=(-1);

    if (on)
        _cuttingSectionCommands->addCuttingPlane(planeVector);
    else
        _cuttingSectionCommands->eraseCuttingPlane(planeVector);

    _hpsWidget->getCanvas().Update();
}

void ts3d::CuttingSectionSlots::addErasePlaneY( bool on ) {
    if ( nullptr == _hpsWidget)
        return;

    HPS::Vector planeVector = HPS::Vector().YAxis();
    if ( _invertY )
        planeVector.operator*=(-1);

    if (on)
        _cuttingSectionCommands->addCuttingPlane(planeVector);
    else
        _cuttingSectionCommands->eraseCuttingPlane(planeVector);

    _hpsWidget->getCanvas().Update();
}

void ts3d::CuttingSectionSlots::addErasePlaneZ( bool on ) {
    if ( nullptr == _hpsWidget)
        return;

    HPS::Vector planeVector = HPS::Vector().ZAxis();
    if ( _invertZ )
        planeVector.operator*=(-1);

    if (on)
        _cuttingSectionCommands->addCuttingPlane(planeVector);
    else
        _cuttingSectionCommands->eraseCuttingPlane(planeVector);

    _hpsWidget->getCanvas().Update();
}

void ts3d::CuttingSectionSlots::onInvertX( bool checked ) {
    if ( nullptr == _hpsWidget)
        return;

    _invertX = checked;

    HPS::Vector planeVector = HPS::Vector().XAxis();
    if ( _invertX )
        planeVector.operator*=(-1);

    _cuttingSectionCommands->invertCuttingPlane(planeVector);
}

void ts3d::CuttingSectionSlots::onInvertY( bool checked ) {
    if ( nullptr == _hpsWidget)
        return;

    _invertY = checked;

    HPS::Vector planeVector = HPS::Vector().YAxis();
    if ( _invertY )
        planeVector.operator*=(-1);

    _cuttingSectionCommands->invertCuttingPlane(planeVector);
}

void ts3d::CuttingSectionSlots::onInvertZ( bool checked ) {
    if ( nullptr == _hpsWidget)
        return;

    _invertZ = checked;

    HPS::Vector planeVector = HPS::Vector().ZAxis();
    if ( _invertZ )
        planeVector.operator*=(-1);

    _cuttingSectionCommands->invertCuttingPlane(planeVector);
}

void ts3d::CuttingSectionSlots::setUnsetSectioning(bool set) {
    if ( nullptr == _hpsWidget)
        return;

    _sectioning = set;

    _cuttingSectionCommands->setUnsetSectioning(set);
}

void ts3d::CuttingSectionSlots::showHidePlanes( bool on ) {
    if ( nullptr == _hpsWidget)
        return;

    _cuttingSectionCommands->showHidePlane(on);

}

void ts3d::CuttingSectionSlots::cancelCuttingSection( void ) {
    if ( nullptr == _hpsWidget)
        return;

    _cuttingSectionCommands->cancelCuttingSection();

    _invertX = false;
    _invertY = false;
    _invertZ = false;
    _sectioning = false;
}

void ts3d::CuttingSectionSlots::getCurrentStatus(bool &planeX, bool &invertX, bool &planeY, bool &invertY, bool &planeZ, bool &invertZ,
                                                 bool &setSectioning, bool &showPlanes) {
    HPS::PlaneArray cuttingPlanes = _cuttingSectionCommands->getCuttingPlanes(setSectioning, showPlanes);

    for ( unsigned int i = 0; i < cuttingPlanes.size(); i++) {
        HPS::Plane plane = cuttingPlanes[i];
        if ( plane.a == 1 && plane.b == 0 && plane.c == 0 ) {
            planeX = true;
        } else if ( plane.a == -1 && plane.b ==  0 && plane.c ==  0 ) {
            planeX = true;
            invertX = true;
        } else if ( plane.a ==  0 && plane.b ==  1 && plane.c ==  0 ) {
            planeY = true;
        } else if ( plane.a ==  0 && plane.b == -1 && plane.c ==  0 ) {
            planeY = true;
            invertY = true;
        } else if ( plane.a ==  0 && plane.b ==  0 && plane.c ==  1 ) {
            planeZ = true;
        } else if ( plane.a ==  0 && plane.b ==  0 && plane.c == -1 ) {
            planeZ = true;
            invertZ = true;
        }
    }
}
