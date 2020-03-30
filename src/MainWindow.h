#pragma once

namespace ts3d {
    class HPSWidget;
    class HPSMdiSubWindow;
    /*! \class MainWindow
    \ingroup toplevel_objects
    \brief This is the top level application window for the application.

    The central widget of this main window object is a \c QMdiArea.
    */
    class MainWindow : public QMainWindow {
        Q_OBJECT;
    public:
        /*! \brief Since there is only one instance of this object per application,
        you can use this method to easily gain access to it.

        The first call to this function will initialize the instance and therefore
        should _only_ be called by the initialization process within ts3d::Application.
        */
        static MainWindow *instance( void );

        /*! \brief Getter for the currently active ts3d::HPSWidget object in the
        MDI area. 

        This may be \c nullptr if there currently is no active widget.
        \return A pointer to the current ts3d::HPSWidget or \c nullptr if none exists.
        */
        HPSWidget *getCurrentHPSWidget( void ) const;

        /*! \brief Getter for the current active ts3d::HPSMdiSubWindow object.
        \return A pointer to the current ts3d::HPSMdiSubWindow or \c nullptr if non exists.
        \sa getCurrentHPSWidget()
        */
        HPSMdiSubWindow *getActiveHPSMdiSubWindow( void ) const;
    
    public slots:
        /*! \brief Invoked when a file is opened via ts3d::FileOpener

        This method is implemented to create and initialize the ts3d::HPSWidget for display.
        */
        void onModelOpened( HPS::Model const model, QString const &filename );
        /*! \brief Invoked when a CAD model is opened via ts3d::FileOpener

        This method is implemented to create and initialize the ts3d::HPSWidget for display.
        */
        void onCadModelOpened( HPS::CADModel const cadModel, QString const &filename );
        QMessageBox::StandardButton showInformationMessageBox( QString const &message, QMessageBox::StandardButtons buttons = QMessageBox::Ok );


    protected:
        /*! \brief Implemented to accept drops.
        */
        virtual void dragEnterEvent( QDragEnterEvent * event ) override;

        /*! \brief Implemented to attempt to open the dropped file via ts3d::FileOpener.
        */
        virtual void dropEvent( QDropEvent * event ) override;

        /*! \brief Implemented to preserve the UI layout and state.
        */
        virtual void closeEvent( QCloseEvent *event ) override;

    private:
        /*! \brief Private constructor to enforce singleton design.
        */
        MainWindow( void );

        /*! \brief Destructor
        */
        virtual ~MainWindow( void );

        /*! \brief Used to compute a reasonable initial size for the HPS widget
        */
        QSize getIntialHpsSubWindowSize( void ) const;

        /*! \brief Holder for the mdi child area
        */
        QPointer<QMdiArea> _mdiArea;

        /*! \brief The progress bar, connected to loading progress.
        */
        QPointer<QProgressDialog> _progressDialog;
    };
}