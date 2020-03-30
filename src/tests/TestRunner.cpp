#include <QTest>
#include <ui/tests/FileOpenerTest.h>
#include <ui/tests/MainWindowTest.h>
#include <ui/tests/TestRunner.h>
#include <ui/Application.h>

int main(int argc, char *argv[]){
    ts3d::Application::initializeInstance( argc, argv );

    int status = 0;
    auto runTest = [&status, argc, argv](QObject* obj) {
        status |= QTest::qExec(obj, argc, argv);
    };

    // run suite
    runTest(new ts3d::FileOpenerTest);
    runTest(new ts3d::MainWindowTest);

    ts3d::Application::destroyInstance();
    return status;
}