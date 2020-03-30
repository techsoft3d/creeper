#include <QTest>
#include <ui/tests/FileOpenerTest.h>
#include <ui/FileOpener.h> 
#include <ui/Application.h>
#include <ui/MainWindow.h>
#include <ui/tests/TestCommon.h>



//Setting up the test case
void ts3d::FileOpenerTest::initTestCase(){
	_mainWidget = ts3d::MainWindow::instance()->centralWidget();
	connect( FileOpener::instance(), &FileOpener::modelOpened, this, &ts3d::FileOpenerTest::onModelOpened );
    connect( FileOpener::instance(), &FileOpener::cadModelOpened, this, &ts3d::FileOpenerTest::onCadModelOpened );
    connect( FileOpener::instance(), &FileOpener::failure, this, &ts3d::FileOpenerTest::onFailure );
	connect( FileOpener::instance(), &FileOpener::begin, this, &ts3d::FileOpenerTest::begin );
	connect( FileOpener::instance(), &FileOpener::progressChanged, this, &ts3d::FileOpenerTest::progressChanged );
	connect( FileOpener::instance(), &FileOpener::complete, this, &ts3d::FileOpenerTest::complete );
	resetTestData();
}

// Tests
void ts3d::FileOpenerTest::testOpenFileBadFileLocation(){
	//This test is run once for each "newRow" in the 
	//associated data function below
	resetTestData();

	QFETCH(QString, path);

	//This function will dismiss the modal pop up
	//that happens in the GUI, so use this when 
	//makeing tests that will trigger a messagebox
	//in the UI.  You call it right before you call 
	//the function that causes the modal to pop up
	dismissMessageBox();
	FileOpener::instance()->openFile( path );
	QVERIFY( _errorMessage == tr( "The selected file doesn't exist." ));
	QVERIFY( _modelLoaded == false );
	QVERIFY( _cadModelLoaded == false );
	QVERIFY( _importComplete == true );
	QVERIFY( _progress <= 0.0 );
	QVERIFY( _loadedFileName == path );
}

void ts3d::FileOpenerTest::testOpenFileUnknownFileType(){
	resetTestData();
	dismissMessageBox(500); //Wait to clear the error message box and not the progress box
	FileOpener::instance()->openFile( ts3d::TestCommon::UNKNOWN_TYPE_FILE );
	QVERIFY( _errorMessage == tr( "Unsupported file format." ));
	QVERIFY( _modelLoaded == false );
	QVERIFY( _cadModelLoaded == false );
	QVERIFY( _loadedFileName == ts3d::TestCommon::UNKNOWN_TYPE_FILE );
	QVERIFY( _importComplete == true );
	QVERIFY( _progress <= 0.0 );
}

void ts3d::FileOpenerTest::testCancelFunction(){
	resetTestData();
	QFETCH( QString, file );

	QTimer::singleShot(175, [=]()
    {
		FileOpener::instance()->cancel();
    });

	FileOpener::instance()->openFile( file );
	QVERIFY( _errorMessage.isEmpty() );
	QVERIFY( _modelLoaded == false );
	QVERIFY( _cadModelLoaded == false );
	QVERIFY( _loadedFileName == file );
	QVERIFY( _importComplete == true );
	QVERIFY( _progress < 1.0 );

	dynamic_cast<QMdiArea*>(_mainWidget)->closeAllSubWindows();
}


void ts3d::FileOpenerTest::testOpenValidModel(){
	resetTestData();
	QFETCH( QString, file );
	FileOpener::instance()->openFile( file );
	QVERIFY( _errorMessage.isEmpty() );
	QVERIFY( _modelLoaded == true );
	QVERIFY( _cadModelLoaded == false );
	QVERIFY( _loadedFileName == file );
	QVERIFY( _importComplete == true );
	QVERIFY( _progress >= 1.0 );

	dynamic_cast<QMdiArea*>(_mainWidget)->closeAllSubWindows();
}

