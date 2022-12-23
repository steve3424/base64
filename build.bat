@echo off

set BATCH_DIR=%~dp0
set BUILD_DIR=%BATCH_DIR%zbin

mkdir %BUILD_DIR%
pushd %BUILD_DIR%

cl ..\src\main.c

popd