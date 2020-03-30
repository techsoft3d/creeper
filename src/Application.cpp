#include <hoops_license.h>
#include <A3DSDKLoader.h>
#include <MainWindow.h>
#include "CommandLineOptions.h"
#include <Application.h>

// static
ts3d::Application *ts3d::Application::_instance = nullptr;

// static
ts3d::Application *ts3d::Application::instance( void ) {
    return _instance;
}

// static
bool ts3d::Application::initializeInstance( int &argc, char *argv[] ) {
    if(_instance) {
        return false;
    }

    _instance = new Application( argc, argv );

    return true;
}

void ts3d::Application::destroyInstance( void ) {
    delete _instance;
    _instance = nullptr;
}

HPS::SegmentKey ts3d::Application::getHighlightStyleSegment( void ) const {
    return _highlightSegmentKey;
}

HPS::PortfolioKey ts3d::Application::getPortfolioKey( void ) const {
    return _portfolioKey;
}

HPS::UTF8 ts3d::Application::getHighlightStyleName( void ) const {
    return HPS::UTF8( "Its_a_creeper_highlight_stlye" );
}

ts3d::Application::Application( int &argc, char *argv[] )
    : QApplication( argc, argv ),
    _world( HOOPS_LICENSE ) {
 
    setApplicationName( tr( "HOOPS Viewer", "Application name" ) );
    setApplicationVersion( tr( "0.0.1", "Application version" ) );
    setOrganizationDomain( "techsoft3d.com" );
    setOrganizationName( "Tech Soft 3D" );

    QTranslator translator;
    if (translator.load("viewer_" + QLocale::system().name())) {
        installTranslator(&translator);
    }

    auto const parseResult = CommandLineOptions::instance().parse();
    switch( parseResult ) {
    case CommandLineOptions::Status::Ok:
        break;
    case CommandLineOptions::Status::Error:
          QMessageBox::warning(nullptr, QGuiApplication::applicationDisplayName(),
                               "<html><head/><body><h2>" + CommandLineOptions::instance().getErrorText() + "</h2><pre>"
                               + CommandLineOptions::instance().getHelpText() + "</pre></body></html>");
          QTimer::singleShot( 0, [] { qApp->quit(); } );
          return;
      case CommandLineOptions::Status::Version:
          QMessageBox::information(nullptr, QGuiApplication::applicationDisplayName(),
                                   QGuiApplication::applicationDisplayName() + ' '
                                   + QCoreApplication::applicationVersion());
          QTimer::singleShot( 0, [] { qApp->quit(); } );
          return;
      case CommandLineOptions::Status::Help:
          QMessageBox::warning(nullptr, QGuiApplication::applicationDisplayName(),
                               "<html><head/><body><pre>"
                               + CommandLineOptions::instance().getHelpText() + "</pre></body></html>");
          QTimer::singleShot( 0, [] { qApp->quit(); } );
          return;
    }

    _highlightSegmentKey = HPS::Database::CreateRootSegment();
    _highlightSegmentKey.GetMaterialMappingControl().SetFaceColor( HPS::RGBAColor( 1., 0., 0. ) );
    
    _portfolioKey = HPS::Database::CreatePortfolio();
    _portfolioKey.DefineNamedStyle( getHighlightStyleName(), _highlightSegmentKey );

#ifdef USING_EXCHANGE
    QDir exchangePath;
    if( CommandLineOptions::instance().isExchangePathSet() ) {
        exchangePath.cd( CommandLineOptions::instance().getExchangePath() );
        exchangePath.cd( "bin" );
#if defined(_MSC_VER)
        exchangePath.cd( "win64" );
#elif __APPLE__
        exchangePath.cd( "osx64" );
#elif __linux__
        exchangePath.cd( "linux64" );
#endif
        if( !exchangePath.exists() ) {
            QMessageBox::warning( nullptr, QGuiApplication::applicationDisplayName(),
                                  "The Exchange path does not exist: " + exchangePath.path() );
        }
    }

#if defined(_MSC_VER)
    if(!A3DSDKLoadLibrary(exchangePath.path().toStdWString().c_str())) {
#else
    if(!A3DSDKLoadLibrary(qPrintable( exchangePath.path() ))) {
#endif
        QMessageBox::critical( nullptr, QGuiApplication::applicationDisplayName(),
                               tr("Application", "Unable to load Exchange." ) );

        QTimer::singleShot( 0, [] { qApp->quit(); } );
        return;
    }

    A3DInt32 iMajorVersion, iMinorVersion;
    A3DDllGetVersion( &iMajorVersion, &iMinorVersion );

    if(iMajorVersion != A3D_DLL_MAJORVERSION || iMinorVersion != A3D_DLL_MINORVERSION) {
        QMessageBox::critical( nullptr, QGuiApplication::applicationDisplayName(),
                               tr("HOOPS Exchange: Library version mismatch."));
        QTimer::singleShot( 0, [] { qApp->quit(); } );
        return;
    }

    if(A3D_SUCCESS != A3DLicPutUnifiedLicense( HOOPS_LICENSE )) {
        QMessageBox::critical( nullptr, QGuiApplication::applicationDisplayName(),
                               tr("License error. Please contact labs@techsoft3d.com."));
        QTimer::singleShot( 0, [] { qApp->quit(); } );
        return;
    }

    qInfo() << tr( "HOOPS Exchange successfully initialized." );
#endif

    MainWindow::instance()->show();
}

// virtual
ts3d::Application::~Application( void ) {
#ifdef USING_EXCHANGE
    if( A3DDllTerminate ) {
        A3DDllTerminate();
        A3DSDKUnloadLibrary();
    }
#endif
}
