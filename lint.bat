@echo off
setlocal enabledelayedexpansion

rem Runs clang-format on all *.cpp/*.h/*.json files in the project, excluding builds/
set "FILE_TYPES=*.cpp *.h *.json"
set "EXCLUDED=builds"

rem Make sure we have a clang-format to use.
rem Prefer any clang-format already in the user's %PATH%.
set "PATH=%PATH%;%VCINSTALLDIR%\Tools\Llvm\bin\"
where /q clang-format
if %ERRORLEVEL% neq 0 (
  echo Unable to find clang-format. Are you in a Developer command prompt?
  exit /b 1
)

rem Figure out how parallel we're gonna be
if /i "%1" == "-j" (
  shift
  set /a JOBS=%1
) else if "%1" == "" (
  set /a JOBS=%NUMBER_OF_PROCESSORS%
) else (
  echo Usage: lint.bat ^[-j ^<NUM_JOBS^>^]
  echo     If -j is not specified, NUM_JOBS defaults to the number of processors ^(%NUMBER_OF_PROCESSORS%^)
  exit /b 1
)

rem Generate a temporary filename to store the list of files
:gen_temp_file
set CPP_FILES="%TMP%\lint~%RANDOM%.tmp"
if exist %CPP_FILES% goto :gen_temp_file

rem Find all the files, and split them up amongs %JOBS% different files, round-robin style
set /a i=1
for /f "usebackq tokens=*" %%A in (`dir %FILE_TYPES% /s /b ^| findstr /v "%EXCLUDED%"`) do (
  rem !i! syntax here is "immediate" expansion: https://ss64.com/nt/delayedexpansion.html
  echo %%A >> %CPP_FILES%-!i!
  set /a i=!i! + 1
  if !i! gtr %JOBS% (set /a i=1)
)

rem start a clang-format task for each filelist created
for /l %%A in (1,1,%JOBS%) do (
  rem Use `start /b` to asynchronously spawn a new cmd.exe session running a clang-format and then a delete
  rem The clang-format cmd is stdout/stderr redirected to NUL, and the ^& is an "and then" joiner
  rem In batch, `foo & bar` is a way to indicate both foo and bar on one line, one after another. The ^ here
  rem is an escape, indicating that the & character should be passed to cmd, *not* start
  start "" /b cmd /c clang-format -i --files %CPP_FILES%-%%A >NUL 2>&1 ^& del %CPP_FILES%-%%A
)

rem Loop until all split filelists are deleted by their asynchronous cmds. Poor man's semaphore, file-style.
:wait_for_done
for /l %%A in (1,1,%JOBS%) do (
  if exist %CPP_FILES%-%%A goto :wait_for_done
)
