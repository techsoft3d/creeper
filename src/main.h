#pragma once

/*! \mainpage Creeper - A Qt-based HOOPS viewer
\tableofcontents

This project is a built-from-scratch Qt-based graphical user interface that illustrates
the basic use of HOOPS Visualize HPS, HOOPS Exchange, and the Exchange Sprocket.

\section how_to_build How to build the application
In order to build the application, you will need to fulfill the pre-requisites listed below.
You can use the development IDE of your choice, provided you are acquainted with how to use
any of the packaged build configurations to generate a suitable workspace.

\subsection build_prerequisites Prerequisites
This project has the following dependencies:
-# Qt-5.x.y
-# HOOPS Exchange 2019 or newer
-# HOOPS Visualize HPS 2019 or newer

\subsection build_qt How to Build Using qmake
Crepper contains a qmake-based, cross-platform build configuration. These instructions will step
you through the process of configuring and building using Qt tools.

\subsubsection build_configuration Configuring HOOPS Toolkit Locations
Before you can build the project, you must specify the locations of Exchange and Visualize.
To do this, follow these steps.
-# Copy the file \c build/qmake/config-local.sample to \c build\qmake\config-local.pri.
-# Open \c build/qmake/config-local.pri using a text editor.
-# Edit the section(s) reflecting the build platform(s) to reflect your local HOOPS installations.

\subsubsection build_compile_link Compile and Link
At this point, you can build using Qt tools as you would for any Qt project. The top level project
file is \c build/qmake/creeeper.pro. Options for building include:
include:
-# Use Qt Creator with the \c .pro file as the input.
-# Use \c qmake to generate a \c Makefile.
-# Use \c qmake to generate a "native" IDE workspace. Change your \c pwd to \c build/qmake.
    - \c qmake \c -tp \c vc \c creeper.pro
    - \c qmake \c -spec \c macx-xcode \c creeper.pro

\section running_app Running the application
In order to successfully execute the application, it must be able to find the HOOPS Exchange
dynamic libraries at runtime. The location is not hard coded, so the library search paths
you specify will for your platform will be used in an attempt to find them.

- \c PATH on Windows
- \c DYLD_LIBRARY_PATH on macOS
- \c LD_LIBRARY_PATH on Linux

\section how_to_navigate_source How to navigate the source code
Here are a few pointers for learning how this project is arranged. This basic understanding
of the approach will be helpful if you intend to make additions or modifications.



\namespace ts3d
\brief The \c ts3d namespace is used to contain all functionality.

\defgroup toplevel_objects
\brief The objects contained here are the highest level objects in the application.

*/

/*! \brief The main entry point for the application.
*/
int main(int argc, char *argv[]);
