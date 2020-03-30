#include <MainWindow.h>
#include <actions/ExitAction.h>

ts3d::ExitAction::ExitAction( QObject *owner )
    : QAction( tr( "Exit", "Exit the application" ), owner ) {
    setStatusTip( tr( "Exit the application", "Exit status tip" ) );
    setToolTip( tr( "Exit the application", "File open action tool tip text" ) );
 
    connect( this, &QAction::triggered, qApp, &QCoreApplication::quit);
}

// virtual
ts3d::ExitAction::~ExitAction( void ) {
}
