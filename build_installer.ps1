# Build script for Heaven's Fortress Installer (Windows)

$buildDir = "build_local"

# Check if build directory exists, create if not
if (-not (Test-Path $buildDir)) {
    New-Item -ItemType Directory -Path $buildDir | Out-Null
}

Set-Location $buildDir

# Check for vcpkg toolchain
$vcpkgPath = $env:VCPKG_ROOT
if (-not $vcpkgPath) {
    # Try common location or ask user
    if (Test-Path "C:\vcpkg") {
        $vcpkgPath = "C:\vcpkg"
    }
    elseif (Test-Path "C:\Users\teruc\vcpkg") {
        $vcpkgPath = "C:\Users\teruc\vcpkg"
    }
}

$cmakeArgs = @("..")
if ($vcpkgPath) {
    Write-Host "Using vcpkg at: $vcpkgPath" -ForegroundColor Cyan
    
    # Install dependencies
    Write-Host "Installing dependencies via vcpkg..." -ForegroundColor Cyan
    & "$vcpkgPath\vcpkg.exe" install sdl2 sdl2-mixer[mpg123] glew freeglut opengl --triplet x64-windows
    
    $cmakeArgs += "-DCMAKE_TOOLCHAIN_FILE=$vcpkgPath/scripts/buildsystems/vcpkg.cmake"
    $cmakeArgs += "-DVCPKG_TARGET_TRIPLET=x64-windows"
}
else {
    Write-Host "VCPKG_ROOT not set. Attempting build without explicit toolchain..." -ForegroundColor Yellow
}

# Configure
Write-Host "Configuring CMake..." -ForegroundColor Green
& cmake @cmakeArgs
if ($LASTEXITCODE -ne 0) {
    Write-Error "CMake configuration failed."
    exit 1
}

# Build
Write-Host "Building Release..." -ForegroundColor Green
& cmake --build . --config Release
if ($LASTEXITCODE -ne 0) {
    Write-Error "Build failed."
    exit 1
}

# Package
Write-Host "Generating Installer with CPack..." -ForegroundColor Green
& cpack -C Release
if ($LASTEXITCODE -ne 0) {
    Write-Error "Packaging failed."
    exit 1
}

Write-Host "Installer generated successfully in $buildDir!" -ForegroundColor Green
Get-ChildItem *.exe
