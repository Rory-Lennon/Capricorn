; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPageInfo
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "capricorn.h"
LastPage=0

ClassCount=21
Class1=CCapricornApp
Class2=CAboutDlg
Class3=CCapSheet
Class4=CCapThread
Class5=CCtrlStatus
Class6=CDlgCalc
Class7=CDlgList
Class8=CDlgResults
Class9=CMainFrame
Class10=CPageAnalyse
Class11=CPageBase
Class12=CPageDiff
Class13=CPageFlags
Class14=CPageImport
Class15=CPageInfo
Class16=CPageMedian
Class17=CPageRange
Class18=CViewBase
Class19=CViewOne
Class20=CViewTime
Class21=CViewTwo

ResourceCount=26
Resource1=IDD_ABOUTBOX
Resource2=IDD_LIST
Resource3=IDR_MAINFRAME
Resource4=IDD_DIFF (English (U.K.))
Resource5=IDD_MEDIAN (English (U.K.))
Resource6=IDD_RANGE (English (U.K.))
Resource7=IDD_FLAGS (English (U.K.))
Resource8=IDD_RESULTS
Resource9=IDD_CALC
Resource10=IDD_IMPORT (English (U.K.))
Resource11=IDD_BASE (English (U.K.))
Resource12=IDD_ANALYSE (English (U.K.))
Resource13=IDD_INFO (English (U.K.))
Resource14=IDD_DIFF
Resource15=IDD_ANALYSE
Resource16=IDD_MEDIAN
Resource17=IDD_BASE
Resource18=IDR_MAINFRAME (English (U.S.))
Resource19=IDD_IMPORT
Resource20=IDD_RANGE
Resource21=IDD_CALC (English (U.S.))
Resource22=IDD_LIST (English (U.S.))
Resource23=IDD_ABOUTBOX (English (U.S.))
Resource24=IDD_FLAGS
Resource25=IDD_RESULTS (English (U.S.))
Resource26=IDD_INFO

[CLS:CCapricornApp]
Type=0
BaseClass=CWinApp
HeaderFile=Capricorn.h
ImplementationFile=Capricorn.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=Capricorn.cpp
ImplementationFile=Capricorn.cpp
LastObject=IDOK

[CLS:CCapSheet]
Type=0
BaseClass=CPropertySheet
HeaderFile=CapSheet.h
ImplementationFile=CapSheet.cpp

[CLS:CCapThread]
Type=0
BaseClass=CWinThread
HeaderFile=CapThread.h
ImplementationFile=CapThread.cpp

[CLS:CCtrlStatus]
Type=0
BaseClass=CStatusBar
HeaderFile=CtrlStatus.h
ImplementationFile=CtrlStatus.cpp

[CLS:CDlgCalc]
Type=0
BaseClass=CDialog
HeaderFile=DlgCalc.h
ImplementationFile=DlgCalc.cpp

[CLS:CDlgList]
Type=0
BaseClass=CDialog
HeaderFile=DlgList.h
ImplementationFile=DlgList.cpp

[CLS:CDlgResults]
Type=0
BaseClass=CDialog
HeaderFile=DlgResults.h
ImplementationFile=DlgResults.cpp
Filter=D
VirtualFilter=dWC

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:CPageAnalyse]
Type=0
BaseClass=CPageBase
HeaderFile=PageAnalyse.h
ImplementationFile=PageAnalyse.cpp

[CLS:CPageBase]
Type=0
BaseClass=CPropertyPage
HeaderFile=PageBase.h
ImplementationFile=PageBase.cpp

[CLS:CPageDiff]
Type=0
BaseClass=CPageBase
HeaderFile=PageDiff.h
ImplementationFile=PageDiff.cpp

[CLS:CPageFlags]
Type=0
BaseClass=CPageBase
HeaderFile=PageFlags.h
ImplementationFile=PageFlags.cpp
LastObject=CPageFlags

