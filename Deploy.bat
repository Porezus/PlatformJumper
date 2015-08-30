rmdir /s /q Deploy
mkdir Deploy

xcopy proj.win32\Release.win32\*.exe Deploy
xcopy proj.win32\Release.win32\*.dll Deploy
xcopy /s Resources Deploy
