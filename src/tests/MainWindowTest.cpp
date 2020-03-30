#include <QTest>
#include <ui/tests/MainWindowTest.h>
#include <ui/tests/TestCommon.h>
#include <ui/MainWindow.h>
#include <ui/HPSMdiSubWindow.h>

//Setting up the test case
void ts3d::MainWindowTest::initTestCase(){
}

//Tests
void ts3d::MainWindowTest::testOnValidModelOpened(){
    HPS::Model validModel = HPS::Factory::CreateModel( ts3d::TestCommon::HSF_FILE.toStdString().c_str() );
    ts3d::MainWindow::instance()->onModelOpened( validModel, ts3d::TestCommon::HSF_FILE );
    ts3d::HPSMdiSubWindow * currentWindow = ts3d::MainWindow::instance()->getActiveHPSMdiSubWindow();

    QVERIFY( currentWindow != nullptr );

    currentWindow->getCanvas().Update(); 
    QVERIFY( currentWindow->windowTitle() == "HPS::Model - " + ts3d::TestCommon::HSF_FILE );

}

ts3d::MainWindowTest::~MainWindowTest( void ){
}