[CLS:CPageImport]
Type=0
BaseClass=CPageBase
HeaderFile=PageImport.h
ImplementationFile=PageImport.cpp

[CLS:CPageInfo]
Type=0
BaseClass=CPageBase
HeaderFile=PageInfo.h
ImplementationFile=PageInfo.cpp
LastObject=CPageInfo

[CLS:CPageMedian]
Type=0
BaseClass=CPageBase
HeaderFile=PageMedian.h
ImplementationFile=PageMedian.cpp

[CLS:CPageRange]
Type=0
BaseClass=CPageBase
HeaderFile=PageRange.h
ImplementationFile=PageRange.cpp

[CLS:CViewBase]
Type=0
BaseClass=CWnd
HeaderFile=ViewBase.h
ImplementationFile=ViewBase.cpp

[CLS:CViewOne]
Type=0
BaseClass=CViewBase
HeaderFile=ViewOne.h
ImplementationFile=ViewOne.cpp

[CLS:CViewTime]
Type=0
BaseClass=CWnd
HeaderFile=ViewTime.h
ImplementationFile=ViewTime.cpp

[CLS:CViewTwo]
Type=0
BaseClass=CViewBase
HeaderFile=ViewTwo.h
ImplementationFile=ViewTwo.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=10
Control1=IDC_STATIC,static,1342308480
Control2=IDC_STATIC,static,1342308352
Control3=IDOK,button,1342373889
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,button,1342177287
Control8=IDC_STATIC,button,1342177287
Control9=IDC_STATIC,static,1342181390
Control10=IDC_STATIC,static,1342308352

[DLG:IDD_CALC]
Type=1
Class=CDlgCalc
ControlCount=2
Control1=IDC_PROG,msctls_progress32,1350565888
Control2=IDC_BUT_END,button,1342242816

[DLG:IDD_LIST]
Type=1
Class=CDlgList
ControlCount=2
Control1=IDC_TREEDATA,SysTreeView32,1342242979
Control2=IDC_TREECTRLS,SysTreeView32,1342242851

[DLG:IDD_RESULTS]
Type=1
Class=CDlgResults
ControlCount=6
Control1=IDC_STATIC,button,1342177287
Control2=IDC_BUT_UP,button,1342242816
Control3=IDC_BUT_DOWN,button,1342242816
Control4=IDC_STATIC,static,1342308354
Control5=IDS_GAIN,edit,1342253058
Control6=IDC_RES_NUM,edit,1342253058

[DLG:IDD_ANALYSE]
Type=1
Class=CPageAnalyse
ControlCount=15
Control1=IDC_STATIC,button,1342177287
Control2=IDC_BUT_PROCESS,button,1342242816
Control3=IDE_IN,edit,1350631554
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_OUTPUT,static,1342308354
Control7=IDC_STATIC,static,1342308352
Control8=IDC_GAIN,static,1342308354
Control9=IDC_STATIC,button,1342177287
Control10=IDE_TT,edit,1350631554
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDS_GNY,static,1342308354
Control15=IDC_STATIC,static,1342308352

[DLG:IDD_BASE]
Type=1
Class=CPageBase
ControlCount=0

[DLG:IDD_DIFF]
Type=1
Class=CPageDiff
ControlCount=8
Control1=IDC_BUT_DIFF1,button,1342242816
Control2=IDC_STATIC,button,1342177287
Control3=IDC_BUT_DIFF2,button,1342242816
Control4=IDC_RAD_D1,button,1342177289
Control5=IDC_RAD_D2,button,1342177289
Control6=IDC_STATIC,button,1342177287
Control7=IDC_BUT_DIFF3,button,1342242816
Control8=IDC_RAD_D3,button,1342177289

