@echo off
REM This script runs the tests using MSYS2. 

@REM setlocal: any environment variables set in this script do not affect the parent environment.
setlocal

set BASH=C:\msys64\usr\bin\bash.exe

if not exist "%BASH%" (
  echo MSYS2 not found. Please run bootstrap.cmd first.
  exit /b 1
)

REM Capture current directory in Windows form.
set WIN_WORKING_DIR=%CD%

"%BASH%" -l -c "cd \"$(cygpath -u '%WIN_WORKING_DIR%')\" && ./run-tests"
