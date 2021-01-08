REM Batch file to erase unneeded and possibly large files if using Visual Studio

REM *****Note:  it would be a BAD IDEA to take this outside this folder or the folder
REM  where you keep your own C++ code -- it may delete something you want!  Be careful! ****

REM  Aug 2020


REM Get rid of folders we don't need, possibly containing large files
for /r . %%d in (Debug,Release,x64,.vs,Backup) do @if exist "%%d" rd /s/q "%%d"

del /s *.o      REM Delete Unix- or MinGW-created files
del /s a.out
del /s a.exe
del /s core
del /s *.dep

REM Get rid of other large files
del /s *.sdf	REM Earlier versions (2010-2015)   -- can skip if using 2017 or later 
del /s *.obj	REM Still needed because I'm using a diff intermed directory for SSDL library

REM and miscellany
del /s *.log	
del /s *.tlog
del /s *.idb
del /s *.lastbuildstate
del /s *.ifc    REM compiled version of a VS C++ module