[DLG:IDD_FLAGS]
Type=1
Class=CPageFlags
ControlCount=27
Control1=IDC_SPIN,msctls_updown32,1342177312
Control2=IDC_STATIC,button,1342177287
Control3=IDE_BC,edit,1350631554
Control4=IDC_STATIC,button,1342177287
Control5=IDE_RC,edit,1350639618
Control6=IDC_STATIC,static,1342177283
Control7=IDC_STATIC,static,1342177283
Control8=IDC_STATIC,static,1342177283
Control9=IDE_ML,edit,1350631554
Control10=IDE_MU,edit,1350631554
Control11=IDE_MC,edit,1350631554
Control12=IDC_STATIC,button,1342177287
Control13=IDC_STATIC,static,1342177283
Control14=IDC_STATIC,static,1342177283
Control15=IDC_STATIC,static,1342177283
Control16=IDC_STATIC,button,1342177287
Control17=IDC_BUT_UPDATE,button,1342242816
Control18=IDC_SLIDER,msctls_trackbar32,1342242816
Control19=IDC_STATIC,static,1342177283
Control20=IDR_FINE,button,1342177289
Control21=IDR_COARSE,button,1342177289
Control22=IDC_STATIC,static,1342177283
Control23=IDC_STATIC,static,1342177283
Control24=IDC_STATIC,static,1342308352
Control25=IDS_RESOLUTION,edit,1342253058
Control26=IDC_STATIC,static,1342308352
Control27=IDC_STATIC,static,1342308352

[DLG:IDD_IMPORT]
Type=1
Class=CPageImport
ControlCount=8
Control1=IDE_COL_DATE,edit,1350631554
Control2=IDC_STATIC,static,1342308352
Control3=IDE_COL_VAL,edit,1350631554
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,button,1342177287
Control6=IDB_MOVE_UP,button,1342242816
Control7=IDC_STATIC,button,1342177287
Control8=IDB_DELETE,button,1342242816

[DLG:IDD_INFO]
Type=1
Class=CPageInfo
ControlCount=14
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308354
Control5=IDC_STATIC,static,1342308354
Control6=IDC_STATIC,button,1342177287
Control7=IDE_CURRENCY,edit,1350631552
Control8=IDE_COMMENT,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDE_MAXV,edit,1342253058
Control12=IDE_MINV,edit,1342253058
Control13=IDE_MAXA,edit,1342253058
Control14=IDE_MINA,edit,1342253058

[DLG:IDD_MEDIAN]
Type=1
Class=CPageMedian
ControlCount=12
Control1=65535,button,1342177287
Control2=IDE_ADD_DAY,edit,1350631554
Control3=IDE_ADD_MONTH,edit,1350631554
Control4=IDE_ADD_YEAR,edit,1350631554
Control5=65535,static,1342308354
Control6=65535,static,1342308354
Control7=65535,static,1342308354
Control8=IDE_ADD_VAL,edit,1350631554
Control9=65535,static,1342308352
Control10=65535,static,1342308352
Control11=IDC_BUT_NEW_APPLY,button,1342242816
Control12=IDC_BUT_UNDO,button,1342242816

[DLG:IDD_RANGE]
Type=1
Class=CPageRange
ControlCount=20
Control1=IDC_START_DAY,edit,1350631554
Control2=IDC_START_MONTH,edit,1350631554
Control3=IDC_START_YEAR,edit,1350631554
Control4=IDC_END_MONTH,edit,1350631554
Control5=IDC_END_DAY,edit,1350631554
Control6=IDC_END_YEAR,edit,1350631554
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308354
Control10=IDC_STATIC,static,1342308354
Control11=IDC_STATIC,static,1342308354
Control12=IDC_STATIC,button,1342177287
Control13=IDC_BASE_ZERO,button,1342242819
Control14=IDC_BUT_APPLY,button,1342242816
Control15=IDC_BUT_LIMITS,button,1342242816
Control16=IDC_ZOOM,msctls_updown32,1342177376
Control17=IDC_PAN,msctls_updown32,1342177376
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,button,1342177287

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_EDIT_CUT
Command2=ID_EDIT_COPY
Command3=ID_EDIT_PASTE
Command4=ID_FILE_PRINT
Command5=ID_APP_ABOUT
CommandCount=5

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_IMPORT
Command6=ID_FILE_MRU_FILE1
Command7=ID_APP_EXIT
Command8=ID_APP_ABOUT
CommandCount=8

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_EDIT_PASTE
Command3=ID_EDIT_UNDO
Command4=ID_EDIT_CUT
Command5=ID_NEXT_PANE
Command6=ID_PREV_PANE
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_CUT
Command10=ID_EDIT_UNDO
CommandCount=10

