#pragma once
namespace ts3d {
    class HPSWidget;
    /*! \class HPSMdiSubWindow
    \brief QMdiSubWindow containing a ts3d::HPSWidget

    Usually, the ts3d::MainWindow object will respond to the ts3d::FileOpener object
    and create an instance of a ts3d::HPSMdiSubWindow. However, this object is not
    dependent on the ts3d::MainWindow.
    */
    class HPSMdiSubWindow : public QMdiSubWindow {
        Q_OBJECT;
    public:
        /*! \brief Constructor taking an HPS::CADModel */
        HPSMdiSubWindow( QWidget *parent, HPS::CADModel const model, QSize const &initialSize );

        /*! \brief Constructor taking a generic HPS::Model */
        HPSMdiSubWindow( QWidget *parent, HPS::Model const model, QSize const &initialSize );

        /*! \brief Convenience getter for the HPS::View */
        HPS::View getView( void ) const;

        /*! \brief Convenience getter for the HPS::Canvas */
        HPS::Canvas getCanvas( void ) const;

        /*! \brief Convenience getter for the generic HPS::Model */
        HPS::Model getModel( void ) const;

        /*! \brief Getter for the HPS::CADModel associated with this widget. */
        HPS::CADModel getCADModel( void ) const;

        /*! \brief Determines if the HPS::CADModel is valid. It is valid
        when the Exchange Sprocket was used to load the file. Otherwise
        the HPS::CADModel is invalid. the HPS::Model obtained from
        getModel() is always valid.
        */
        bool isCADModelValid( void ) const;
    
    signals:
        void closed( void );

    protected:
        virtual void closeEvent( QCloseEvent *event ) override;

    private:
        HPSWidget *createHPSWidget( void );

        HPS::CADModel _cadModel;
        bool _isCadModelValid;
        QPointer<HPSWidget> _widget;
    };
}