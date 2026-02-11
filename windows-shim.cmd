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

if "%~2"=="" (
  set MSYS_SHELL=-msys
) else (
  set MSYS_SHELL=%~2
)

set BASH_SCRIPT=%~1

REM Capture current directory in Windows form.
set WIN_WORKING_DIR=%CD%

"%LAUNCHER%" %MSYS_SHELL% -here -defterm -no-start -c "exec ./%BASH_SCRIPT%"
