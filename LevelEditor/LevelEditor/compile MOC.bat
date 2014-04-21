@echo off
set ENABLED=true

if %ENABLED% == true (
	for %%a in ("*.h") do (
		findstr /N Q_OBJECT "%%a" > tempLogFile && echo exporting %%a && moc48 %%a > %a%%%~na_mock.cpp
		del tempLogFile
	)
) else (
	echo rebuilding moc files skipped, re-enable in batch file
)
