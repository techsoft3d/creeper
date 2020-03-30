#include "ui_pch.h"
#include <main.h>
#include <Application.h>

int main( int argc, char *argv[] ) {
    try {
        ts3d::Application::initializeInstance( argc, argv );
        auto result =  ts3d::Application::instance()->exec();
        ts3d::Application::destroyInstance();
        return result;
    } catch( std::exception e ) {
        qCritical() << "Caught exception: " << e.what() << endl;
        return -1;
    }

    return 0;
}
