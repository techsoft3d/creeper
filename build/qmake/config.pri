win32:PROJECT_ROOT = $$system(cd)
!win32:PROJECT_ROOT = $$system(pwd)

exists(config-local.pri) { 
    include(config-local.pri)
} else {
    error("The file 'config-local.pri' is missing. Copy 'config-local.sample' to 'config-local.pri', edit it, and re-run qmake")
}

CONFIG -= debug_and_release debug_and_release_target release
CONFIG += debug
