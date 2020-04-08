# Creeper is a cross platform viewer application build on the HOOPS native platform and Qt.

## Step 1 - Prerequisites
* VS 2015 or VS 2017 (Windows)
* Xcode 11.3.1 (macOS)
* GCC 7.4.0 (Linux)
* Qt 5.x (64-bit)
* HOOPS Visualize 20xx
* Sprocket compatible version of HOOPS Exchange 20xx

## Step 2 - Configure the Build
In order to proceed with any of the build options, you must first specify the locations of HOOPS Visualize and HOOPS Exchange.

1. Copy `creeper/build/qmake/config-local.sample` to `creeper/build/qmake/config-local.pri`.
1. Edit `creeper/build/qmake/config-local.pri` and update the locations of the HOOPS Platform Toolkits to reflect your local folders.

## Step 3 - Build
Building creeper using the native Qt build tools is straightforward and similar on each platform. Differences for each
platform are noted. Options also exist for Visual Studio and XCode.

### (Option 1 ) - QtCreator (all platforms)
1. Launch QtCreator
1. Choose Open Project and select `creeper/build/qmake/creeper.pro`.
1. Click "Configure Project" after making any desired changes in the window that appears.
1. Click the "Build" button.

### (Option 2) - `qmake` (all platforms)
1. Open a command line window/terminal. Ensure prerequisite tools (Qt, compiler) are available in your `PATH`.

	* On Windows, ensure this is a Visual Studio 64-bit compiler command prompt. Execute `qtenv2.bat` to add Qt variables. To verify your command prompt is configured, run `qmake.exe`, and you should see the command line usage printed. In addition, run `cl.exe`, and you should see the command line usage printed.
	* On macOS and Linux, manually add the Qt `bin` folder to your `PATH`.
1. Change directory to `creeper/build/qmake`.
1. Generate the `Makefile` by executing `qmake creeper.pro`. You should not see any errors or warnings. If you do, hopefully the messages are self-explanatory.
1. Compile by executing `nmake` on Windows, or `make` on Linux and macOS. You should not see any warnings or errors.
1. Verify the build product `viewer.exe` (Windows) or `viewer` is present in the `bin` folder.

### (Option 3) - Visual Studio (Windows)
1. Follow steps 1 and 2 of Option 2 above.
1. Generate the Visual Studio project file by executing `qmake -tp vc creeper.pro`. You should not see any errors or warnings.
1. Add the HOOPS Visualize DLL folders are in your `PATH`.
	* For example, `set PATH=%PATH%;C:\ts3d\HOOPS_Visualize_2020\bin\win64_v140d`.
1. Open the project by typing `devenv viewer.vcxproj`.

### (Option 4) - XCode (macOS)
1. Follow steps 1 and 2 of Option 2 above.
1. Generate the Visual Studio project file by executing `qmake -spec macx-xcode creeper.pro`. You should not see any errors or warnings.
1. Open the project by typing `open viewer.xcodeproj`.

## Step 4 - Running the application 
In order to run the application, it needs to locate the HOOPS Visualize and HOOPS Exchange dynamic libraries. HOOPS Visualize is a linktime dependency so its dynamic libraries are loaded as the executable is launched.

* [Windows] The `PATH` environment variable must contain the `bin/<arch>` debug folder.
* [macOS, Linux] The application is linked with an `rpath` specification. No additional runtime configuration is needed for Visualize.

The Exchange dynamic libraries are loaded using `dlopen` or `LoadLibraryEx` once the application starts. By default, the application will attempt to use the folder you specified for the build settings. You can override this location by using the command line option `-x`.

### (Option 1) - QtCreator (all platforms)
These steps describe how to specify the required variables and arguments to run Creeper from within QtCreator.
1. [Windows] Add the Visualize bin directory to the `PATH` environment variable.
	* Click on the `Projects` button in the vertical tool ribbon on the left of the window.
	* Click on the `Run` button located in the `Active Project`, `Build & Run` section of the main window that appears.
	* At the bottom of the `Run Settings` window, edit the `Run Environment`.
	* Add the variable `PATH` and specify the Visualize debug DLL folder for your architecture.
1. Build and Debug as normal.

### (Option 2) - Command Line (all platforms)
1. [Windows] Add the HOOPS Visualize DLL folders are in your `PATH`.
	* For example, `set PATH=%PATH%;C:\ts3d\HOOPS_Visualize_2020\bin\win64_v140d`.
1. Execute `bin/viewer.exe` (Windows), `bin/viewer` (Linux), or `open bin/viewer.app` (macOS).

### (Option 3) - Visual Studio (Windows)
1. If you followed the Build instructions correctly, you have already set your `PATH` environment variable.
1. Build and Debug as normal.

### (Option 4) - XCode (macOS)
1. As noted previously, macOS makes use of the `rpath` mechanism. No additional settings are required.
1. Build and Debug as normal.

## Release Build
In order to generate a build configuration for an optimized application without debugging information, you must re-reun `qmake` with options to specify the release configuration.

### (Option 1) - QtCreator (all platforms)
1. QtCreator is configured with options for Release builds automatically. Just use the selector to pick the configuration.

### (Option 2) - `qmake` (all platforms)
1. Use the command `qmake "CONFIG += release" -after`.

### (Option 3) - Visual Studio (Windows)
1. Use the command `qmake "CONFIG += release" -after -tp vc`.

### (Option 4) - XCode (macOS)
1. Use the command `qmake "CONFIG += release" -after -spec macx-xcode`.

## Adding Files to the Project
1. Examine the folder structure within `src`. It will be evident how to organize any files you may want to add.
1. Start by creating the files inside `src` folder.
1. Edit `build/qmake/src.pro` and add the base filename to the list.
1. Re-run `qmake`, `qmake -tp vc`, or `qmake -spec macx-xcode` to regenerate `Makefile` or the workspace.


