#Creeper is a cross platform viewer application build on the HOOPS native platform and Qt.

##Building on Windows
Pre-requisites:

* VS 2015 or VS 2017 (64-bit)
* Qt 5.x (64-bit)
* HOOPS Visualize 201x
* Sprocket compatible version of HOOPS Exchange 201x
---
1. Open a command prompt that has VS and Qt configured.
 * Open a Visual Studio 64-bit compiler command prompt, then execute qtenv2.bat from your Qt installations's bin folder. (for example `C:\Qt\5.11.1\msvc2015_64\bin\qtenv2.bat`)
 * To verify your command prompt is configured, run `qmake.exe`, and you should see the command line usage printed. In addition, run `cl.exe`, and you should see the command line usage printed.
1. Specify the locations of your HOOPS Platform components.
 * Copy the file `build/qmake/config-local.sample` to `build/qmake/config-local.pri`'
 * Edit the file `build/qmake/config-local.pri` and update the variable in the `win32` section so they reflect the installation location on your computer.
 ** NOTE: Never commit your copy of config-local.pri. Everyone's will be different!
1. Generate the Makefiles by executing `qmake creeper.pro` in the `build/qmake` folder. You should not see any errors or warnings. If you do, hopefully the messages are self-explanatory.
1. Compile by executing `nmake`. You should not see any warnings or errors.
1. Verify the build product `viewer.exe` is present in the bin folder.

##Run the application
1. Make sure both Visualize and Exchange DLL folders are in your PATH.
  * For example, execute `set PATH=%PATH%;C:\ts3d\HOOPS_Visualize_2018_SP2\bin\win64_v140d;C:\ts3d\HOOPS_Exchange_Publish_2018_SP2\bin\win64`
1. Execute 'bin\viewer.exe'.


##Using Visual Studio
Once you have successfully built and run from the command prompt, you can be sure that your configuration is correct. In addition to using the command prompt, you can automatically generate a visual studio workspace for building, running and debugging. To do this, type `qmake -r -tp vc`. Open this workspace from the command prompt (so the process inherits the PATH environment you set above) by typing 'devenv viewer.sln'. Once open, ensure the build target is 64-bit debug. You can build and run the solution from withint Visual Studio.

##Adding Files to the Project
1. Examine the folder structure within `src`. It will be evident how to organize any files you may want to add.
1. Start by creating the files inside `src` folder.
1. Edit `build/qmake/src.pro` and add the base filename to the list.
1. Re-run `qmake -r` or `qmake -r -tp vc` to regenerate the makefiles or workspace.



