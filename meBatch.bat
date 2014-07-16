call "c:\Program Files (x86)\Microsoft Visual Studio 11.0\VC\vcvarsall.bat" x86_amd64

@echo off

call :processDir
goto :eof

:processDir
::build projects
for %%a in ("*.sln") do (
	MSBuild "%%a"
)
::loop folders
for /D %%d in (*) do (
	cd %%d
	call :processDir
	cd ..
)
goto :eof

::not compiling
:eof