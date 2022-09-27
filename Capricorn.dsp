# Microsoft Developer Studio Project File - Name="Capricorn" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Capricorn - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Capricorn.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Capricorn.mak" CFG="Capricorn - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Capricorn - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Capricorn - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Capricorn - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "release output"
# PROP Intermediate_Dir "release intermediate"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"release output/Cyclops.exe"

!ELSEIF  "$(CFG)" == "Capricorn - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "debug_output"
# PROP Intermediate_Dir "debug_intermediate"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Capricorn - Win32 Release"
# Name "Capricorn - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Capricorn.cpp
# End Source File
# Begin Source File

SOURCE=.\Capricorn.rc
# End Source File
# Begin Source File

SOURCE=.\CapSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\CapThread.cpp
# End Source File
# Begin Source File

SOURCE=.\CtrlStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCalc.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgList.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgResults.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\PageAnalyse.cpp
# End Source File
# Begin Source File

SOURCE=.\PageBase.cpp
# End Source File
# Begin Source File

SOURCE=.\PageDiff.cpp
# End Source File
# Begin Source File

SOURCE=.\PageFlags.cpp
# End Source File
# Begin Source File

SOURCE=.\PageImport.cpp
# End Source File
# Begin Source File

SOURCE=.\PageInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\PageMedian.cpp
# End Source File
# Begin Source File

SOURCE=.\PageRange.cpp
# End Source File
# Begin Source File

SOURCE=.\SJData.cpp
# End Source File
# Begin Source File

SOURCE=.\SJDataBase.cpp
# End Source File
# Begin Source File

SOURCE=.\SJDataSet.cpp
# End Source File
# Begin Source File

SOURCE=.\SJFileCSV.cpp
# End Source File
# Begin Source File

SOURCE=.\SJFileIn.cpp
# End Source File
# Begin Source File

SOURCE=.\SJFileProject.cpp
# End Source File
# Begin Source File

SOURCE=.\SJLimits.cpp
# End Source File
# Begin Source File

SOURCE=.\SJParamSet.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\ViewBase.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewOne.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewTime.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewTwo.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Capricorn.h
# End Source File
# Begin Source File

SOURCE=.\CapSheet.h
# End Source File
# Begin Source File

SOURCE=.\CapThread.h
# End Source File
# Begin Source File

SOURCE=.\CtrlStatus.h
# End Source File
# Begin Source File

SOURCE=.\DlgCalc.h
# End Source File
# Begin Source File

SOURCE=.\DlgList.h
# End Source File
# Begin Source File

SOURCE=.\DlgResults.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\PageAnalyse.h
# End Source File
# Begin Source File

SOURCE=.\PageBase.h
# End Source File
# Begin Source File

SOURCE=.\PageDiff.h
# End Source File
# Begin Source File

SOURCE=.\PageFlags.h
# End Source File
# Begin Source File

SOURCE=.\PageImport.h
# End Source File
# Begin Source File

SOURCE=.\PageInfo.h
# End Source File
# Begin Source File

SOURCE=.\PageMedian.h
# End Source File
# Begin Source File

SOURCE=.\PageRange.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SJData.h
# End Source File
# Begin Source File

SOURCE=.\SJDataBase.h
# End Source File
# Begin Source File

SOURCE=.\SJDataSet.h
# End Source File
# Begin Source File

SOURCE=.\SJFileCSV.h
# End Source File
# Begin Source File

SOURCE=.\SJFileIn.h
# End Source File
# Begin Source File

SOURCE=.\SJFileProject.h
# End Source File
# Begin Source File

SOURCE=.\SJLimits.h
# End Source File
# Begin Source File

SOURCE=.\SJParamSet.h
# End Source File
# Begin Source File

SOURCE=.\SJPtrList.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\ViewBase.h
# End Source File
# Begin Source File

SOURCE=.\ViewOne.h
# End Source File
# Begin Source File

SOURCE=.\ViewTime.h
# End Source File
# Begin Source File

SOURCE=.\ViewTwo.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\mfc\listbox\IconLBDemo\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\MFC\LISTBOX\IconLBDemo\RES\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\MFC\LISTBOX\IconLBDemo\RES\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Capricorn.ico
# End Source File
# Begin Source File

SOURCE=.\res\Capricorn.rc2
# End Source File
# Begin Source File

SOURCE=.\RES\Cyclops.ico
# End Source File
# Begin Source File

SOURCE=.\RES\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\upper.ico
# End Source File
# End Group
# End Target
# End Project
