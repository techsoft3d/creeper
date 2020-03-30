#include <actions/FileOpen.h>
#include <FileToolBar.h>

ts3d::FileToolBar::FileToolBar( QWidget *parent )
    : QToolBar( parent ) {
    setObjectName( "FileToolBar" );
    addAction( new FileOpen( this ) );
}

// virtual
ts3d::FileToolBar::~FileToolBar( void ) {

}