[DLG:IDD_RANGE (English (U.K.))]
Type=1
Class=?
ControlCount=20
Control1=IDC_START_DAY,edit,1350631554
Control2=IDC_START_MONTH,edit,1350631554
Control3=IDC_START_YEAR,edit,1350631554
Control4=IDC_END_MONTH,edit,1350631554
Control5=IDC_END_DAY,edit,1350631554
Control6=IDC_END_YEAR,edit,1350631554
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308354
Control10=IDC_STATIC,static,1342308354
Control11=IDC_STATIC,static,1342308354
Control12=IDC_STATIC,button,1342177287
Control13=IDC_BASE_ZERO,button,1342242819
Control14=IDC_BUT_APPLY,button,1342242816
Control15=IDC_BUT_LIMITS,button,1342242816
Control16=IDC_ZOOM,msctls_updown32,1342177376
Control17=IDC_PAN,msctls_updown32,1342177376
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,button,1342177287

[DLG:IDD_BASE (English (U.K.))]
Type=1
Class=?
ControlCount=0

[DLG:IDD_DIFF (English (U.K.))]
Type=1
Class=?
ControlCount=8
Control1=IDC_BUT_DIFF1,button,1342242816
Control2=IDC_STATIC,button,1342177287
Control3=IDC_BUT_DIFF2,button,1342242816
Control4=IDC_RAD_D1,button,1342177289
Control5=IDC_RAD_D2,button,1342177289
Control6=IDC_STATIC,button,1342177287
Control7=IDC_BUT_DIFF3,button,1342242816
Control8=IDC_RAD_D3,button,1342177289

[DLG:IDD_ANALYSE (English (U.K.))]
Type=1
Class=?
ControlCount=15
Control1=IDC_STATIC,button,1342177287
Control2=IDC_BUT_PROCESS,button,1342242816
Control3=IDE_IN,edit,1350631554
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_OUTPUT,static,1342308354
Control7=IDC_STATIC,static,1342308352
Control8=IDC_GAIN,static,1342308354
Control9=IDC_STATIC,button,1342177287
Control10=IDE_TT,edit,1350631554
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDS_GNY,static,1342308354
Control15=IDC_STATIC,static,1342308352

[DLG:IDD_FLAGS (English (U.K.))]
Type=1
Class=?
ControlCount=27
Control1=IDC_SPIN,msctls_updown32,1342177312
Control2=IDC_STATIC,button,1342177287
Control3=IDE_BC,edit,1350631554
Control4=IDC_STATIC,button,1342177287
Control5=IDE_RC,edit,1350639618
Control6=IDC_STATIC,static,1342177283
Control7=IDC_STATIC,static,1342177283
Control8=IDC_STATIC,static,1342177283
Control9=IDE_ML,edit,1350631554
Control10=IDE_MU,edit,1350631554
Control11=IDE_MC,edit,1350631554
Control12=IDC_STATIC,button,1342177287
Control13=IDC_STATIC,static,1342177283
Control14=IDC_STATIC,static,1342177283
Control15=IDC_STATIC,static,1342177283
Control16=IDC_STATIC,button,1342177287
Control17=IDC_BUT_UPDATE,button,1342242816
Control18=IDC_SLIDER,msctls_trackbar32,1342242816
Control19=IDC_STATIC,static,1342177283
Control20=IDR_FINE,button,1342177289
Control21=IDR_COARSE,button,1342177289
Control22=IDC_STATIC,static,1342177283
Control23=IDC_STATIC,static,1342177283
Control24=IDC_STATIC,static,1342308352
Control25=IDS_RESOLUTION,edit,1342253058
Control26=IDC_STATIC,static,1342308352
Control27=IDC_STATIC,static,1342308352

