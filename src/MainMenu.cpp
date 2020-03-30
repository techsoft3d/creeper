#include <FileOpener.h>
#include <actions/FileOpen.h>
#include <actions/RenderMode.h>
#include <actions/CameraOrientation.h>
#include <actions/ProjectionMode.h>
#include <actions/ExitAction.h>
#include <MainMenu.h>
#include <MainWindow.h>
#include <HPSWidget.h>

namespace {
    static auto const MAX_RECENTLY_USED_FILES = 5u;
}
ts3d::MainMenu::MainMenu( QWidget *parent )
    : QMenuBar( parent ) {

    auto mainMenu = this;
    auto fileMenu = mainMenu->addMenu( tr( "File", "File Menu" ) );

    auto fileOpenAction = new FileOpen( fileMenu );
    fileOpenAction->setShortcut( QKeySequence::Open );
    fileMenu->addAction( fileOpenAction );
    fileMenu->addSeparator();

    _recentlyUsedFilesMenu = fileMenu->addMenu( tr( "Recent", "Recently used files submenu title" ) );

    QSettings settings;
    for(auto idx = 0u; idx < MAX_RECENTLY_USED_FILES; ++idx) {
        auto filename = settings.value( QString( "RecentFile%1" ).arg( idx ) ).toString();
        if(filename.isEmpty()) {
            continue;
        }
        QFileInfo fi( filename );
        if(!fi.exists()) {
            continue;
        }
        auto action = _recentlyUsedFilesMenu->addAction( fi.fileName() );
        action->setShortcut( Qt::CTRL | (Qt::Key_1 + idx) );
        connect( action, &QAction::triggered, [filename] {
            FileOpener::instance()->openFile( filename );
        } );

        RecentlyUsedFile ruf( action, filename );
        _recentlyUseFilesList.append( ruf );
    }
    fileMenu->addSeparator();
    
    fileMenu->addAction( new ExitAction( fileMenu ) );

    connect( FileOpener::instance(), &FileOpener::modelOpened, this, &MainMenu::onModelOpened );
    connect( FileOpener::instance(), &FileOpener::cadModelOpened, this, &MainMenu::onCadModelOpened );

    auto viewMenu = mainMenu->addMenu( tr("View", "View Menu"));
    Q_UNUSED( viewMenu );

    auto cameraMenu = mainMenu->addMenu( tr("Camera", "Camera Menu"));
    auto cameraOrientSubMenu = cameraMenu->addMenu( tr( "Camera Orientation"));
    auto cameraOrientActions = new QActionGroup(this);
    cameraOrientActions->addAction( new CameraOrientation( cameraMenu, tr("Front", "Camera Orientation"),  HPS::Vector(-1, 0, 0), HPS::Vector( 0, 1, 0) ) );
    cameraOrientActions->addAction( new CameraOrientation( cameraMenu, tr("Back", "Camera Orientation"),   HPS::Vector( 1, 0, 0), HPS::Vector( 0, 1, 0) ) );
    cameraOrientActions->addAction( new CameraOrientation( cameraMenu, tr("Left", "Camera Orientation"),   HPS::Vector( 0, 0,-1), HPS::Vector( 0, 1, 0) ) );
    cameraOrientActions->addAction( new CameraOrientation( cameraMenu, tr("Right", "Camera Orientation"),  HPS::Vector( 0, 0, 1), HPS::Vector( 0, 1, 0) ) );
    cameraOrientActions->addAction( new CameraOrientation( cameraMenu, tr("Top", "Camera Orientation"),    HPS::Vector( 0, 1, 0), HPS::Vector( 1, 0, 0) ) );
    cameraOrientActions->addAction( new CameraOrientation( cameraMenu, tr("Bottom", "Camera Orientation"), HPS::Vector( 0,-1, 0), HPS::Vector( 1, 0, 0) ) );
    for (auto action : cameraOrientActions->actions()) {
        action->setCheckable(true);
    }
    cameraOrientSubMenu->addActions(cameraOrientActions->actions());
    cameraMenu->addSeparator();

    auto cameraProjSubMenu =cameraMenu->addMenu( tr( "Projection Mode"));
    auto cameraProjActions = new QActionGroup(this);
    cameraProjActions->addAction( new ProjectionMode( cameraMenu, HPS::Camera::Projection::Perspective ) );
    cameraProjActions->addAction( new ProjectionMode( cameraMenu, HPS::Camera::Projection::Orthographic ) );
    cameraProjActions->addAction( new ProjectionMode( cameraMenu, HPS::Camera::Projection::Stretched ) );
    for (auto action : cameraProjActions->actions()) {
        action->setCheckable(true);
    }
    cameraProjSubMenu->addActions(cameraProjActions->actions());
    cameraMenu->addSeparator();

    connect( cameraProjSubMenu, &QMenu::aboutToShow, [cameraProjActions] {
        if(auto hps_widget = ts3d::MainWindow::instance()->getCurrentHPSWidget()) {
            HPS::Camera::Projection projMode;
            hps_widget->getView().GetSegmentKey().GetCameraControl().ShowProjection( projMode );
            auto projModeStr = ProjectionMode::getProjectionModeName( projMode );
            auto checkedAction = cameraProjActions->checkedAction();
            if((checkedAction == 0) || (projModeStr != checkedAction->text())) {
                for(auto action : cameraProjActions->actions()) {
                    if(action->text() == projModeStr) {
                        action->setChecked( true );
                    }
                }
            }
        }
    });



    auto graphicsMenu = mainMenu->addMenu( tr("Graphics", "Graphics Menu"));
    auto renderingSubMenu = graphicsMenu->addMenu( tr( "Rendering Mode" ));
    auto renderingActions = new QActionGroup(this);
    renderingActions->addAction( new RenderMode( graphicsMenu, HPS::Rendering::Mode::Gouraud ) );
    renderingActions->addAction( new RenderMode( graphicsMenu, HPS::Rendering::Mode::GouraudWithLines ) );
    renderingActions->addAction( new RenderMode( graphicsMenu, HPS::Rendering::Mode::Flat ) );
    renderingActions->addAction( new RenderMode( graphicsMenu, HPS::Rendering::Mode::FlatWithLines ) );
    renderingActions->addAction( new RenderMode( graphicsMenu, HPS::Rendering::Mode::Phong ) );
    renderingActions->addAction( new RenderMode( graphicsMenu, HPS::Rendering::Mode::PhongWithLines ) );
    renderingActions->addAction( new RenderMode( graphicsMenu, HPS::Rendering::Mode::HiddenLine ) );
    renderingActions->addAction( new RenderMode( graphicsMenu, HPS::Rendering::Mode::FastHiddenLine ) );
    renderingActions->addAction( new RenderMode( graphicsMenu, HPS::Rendering::Mode::Wireframe ) );
    for (auto action : renderingActions->actions()) {
        action->setCheckable(true);
    }
    renderingSubMenu->addActions(renderingActions->actions());
    graphicsMenu->addSeparator();

    connect( renderingSubMenu, &QMenu::aboutToShow, [renderingActions] {
        if(auto hps_widget = ts3d::MainWindow::instance()->getCurrentHPSWidget()) {
            for(auto action : renderingActions->actions()) {
                action->setEnabled( true );
            }
            auto renderMode = RenderMode::getRenderModeName( hps_widget->getView().GetRenderingMode() );
            auto checkedAction = renderingActions->checkedAction();
            if((checkedAction == 0) || (renderMode != checkedAction->text())) {
                for(auto action : renderingActions->actions()) {
                    //action->setChecked(false);
                    if(action->text() == renderMode) {
                        action->setChecked( true );
                    }
                }
            }
        } else {
            for(auto action : renderingActions->actions()) {
                action->setEnabled( false );
            }
        }
    });

    auto lightingSubMenu = graphicsMenu->addMenu( tr( "Lighting" ));
    Q_UNUSED( lightingSubMenu );

    auto markupMenu = mainMenu->addMenu( tr("Markup", "Markup Menu"));
    Q_UNUSED( markupMenu );
}

