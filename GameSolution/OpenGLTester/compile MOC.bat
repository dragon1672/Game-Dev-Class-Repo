@echo off
set ENABLED=true

if %ENABLED% == true (
	echo creating moc files
	moc48 MyWindow.h > MyWindow_mock.cpp
	moc48 DebugSlider.h > DebugSlider_mock.cpp
	moc48 MyGUI.h > MyGUI_mock.cpp
	echo creating moc files complete
) else (
	echo rebuilding moc files skipped, re-enable in batch file
)