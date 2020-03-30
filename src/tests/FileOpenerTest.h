#pragma once
#include <ui/FileOpener.h>

namespace ts3d {
    class FileOpenerTest: public QObject {
        Q_OBJECT;

	    public:
	        virtual ~FileOpenerTest( void );

	    private:
	    	bool _modelLoaded;
	    	bool _cadModelLoaded;
			bool _importComplete;
	    	QString _errorMessage;
	    	QString _loadedFileName;
			float _progress;
			static const QString ROOT_TEST_DIR; 
			QWidget * _mainWidget; //This is a handle to the QMdiArea in our app

			void dismissMessageBox( int delay = 0 );
			void resetTestData();

	    private slots:
	    	//This is called before any tests are run
	    	void initTestCase();

	    	//These are the tests cases and associated
	    	//data functions
        	void testOpenFileBadFileLocation();
        	void testOpenFileBadFileLocation_data();
        	void testOpenFileUnknownFileType();
			void testCancelFunction();
			void testCancelFunction_data();
			void testOpenValidModel();
			void testOpenValidModel_data();
			void testOpenValidCADModel();
			void testOpenValidCADModel_data();

        public slots:
        	void onModelOpened( HPS::Model const model, QString fileName );
        	void onCadModelOpened( HPS::CADModel const cadModel, QString fileName );
        	void onFailure( QString failureMessage );
			void begin( QString fileName );
			void progressChanged( float progress );
			void complete( void );

    };
}