[DLG:IDD_MEDIAN (English (U.K.))]
Type=1
Class=?
ControlCount=12
Control1=65535,button,1342177287
Control2=IDE_ADD_DAY,edit,1350631554
Control3=IDE_ADD_MONTH,edit,1350631554
Control4=IDE_ADD_YEAR,edit,1350631554
Control5=65535,static,1342308354
Control6=65535,static,1342308354
Control7=65535,static,1342308354
Control8=IDE_ADD_VAL,edit,1350631554
Control9=65535,static,1342308352
Control10=65535,static,1342308352
Control11=IDC_BUT_NEW_APPLY,button,1342242816
Control12=IDC_BUT_UNDO,button,1342242816

[DLG:IDD_IMPORT (English (U.K.))]
Type=1
Class=?
ControlCount=8
Control1=IDE_COL_DATE,edit,1350631554
Control2=IDC_STATIC,static,1342308352
Control3=IDE_COL_VAL,edit,1350631554
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,button,1342177287
Control6=IDB_MOVE_UP,button,1342242816
Control7=IDC_STATIC,button,1342177287
Control8=IDB_DELETE,button,1342242816

[DLG:IDD_INFO (English (U.K.))]
Type=1
Class=?
ControlCount=14
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308354
Control5=IDC_STATIC,static,1342308354
Control6=IDC_STATIC,button,1342177287
Control7=IDE_CURRENCY,edit,1350631552
Control8=IDE_COMMENT,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDE_MAXV,edit,1342253058
Control12=IDE_MINV,edit,1342253058
Control13=IDE_MAXA,edit,1342253058
Control14=IDE_MINA,edit,1342253058

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_EDIT_CUT
Command2=ID_EDIT_COPY
Command3=ID_EDIT_PASTE
Command4=ID_FILE_PRINT
Command5=ID_APP_ABOUT
CommandCount=5

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_IMPORT
Command6=ID_FILE_MRU_FILE1
Command7=ID_APP_EXIT
Command8=ID_APP_ABOUT
CommandCount=8

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_EDIT_PASTE
Command3=ID_EDIT_UNDO
Command4=ID_EDIT_CUT
Command5=ID_NEXT_PANE
Command6=ID_PREV_PANE
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_CUT
Command10=ID_EDIT_UNDO
CommandCount=10

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=14
Control1=IDC_STATIC,static,1342308480
Control2=IDC_STATIC,static,1342308352
Control3=IDOK,button,1342373889
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,button,1342177287
Control8=IDC_STATIC,button,1342177287
Control9=IDC_STATIC,static,1342181390
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,button,1342177287
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352

[DLG:IDD_CALC (English (U.S.))]
Type=1
Class=?
ControlCount=2
Control1=IDC_PROG,msctls_progress32,1350565888
Control2=IDC_BUT_END,button,1342242816

[DLG:IDD_LIST (English (U.S.))]
Type=1
Class=?
ControlCount=2
Control1=IDC_TREEDATA,SysTreeView32,1342242979
Control2=IDC_TREECTRLS,SysTreeView32,1342242851

[DLG:IDD_RESULTS (English (U.S.))]
Type=1
Class=?
ControlCount=6
Control1=IDC_STATIC,button,1342177287
Control2=IDC_BUT_UP,button,1342242816
Control3=IDC_BUT_DOWN,button,1342242816
Control4=IDC_STATIC,static,1342308354
Control5=IDS_GAIN,edit,1342253058
Control6=IDC_RES_NUM,edit,1342253058

