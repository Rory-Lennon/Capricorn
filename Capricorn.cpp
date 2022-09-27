#include "stdafx.h"
#include "Capricorn.h"
#include "MainFrm.h"
#include "SJParamSet.h"
#include "SJFileProject.h"
#include "SJFileCSV.h"

BEGIN_MESSAGE_MAP(CCapricornApp, CWinApp)
	//{{AFX_MSG_MAP(CCapricornApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_REFRESH_DATA, OnRefreshData)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_IMPORT, OnImport)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CCapricornApp::CCapricornApp()
{
	m_datesincol = 1;
	m_valsincol = 2;
}

CCapricornApp theApp;

BOOL CCapricornApp::InitInstance()
{
	Enable3dControls();			

	SetRegistryKey(_T("Cyclops Markets Monitor"));
	LoadStdProfileSettings(8);

	CMainFrame* pFrame = new CMainFrame;
	m_pMainWnd = pFrame;

	pFrame->LoadFrame(IDR_MAINFRAME, WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL, NULL);

	m_app_icon = LoadIcon(IDI_CAPRICORN);
	m_pMainWnd->SetIcon(m_app_icon, TRUE);
	m_pMainWnd->SetIcon(m_app_icon, FALSE);

	m_pMainWnd->SetWindowText("Cyclops Markets Monitor -  Professional Edition ");
	pFrame->ShowWindow(SW_SHOW);

	pFrame->UpdateWindow();

	m_last_file = GetProfileString("user", "last_file", "..\\Project Files\\DOW.xml");
	m_datesincol = GetProfileInt("user", "datesincol", 1);
	m_valsincol = GetProfileInt("user", "valsincol", 2);

	open_file(m_last_file);

	return TRUE;
}

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA
	//{{AFX_VIRTUAL(CAboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CCapricornApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

void CCapricornApp::OnRefreshData() 
{
	((CMainFrame*)AfxGetMainWnd())->m_view_one.Invalidate();
}

void CCapricornApp::OnFileOpen() 
{
	BOOL b_save_or_open = TRUE;
	CString str_default_extension = "";
	CString str_file_title = "";
	CString str_filter = _T("Cyclops Project Files (*.xml)|*.xml||");

	CFileDialog dlg_file(b_save_or_open, 
							   str_default_extension, 
							   str_file_title,
							   OFN_HIDEREADONLY,
							   str_filter,
							   NULL);

	dlg_file.m_ofn.lpstrInitialDir = _T("..\\Project Files");
	int do_it = dlg_file.DoModal();
	if(do_it == 1) open_file(dlg_file.GetPathName());	
}

BOOL CCapricornApp::open_file(CString file_path)
{
	if(file_path == "") return FALSE;
	OnFileNew();

	m_last_file = file_path;
	AddToRecentFileList(file_path);
	
	SJFileProject project_file;
	if(!project_file.Open(file_path, false)) return FALSE;
	project_file.read_file();
	project_file.Close();

	AfxGetMainWnd()->SendMessageToDescendants(MSG_PARAMS, TO_DIALOG, 0, TRUE);
	AfxGetMainWnd()->SendMessageToDescendants(MSG_PARAMS, TO_CURRENT, 0, TRUE);
	AfxGetMainWnd()->SendMessageToDescendants(MSG_PARAMS, UPDATE_LIST, 0, TRUE);
	AfxGetMainWnd()->SendMessageToDescendants(MSG_PARAMS, REQUEST_RESULT, 0, TRUE);

	return TRUE;
}

void CCapricornApp::OnImport() 
{
	BOOL b_save_or_open = TRUE;
	CString str_default_extension = "";
	CString str_file_title = "";
	CString str_filter = _T("All Files (*.*)|*.*||");

	CFileDialog dlg_file(b_save_or_open, 
							   str_default_extension, 
							   str_file_title,
							   OFN_HIDEREADONLY,
							   str_filter,
							   NULL);

	dlg_file.m_ofn.lpstrTitle = "Import";
	dlg_file.m_ofn.lpstrInitialDir = _T("..\\Data Files");
	int do_it = dlg_file.DoModal();
	if(do_it == 1) import_file(dlg_file.GetPathName());	
}

BOOL CCapricornApp::import_file(CString file_path)
{
	if(file_path == "") return FALSE;

	CString extension = file_path.Mid(file_path.GetLength() - 4, 4);
	extension.MakeUpper();

	SJDataSet* p_set = NULL;
 
	AfxGetMainWnd()->SendMessageToDescendants(MSG_PARAMS, FROM_DIALOG, 0, TRUE);

	SJFileCSV file_csv;
	file_csv.m_datesincol = m_datesincol;
	file_csv.m_valsincol = m_valsincol;
	file_csv.Open(file_path, false);
	p_set = file_csv.read_file();
	file_csv.Close();

	if(p_set) m_data_base.change_current(p_set);
	AfxGetMainWnd()->SendMessageToDescendants(MSG_PARAMS, TO_CURRENT, 0, TRUE);
	AfxGetMainWnd()->SendMessageToDescendants(MSG_PARAMS, UPDATE_LIST, 0, TRUE);
	return TRUE;
}

void CCapricornApp::OnFileSaveAs() 
{
	BOOL b_save_or_open = FALSE;
	CString str_default_extension = "cps";
	CString str_file_title = "Project-1.xml";
	CString str_filter = _T("Cyclops Project Files (*.xml)|*.xml||");

	CFileDialog dlg_file(b_save_or_open, 
							   str_default_extension, 
							   str_file_title,
							   OFN_HIDEREADONLY,
							   str_filter,
							   NULL);

	dlg_file.m_ofn.lpstrInitialDir = _T("..\\Project Files");
	int do_it = dlg_file.DoModal();

	if(do_it == 1)
	{
		m_last_file = dlg_file.GetPathName();
		if(!save_file(dlg_file.GetPathName()))
		{
			MessageBox(NULL, "File Not Saved.", "Error", MB_OK | MB_ICONERROR);
		}
	}	
}

void CCapricornApp::OnFileSave() 
{
	if(!save_file(m_last_file)) OnFileSaveAs(); 
}

BOOL CCapricornApp::save_file(CString file_path)
{
	if(file_path == "") return FALSE;

	AfxGetMainWnd()->SendMessageToDescendants(MSG_PARAMS, FROM_DIALOG, 0, TRUE);

	ofstream open_file(file_path);
	if(!open_file.is_open()) return FALSE;
	m_data_base.write_data(&open_file);
	open_file.close();

	m_last_file = file_path;
	AddToRecentFileList(file_path);

	return TRUE;
}

int CCapricornApp::ExitInstance() 
{
	WriteProfileString("user", "last_file", m_last_file);
	WriteProfileInt("user", "valsincol", m_valsincol);
	WriteProfileInt("user", "datesincol", m_datesincol);
	return CWinApp::ExitInstance();
}

CDocument* CCapricornApp::OpenDocumentFile(LPCTSTR lpszFileName) 
{
	open_file(lpszFileName);
//	return CWinApp::OpenDocumentFile(lpszFileName);
	return (CDocument*)TRUE; 
}

void CCapricornApp::OnFileNew() 
{
	m_last_file = "";
	AfxGetMainWnd()->SendMessageToDescendants(MSG_PARAMS, NEW_FILE);
	m_data_base.new_file();
	AfxGetMainWnd()->SendMessageToDescendants(MSG_PARAMS, UPDATE_LIST);
}

