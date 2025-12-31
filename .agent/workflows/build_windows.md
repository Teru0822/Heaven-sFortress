# Build Setup for Heaven's Fortress
1. Install prerequisites:
   - CMake
   - Visual Studio Code (or Visual Studio)
   - Git
   - vcpkg (install in C:\vcpkg or user directory)

2. Configure vcpkg:
   ```powershell
   ./vcpkg install sdl2 sdl2-mixer[mpg123] glew freeglut opengl --triplet x64-windows
   ```

3. Build:
   ```powershell
   ./build_installer.ps1
   ```
   
4. Output:
   - Installer/Zip will be in `build_local` directory.
