#include <HPSWidget.h>
#include <HPSMdiSubWindow.h>
#include <MainMenu.h>
#include <FileOpener.h>
#include <FileToolBar.h>
#include <TreeDockWidget.h>
#include <CuttingSectionDockWidget.h>
#include <MainWindow.h>

// static
ts3d::MainWindow *ts3d::MainWindow::instance( void ) {
    static QPointer<MainWindow> _instance = nullptr;
    if(nullptr == _instance) {
        _instance = new MainWindow();
    }
    return _instance;
}

QMessageBox::StandardButton ts3d::MainWindow::showInformationMessageBox( QString const &message, QMessageBox::StandardButtons buttons ) {
    return QMessageBox::information( this, tr( "%1 - Information", "Information box title" ).arg( qApp->applicationDisplayName() ), message, buttons );
}

void ts3d::MainWindow::onModelOpened( HPS::Model const model, QString const &filename ) {
    if(_mdiArea) {
       QMdiSubWindow * window = _mdiArea->addSubWindow( new HPSMdiSubWindow( _mdiArea, model, getIntialHpsSubWindowSize() ) );
       window->setWindowTitle(QString("HPS::Model - " + filename ));
       window->show();
    }
}


void ts3d::MainWindow::onCadModelOpened( HPS::CADModel const model, QString const &filename ) {
    if(_mdiArea) {
       QMdiSubWindow * window = _mdiArea->addSubWindow( new HPSMdiSubWindow( _mdiArea, model, getIntialHpsSubWindowSize() ) );
       window->setWindowTitle(QString("HPS::CADModel - " + filename ));
       window->show();
    }
}

ts3d::HPSWidget *ts3d::MainWindow::getCurrentHPSWidget( void ) const {
    auto subWindow = _mdiArea ? _mdiArea->currentSubWindow() : nullptr;
    return dynamic_cast<HPSWidget*>(subWindow ? subWindow->widget() : nullptr);
}

ts3d::HPSMdiSubWindow *ts3d::MainWindow::getActiveHPSMdiSubWindow( void ) const {
    return dynamic_cast<HPSMdiSubWindow*>(_mdiArea ? _mdiArea->currentSubWindow() : nullptr);
}


void ts3d::MainWindow::dragEnterEvent( QDragEnterEvent * event ) {
    event->acceptProposedAction();
}

void ts3d::MainWindow::dropEvent( QDropEvent * event ) {
    for(auto url : event->mimeData()->urls()) {
        FileOpener::instance()->openFile( url.toLocalFile() );
    }
}

void ts3d::MainWindow::closeEvent( QCloseEvent *event ) {
    QSettings settings;
    settings.setValue( "MainWindow/geometry", saveGeometry() );
    settings.setValue( "MainWindow/windowState", saveState() );
    QMainWindow::closeEvent( event );
}

ts3d::MainWindow::MainWindow( void )
    : QMainWindow(),
    _mdiArea( new QMdiArea( this ) ) {
    setAcceptDrops( true );
    setMenuBar( new MainMenu( this ) );
    addToolBar( new FileToolBar( this ) );
    auto treeDockWidget = new TreeDockWidget( this );
    addDockWidget( Qt::DockWidgetArea::LeftDockWidgetArea, treeDockWidget );

    auto cuttingSectionDockWidget = new CuttingSectionDockWidget( this);
    addDockWidget( Qt::DockWidgetArea::RightDockWidgetArea, cuttingSectionDockWidget );

    setCentralWidget( _mdiArea );

    connect( FileOpener::instance(), &FileOpener::modelOpened, this, &MainWindow::onModelOpened );
    connect( FileOpener::instance(), &FileOpener::cadModelOpened, this, &MainWindow::onCadModelOpened );
    connect( FileOpener::instance(), &FileOpener::failure, [&]( QString message ) {
        showInformationMessageBox( message );
    } );
    connect( _mdiArea, &QMdiArea::subWindowActivated, treeDockWidget, &TreeDockWidget::onActiveMdiSubWindowChanged );
    connect( _mdiArea, &QMdiArea::subWindowActivated, cuttingSectionDockWidget, &CuttingSectionDockWidget::onActiveMdiSubWindowChanged );
    connect( FileOpener::instance(), &FileOpener::begin, [&](QString filename) {
        _progressDialog = new QProgressDialog( this );
        _progressDialog->setLabelText( QString( "Loading file %1..." ).arg( QFileInfo( filename ).fileName() ) );
        _progressDialog->setAutoClose( false );
        _progressDialog->setModal( true );
        connect( _progressDialog, &QProgressDialog::canceled, FileOpener::instance(), &FileOpener::cancel );
        _progressDialog->show();
    } );
    connect( FileOpener::instance(), &FileOpener::complete, [&] {
        if(_progressDialog) {
            _progressDialog->hide();
            _progressDialog->deleteLater();
        }
    } );
    connect( FileOpener::instance(), &FileOpener::progressChanged, [&](double progress) {
        if(_progressDialog) {
            _progressDialog->setValue( progress * 100 );
        }
    } );
    QSettings settings;
    restoreGeometry( settings.value( "MainWindow/geometry" ).toByteArray() );
    restoreState( settings.value( "MainWindow/windowState" ).toByteArray() );
}

// virtual
ts3d::MainWindow::~MainWindow( void ) {
}

QSize ts3d::MainWindow::getIntialHpsSubWindowSize( void ) const {
    QSize initialSize;
    if(_mdiArea) {
        if(auto activeSubWindow = _mdiArea->activeSubWindow()) {
            initialSize = activeSubWindow->size();
        } else {
            initialSize = _mdiArea->size() * 0.75;
        }
    }
    return initialSize;
}

