@echo off
setlocal EnableDelayedExpansion

echo Enter some file names from the resources directory.
set /p user_input="File names: "

set filenames=

for %%s in (%user_input%) do (
    set filenames=!filenames! resources/%%s
)

set filenames=%filenames:~1%
a.out %filenames%
pause
