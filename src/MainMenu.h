#pragma once

namespace ts3d {
    /*! \class MainMenu
    \ingroup toplevel_objects
    \brief The main menu used in ts3d::MainWindow
    */
    class MainMenu : public QMenuBar {
        Q_OBJECT;
    public:
        MainMenu( QWidget *parent );
        virtual ~MainMenu( void );
    
    private slots:
        void onModelOpened( HPS::Model model, QString filename );
        void onCadModelOpened( HPS::CADModel, QString filename );

    private:
        struct RecentlyUsedFile {
            QPointer<QAction> action;
            QString filename;
            RecentlyUsedFile( QAction *a, QString const &fn ) : action( a ), filename( fn ) {}
        };

        void addRecentlyUsedFile( QString const filename );
        QList<RecentlyUsedFile> _recentlyUseFilesList;
        QPointer<QMenu> _recentlyUsedFilesMenu;
    };
}