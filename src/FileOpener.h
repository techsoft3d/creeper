#pragma once

namespace ts3d {
    /*! \class FileOpener
    \brief Singleton object used to open files
    */
    class FileOpener : public QObject {
        Q_OBJECT;
    public:
        /*! \brief Obtain the singleton instance of this object.
        */
        static FileOpener *instance( void );

    public slots:
        /*! \brief Use this method to load a file by name.
        */
        void openFile( QString const &filename );

        /*! \brief Use this method to cancel a load in progress.
        */
        void cancel( void );

    signals:
        /*! \brief This signal is emitted when an HPS model is loaded.
        */
        void modelOpened( HPS::Model model, QString filename );
        
        /*! \brief This signal is emitted when a CAD model is loaded.
        */
        void cadModelOpened( HPS::CADModel model, QString filename );

        /*! \name Progress Signals
        \brief This group of signals are emitted to reflect the status
        of a load. 
        @{ */
        /*! \brief Emitted when loading of a file begins
        */
        void begin( QString filename );
        /*! \brief Emitted to reflect progess when 

        This signal will always be followed by 0 or more
        progressChanged(float progress) signals.

        It is guarenteed that complete() will be emitted.
        */
        void progressChanged( float progress );

        /*! \brief Emitted when a loading failure occurs
        */
        void failure( QString failureMessage );

        /*! \brief Emitted when loading is complete.
        */
        void complete( void );
        /*! @} */

    private:
        FileOpener( void );
        virtual ~FileOpener( void );
        bool handleNotifier( HPS::IONotifier notifier );
        bool _cancelled;
    };
}