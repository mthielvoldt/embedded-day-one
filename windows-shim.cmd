@echo off
REM This script runs the tests using MSYS2. 

@REM setlocal: any environment variables set in this script do not affect the parent environment.
setlocal

set LAUNCHER=C:\msys64\msys2_shell.cmd

if not exist "%LAUNCHER%" (
  echo MSYS2 not found. Please install MSYS2. See onboarding.md for instructions. 1>&2
  exit /b 1
)

if "%~1"=="" (
  echo Usage: call windows-shim.cmd ^<bash-script-name^>
  exit /b 2
)

set BASH_SCRIPT=%~1


"%LAUNCHER%" -mingw -here -defterm -no-start -c "exec ./%BASH_SCRIPT%"
