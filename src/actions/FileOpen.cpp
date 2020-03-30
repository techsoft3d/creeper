#include <MainWindow.h>
#include <FileOpener.h>
#include <actions/FileOpen.h>

namespace {
    auto const kFileOpenLastPathSettingsKey = "FileOpen/LastPath";
}

ts3d::FileOpen::FileOpen( QObject *owner )
    : QAction( QIcon(":openIcon"), tr( "Open...", "File open action title" ), owner) {
    setStatusTip( tr( "Open a file", "File open action status tip" ) );
    setToolTip( tr( "Open a file", "File open action tool tip text" ) );
 
    connect( this, &QAction::triggered, [&] {
        QSettings settings;
        
        static QString defaultFilter = "All Files (*.*)";
        auto const dir = settings.value( kFileOpenLastPathSettingsKey,  QDir::homePath()).toString();
        _fileOpenDialog = new FileOpenDialog( MainWindow::instance(), dir );
        if(!_fileOpenDialog->exec()) {
            return;
        }

        auto const filenames = _fileOpenDialog->selectedFiles();
        if(!filenames.isEmpty() && _fileOpenDialog->showImportOptions() ) {
            // show import options dialog here

        }

        for(auto const filename : filenames) {
            FileOpener::instance()->openFile( filename );
        }

        if(!filenames.empty()) {
            QFileInfo file_info( filenames.last() );
            settings.setValue( kFileOpenLastPathSettingsKey, file_info.absolutePath() );
        }
    });
}

// virtual
ts3d::FileOpen::~FileOpen( void ) {
}
