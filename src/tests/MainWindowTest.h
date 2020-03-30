#pragma once
#include <ui/MainWindow.h>

namespace ts3d {
    class MainWindowTest: public QObject {
        Q_OBJECT;

        public:
	        virtual ~MainWindowTest( void );

        private slots:
            //This is called before any tests are run
	    	void initTestCase();

            //Tests
            void testOnValidModelOpened();
    };
}