ts3d::MainMenu::~MainMenu( void ) {
}

void ts3d::MainMenu::onModelOpened( HPS::Model model, QString filename ) {
    Q_UNUSED( model );
    addRecentlyUsedFile( filename );
}

void ts3d::MainMenu::onCadModelOpened( HPS::CADModel, QString filename ) {
    addRecentlyUsedFile( filename );
}

void ts3d::MainMenu::addRecentlyUsedFile( QString const filename ) {
    if(filename.isEmpty()) {
        return;
    }

    // remove oldest or previous matching entry
    if(!_recentlyUseFilesList.empty()) {
        auto index_to_remove = -1;
        for(auto idx = 0; idx < _recentlyUseFilesList.size(); ++idx) {
            if(_recentlyUseFilesList[idx].filename == filename) {
                index_to_remove = idx;
                break;
            }
        }

        if(index_to_remove == 0) {
            return;
        }

        if(index_to_remove == -1 && _recentlyUseFilesList.size() >= static_cast<int>(MAX_RECENTLY_USED_FILES)) {
            index_to_remove = _recentlyUseFilesList.size() - 1;
        }

        if(index_to_remove >= 0 && index_to_remove < _recentlyUseFilesList.size()) {
            auto to_remove = _recentlyUseFilesList[index_to_remove];
            _recentlyUsedFilesMenu->removeAction( to_remove.action );
            _recentlyUseFilesList.removeAt( index_to_remove );
            to_remove.action->deleteLater();
        }
    }

    // add new entry
    auto action = new QAction( QFileInfo( filename ).fileName(), _recentlyUsedFilesMenu );
    connect( action, &QAction::triggered, [filename] {
        FileOpener::instance()->openFile( filename );
    } );

    if(_recentlyUsedFilesMenu->isEmpty()) {
        _recentlyUsedFilesMenu->addAction( action );
    } else {
        _recentlyUsedFilesMenu->insertAction( _recentlyUsedFilesMenu->actions().first(), action );
    }

    RecentlyUsedFile ruf( action, filename );
    _recentlyUseFilesList.insert( 0, ruf );

    // write new settings
    QSettings settings;
    for(auto idx = 0; idx < _recentlyUseFilesList.size(); ++idx) {
        settings.setValue( QString( "RecentFile%1" ).arg( idx ), _recentlyUseFilesList[idx].filename );
    }
}

