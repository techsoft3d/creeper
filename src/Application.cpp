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

namespace {
    QString getExchangeArch( void ) {
        #if defined(_MSC_VER)
            return "win64";
        #elif defined(__APPLE__)
            return "osx64";
        #elif defined(__linux__)
            return "linux64";
        #endif
        return "unknown";
    }
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
    QDir exchangePath( CommandLineOptions::instance().getExchangePath() + "/bin/" + getExchangeArch() );
    while( !exchangePath.exists() ) {
        QMessageBox::information( nullptr, QGuiApplication::applicationDisplayName(),
                                 tr( "Please choose the root directory of your Exchange installation. It folder must contain %1.",
                                    "Application startup" ).arg( "bin/" + getExchangeArch() ) );
        auto const d = QFileDialog::getExistingDirectory( nullptr, tr("Please choose the root directory of your Exchange installation.", "Application startup" ), exchangePath.path() );
        if( d.isEmpty() ) {
            QTimer::singleShot( 0, [] { qApp->quit(); } );
            return;
        }
        exchangePath = QDir( d + "/bin/" + getExchangeArch() );
    }
        
    _world.SetExchangeLibraryDirectory( qPrintable( exchangePath.path() ) );
#endif

    MainWindow::instance()->show();
}

// virtual
ts3d::Application::~Application( void ) {
}
