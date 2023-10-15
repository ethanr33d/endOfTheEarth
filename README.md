# End of the Earth

Summer project. Goal was to make an infinite runner game using C++ and the SDL graphics library. Still a work in progress, but prebuilt development/concept binaries are available in the releases section.

## Build Instructions
### Windows using Visual Studio & Vcpkg
**Prerequisites**
* Visual Studio 2022
* Git 
* Vcpkg 

**Installation**
1. Install Visual Studio 2022 ([Visual Studio homepage](https://visualstudio.microsoft.com/)).

   - Make sure the Desktop Development with C++ workload is selected during installation
3. Install Git ([Git homepage](https://visualstudio.microsoft.com/))
4. Install Vcpkg ([Vcpkg homepage](https://vcpkg.io/en/))
5. Install packages

   Vcpkg is the dependency manager End of the Earth uses. It integreates easily with Visual Studio.
Once vcpkg is installed, cd into the vcpkg directory and run the following command to install necessary build dependencies:
   ```
   vcpkg install sdl2 sdl2-ttf sdl2-image --triplet=x64-windows
   ```
   Make sure to integrate vcpkg into visual studio if not already done:
   ```
   vcpkg integreate install
   ```
6. Clone game repository into directory of choice
   
   ```
   git clone https://github.com/NaturalBornNerd/endOfTheEarth
   ```
7. Open the solution (.sln) in Visual Studio
8. Set build target
   - Debug: Slower build with breakpoint/code stepping support
   - Release: Optimized final build used for releases
9.  Build solution through Build Menu -> Build Solution. The build is stored in the x64 folder in the local repository directory as either Debug or Release depending on build target. The int folder contains build intermediates (.obj, build logs, etc).
10. Run program through directory folder or within Visual Studio using Local Windows Debugger button or through the Debug Menu -> Start Debugging.
