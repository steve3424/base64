@echo off

set BATCH_DIR=%~dp0
set BUILD_DIR=%BATCH_DIR%zbin_test

mkdir %BUILD_DIR%
pushd %BUILD_DIR%

cl %BATCH_DIR%test\tests.c

popd

call %BUILD_DIR%\tests.exe
