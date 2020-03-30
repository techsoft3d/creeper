#include <tree/TreeWidget.h>
#include <MainWindow.h>
#include <HPSMdiSubWindow.h>
#include <HPSWidget.h>
#include <TreeDockWidget.h>

ts3d::TreeDockWidget::TreeDockWidget( QWidget *parent ) 
: QDockWidget( tr("Model Browser", "Tree dock widget title"), parent ) {
    setObjectName( "TreeDockWidget" );
}

ts3d::TreeDockWidget::~TreeDockWidget( void ) {
}

void ts3d::TreeDockWidget::onActiveMdiSubWindowChanged( QMdiSubWindow *subWindow ) {
    if(_lastActiveSubWindow == subWindow) {
        return;
    }

    if(_treeWidgets.contains( subWindow )) {
        setWidget( _treeWidgets[subWindow] );
        return;
    }

    if(auto hpsSubWindow = dynamic_cast<HPSMdiSubWindow*>(subWindow)) {
        auto treeWidget = new TreeWidget( this, dynamic_cast<HPSWidget*>(hpsSubWindow->widget()) );

        HPS::CADModel activeCADModel;
        treeWidget->setCADModel( hpsSubWindow->getCADModel() );
        connect( hpsSubWindow, &HPSMdiSubWindow::closed, [&] {
            _treeWidgets.remove( subWindow );
            setWidget( nullptr );
        });
        setWidget( treeWidget );
        _treeWidgets[subWindow] = treeWidget;
    } else {
        setWidget( nullptr );
    }
}