void ts3d::FileOpenerTest::testOpenValidCADModel(){
	resetTestData();
	QFETCH( QString, file );

	FileOpener::instance()->openFile( file );
	QVERIFY( _errorMessage.isEmpty() );
	QVERIFY( _modelLoaded == false );
	QVERIFY( _cadModelLoaded == true );
	QVERIFY( _loadedFileName == file );
	QVERIFY( _importComplete == true );
	QVERIFY( _progress >= 1.0 );

	dynamic_cast<QMdiArea*>(_mainWidget)->closeAllSubWindows();
}

// Data functions
void ts3d::FileOpenerTest::testOpenValidCADModel_data(){
	QTest::addColumn<QString>("file");

	QTest::newRow( "PRC File" ) << ts3d::TestCommon::PRC_FILE;
}

void ts3d::FileOpenerTest::testOpenValidModel_data(){
	QTest::addColumn<QString>("file");

	QTest::newRow( "HSF File") << ts3d::TestCommon::HSF_FILE;
	QTest::newRow( "STL File" ) << ts3d::TestCommon::STL_FILE;
	QTest::newRow( "OBJ File" ) << ts3d::TestCommon::OBJ_FILE;
	QTest::newRow( "Point File" ) << ts3d::TestCommon::POINT_CLOUD_FILE; 
}

void ts3d::FileOpenerTest::testOpenFileBadFileLocation_data(){
	QTest::addColumn<QString>("path");

	QTest::newRow( "Bad Unix Path" ) << "/this/path/is/bad";
	QTest::newRow( "Bad Windows Path" ) << "C:/this/path/is/bad";
	QTest::newRow( "Empty Path" ) << "";
	QTest::newRow( "Valid Path - No file" ) << "/tmp";
	QTest::newRow( "Just file name - No Path" ) << "FileDoesNotExist.prc";
	QTest::newRow( "Special characters - File !exist" ) << "$#222@@@!!~~~~.stl";
}

void ts3d::FileOpenerTest::testCancelFunction_data(){
	QTest::addColumn<QString>("file");

	QTest::newRow( "Cancel HPS::Model Load" ) << ts3d::TestCommon::STL_FILE;
	//QTest::newRow( "Cancel HPS::CADModel Load" ) << "pmi_Sample.prc"; TODO: Rob to figure out why this fails
}

// Public slots that will be wired up to the FileOpener for testing
void ts3d::FileOpenerTest::onModelOpened( HPS::Model const model, QString fileName ){
	if( !model.Empty() ){
		_modelLoaded = true;
		_loadedFileName = fileName;
	}
}

void ts3d::FileOpenerTest::onCadModelOpened( HPS::CADModel const cadModel, QString fileName ){
	if( !cadModel.Empty() && cadModel.GetSubcomponents().size() > 0 ){
		_cadModelLoaded = true;
		_loadedFileName = fileName;
	}
}

void ts3d::FileOpenerTest::onFailure( QString failureMessage ){
	_errorMessage = failureMessage;
}

void ts3d::FileOpenerTest::begin( QString fileName ){
	_loadedFileName = fileName;
}

void ts3d::FileOpenerTest::progressChanged( float progress ){
	_progress = progress;
}

void ts3d::FileOpenerTest::complete(){
	_importComplete = true;
}
// Misc helper functions

// This function is something I got from stackoverflow to help me get
// around the message box stopping the tests.  There may be a better
// way to do this and if I find it, I'll update this code - Rob
void ts3d::FileOpenerTest::dismissMessageBox( int delay ){
	QTimer::singleShot(delay, [=]()
    {
        auto key = Qt::Key_Enter;

        QWidget* widget = QApplication::activeModalWidget();
        if (widget)
        {
            QKeyEvent* event = new QKeyEvent(QEvent::KeyPress, key, Qt::NoModifier); 
            QCoreApplication::postEvent(widget, event);
        }
		else
            QFAIL("No message box displayed to user");
    });
}

void ts3d::FileOpenerTest::resetTestData(){
    _modelLoaded = false;
    _cadModelLoaded = false;
    _errorMessage = "";
    _loadedFileName = "";
	_importComplete = false;
	_progress = 0.f;
}

ts3d::FileOpenerTest::~FileOpenerTest( void ){
	_mainWidget = nullptr;
}

