# Microsoft Developer Studio Project File - Name="MainGame" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=MainGame - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MainGame.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MainGame.mak" CFG="MainGame - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MainGame - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MainGame - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MainGame - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "MainGame - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "MainGame - Win32 Release"
# Name "MainGame - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Camera.cpp
# End Source File
# Begin Source File

SOURCE=.\CAnimObject.cpp
# End Source File
# Begin Source File

SOURCE=.\CControl.cpp
# End Source File
# Begin Source File

SOURCE=.\CDirectInput.cpp
# End Source File
# Begin Source File

SOURCE=.\CGame.cpp
# End Source File
# Begin Source File

SOURCE=.\CGrenade.cpp
# End Source File
# Begin Source File

SOURCE=.\CGrenadeLauncher.cpp
# End Source File
# Begin Source File

SOURCE=.\CJetpack.cpp
# End Source File
# Begin Source File

SOURCE=.\CMain.cpp
# End Source File
# Begin Source File

SOURCE=.\CMap.cpp
# End Source File
# Begin Source File

SOURCE=.\CMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\CMeshLoader.cpp
# End Source File
# Begin Source File

SOURCE=.\CModelMD2.cpp
# End Source File
# Begin Source File

SOURCE=.\CModelMS3D.cpp
# End Source File
# Begin Source File

SOURCE=.\CObject.cpp
# End Source File
# Begin Source File

SOURCE=.\CParticleSource.cpp
# End Source File
# Begin Source File

SOURCE=.\CPlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\CRocket.cpp
# End Source File
# Begin Source File

SOURCE=.\CRocketLauncher.cpp
# End Source File
# Begin Source File

SOURCE=.\CShotgun.cpp
# End Source File
# Begin Source File

SOURCE=.\CSound.cpp
# End Source File
# Begin Source File

SOURCE=.\CStaticObject.cpp
# End Source File
# Begin Source File

SOURCE=.\CTextureLoader.cpp
# End Source File
# Begin Source File

SOURCE=.\CWeapon.cpp
# End Source File
# Begin Source File

SOURCE=.\GLWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# Begin Source File

SOURCE=.\Math.cpp
# End Source File
# Begin Source File

SOURCE=.\Minigun.cpp
# End Source File
# Begin Source File

SOURCE=.\proc.cpp
# End Source File
# Begin Source File

SOURCE=.\Texload.cpp
# End Source File
# Begin Source File

SOURCE=.\Text.cpp
# End Source File
# Begin Source File

SOURCE=.\Timer.cpp
# End Source File
# Begin Source File

SOURCE=.\Vector3f.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Camera.h
# End Source File
# Begin Source File

SOURCE=.\CAnimObject.h
# End Source File
# Begin Source File

SOURCE=.\CControl.h
# End Source File
# Begin Source File

SOURCE=.\CDirectInput.h
# End Source File
# Begin Source File

SOURCE=.\CGame.h
# End Source File
# Begin Source File

SOURCE=.\CGrenade.h
# End Source File
# Begin Source File

SOURCE=.\CGrenadeLauncher.h
# End Source File
# Begin Source File

SOURCE=.\CJetpack.h
# End Source File
# Begin Source File

SOURCE=.\CMain.h
# End Source File
# Begin Source File

SOURCE=.\CMap.h
# End Source File
# Begin Source File

SOURCE=.\CMenu.h
# End Source File
# Begin Source File

SOURCE=.\CMeshLoader.h
# End Source File
# Begin Source File

SOURCE=.\CModelMD2.h
# End Source File
# Begin Source File

SOURCE=.\CModelMS3D.h
# End Source File
# Begin Source File

SOURCE=.\CObject.h
# End Source File
# Begin Source File

SOURCE=.\CParticleSource.h
# End Source File
# Begin Source File

SOURCE=.\CPlayer.h
# End Source File
# Begin Source File

SOURCE=.\CRocket.h
# End Source File
# Begin Source File

SOURCE=.\CRocketLauncher.h
# End Source File
# Begin Source File

SOURCE=.\CShotgun.h
# End Source File
# Begin Source File

SOURCE=.\CSound.h
# End Source File
# Begin Source File

SOURCE=.\CStaticObject.h
# End Source File
# Begin Source File

SOURCE=.\CTextureLoader.h
# End Source File
# Begin Source File

SOURCE=.\CWeapon.h
# End Source File
# Begin Source File

SOURCE=.\defs.h
# End Source File
# Begin Source File

SOURCE=.\GLWindow.h
# End Source File
# Begin Source File

SOURCE=.\keys.h
# End Source File
# Begin Source File

SOURCE=.\Math.h
# End Source File
# Begin Source File

SOURCE=.\meshes.h
# End Source File
# Begin Source File

SOURCE=.\Minigun.h
# End Source File
# Begin Source File

SOURCE=.\proc.h
# End Source File
# Begin Source File

SOURCE=.\sounds.h
# End Source File
# Begin Source File

SOURCE=.\Texload.h
# End Source File
# Begin Source File

SOURCE=.\Text.h
# End Source File
# Begin Source File

SOURCE=.\textures.h
# End Source File
# Begin Source File

SOURCE=.\Timer.h
# End Source File
# Begin Source File

SOURCE=.\Vector3f.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
