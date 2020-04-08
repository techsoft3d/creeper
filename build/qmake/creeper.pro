!include(config.pri) : error("Unable to include config.pri")
!include($${PROJECT_ROOT}/pri/exchange.pri) : error("Unable to include $${PROJECT_ROOT}/pri/exchange.pri")
!include($${PROJECT_ROOT}/pri/visualize.pri) : error("Unable to include $${PROJECT_ROOT}/pri/visualize.pri")

TEMPLATE = app
LANGUAGE = C++
CONFIG *= qt precompile_header c++14 exceptions rtti

QT *= gui widgets 
DESTDIR = $${PROJECT_ROOT}/bin
TARGET = viewer
MOC_DIR = .moc
OBJECTS_DIR = .obj
INCLUDEPATH *= ../../src
PRECOMPILED_HEADER = ../../src/ui_pch.h
# win32-msvc*:PRECOMPILED_SOURCE = ../../src/main.cpp
HEADERS += $$PRECOMPILED_HEADER
RESOURCES = ../../src/viewer.qrc
TRANSLATIONS = ../../src/resources/viewer_ja.ts

file_bases = \
    Application \
    CommandLineOptions \
    CuttingSectionDockWidget \
    FileOpenDialog \
    FileOpener \
    FileToolBar \
    HPSMdiSubWindow \
    HPSWidget \
    MainMenu \
    MainWindow \
    TreeDockWidget \
    Types \

# Look for testlib added when running qmake QT+=testlib
# and generate a "runTests" executable

!contains(QT,testlib){
	file_bases += main 
}
else{
	TARGET = runTests
}

for(file_base, file_bases) {
	SOURCES += ../../src/$${file_base}.cpp
	HEADERS += ../../src/$${file_base}.h
}

include(actions.pri)
include(tree.pri)
include(operators.pri)

contains(QT,testlib){
	include(tests.pri)
}

