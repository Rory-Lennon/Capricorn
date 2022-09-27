#include "stdafx.h"
#include "capricorn.h"
#include "DlgList.h"
#include "MainFrm.h"

CDlgList::CDlgList() 
{
	//{{AFX_DATA_INIT(CDlgList)
	//}}AFX_DATA_INIT
	mp_data_base = &(((CCapricornApp*)AfxGetApp())->m_data_base);
	m_change_current = TRUE;
}

void CDlgList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgList)
	DDX_Control(pDX, IDC_TREEDATA, m_tree_sets);
	DDX_Control(pDX, IDC_TREECTRLS, m_tree_ctrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgList, CDialog)
	//{{AFX_MSG_MAP(CDlgList)
	ON_WM_SIZE()
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREECTRLS, OnSelchangedTreectrls)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREEDATA, OnSelchangedTreedata)
	ON_MESSAGE(MSG_PARAMS, on_params)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CDlgList::build_controls()
{
	m_controls_root = insert_data(m_tree_ctrl, NULL, "Controls",				  -1, 4, 4, NOT_BOLD);
	HTREEITEM data_root = insert_data(m_tree_ctrl, m_controls_root, "Data",   -1,10,10, NOT_BOLD);

							insert_data(m_tree_ctrl, data_root, "Import",				0, 3, 6, NOT_BOLD);
							insert_data(m_tree_ctrl, data_root, "Time Range",			1, 3, 6, NOT_BOLD);
	HTREEITEM hinfo = insert_data(m_tree_ctrl, data_root, "Info",					2, 3, 6, NOT_BOLD);
							insert_data(m_tree_ctrl, data_root, "Append",				3, 3, 6, NOT_BOLD);


	HTREEITEM analysis_root = insert_data(m_tree_ctrl, m_controls_root, "Analysis", -1, 9, 9, NOT_BOLD);

//	insert_data(m_tree_ctrl, analysis_root, "Differential",							4, 3, 6, NOT_BOLD);
	insert_data(m_tree_ctrl, analysis_root, "Parameters",								4, 3, 6, NOT_BOLD);
	insert_data(m_tree_ctrl, analysis_root, "Process",									5, 3, 6, NOT_BOLD);

	m_tree_ctrl.Expand(m_controls_root, TVE_EXPAND);
	m_tree_ctrl.Expand(data_root, TVE_EXPAND);
	m_tree_ctrl.Expand(analysis_root, TVE_EXPAND);	

	m_sets_root = insert_data(m_tree_sets, NULL, "Datasets",							-1, 4, 4, NOT_BOLD);
	m_primary_root = insert_data(m_tree_sets, m_sets_root, "Primary",				-1, 0, 0, NOT_BOLD);
	m_secondary_root = insert_data(m_tree_sets, m_sets_root, "Secondary",		-1, 1, 1, NOT_BOLD);

	m_tree_ctrl.SelectItem(hinfo);
}

LONG CDlgList::on_params(WPARAM wParam, LPARAM lParam)
{
	if(wParam == UPDATE_LIST)
	{
		m_change_current = FALSE;

		delete_below(m_tree_sets, m_primary_root);
		delete_below(m_tree_sets, m_secondary_root);

		int i = 0;
		int j = 0;
		POS pos = mp_data_base->ml_datasets.get_head_pos();
		while(pos) 
		{
			SJDataSet* p_set = mp_data_base->ml_datasets.get_next(pos);
			if(i == 0) insert_data(m_tree_sets, m_primary_root, p_set->m_name, (int)p_set, 2, 5, NOT_BOLD);
			else insert_data(m_tree_sets, m_secondary_root, p_set->m_name, (int)p_set, 2, 5, NOT_BOLD);
			i++;
		}
		m_tree_sets.Expand(m_sets_root, TVE_EXPAND);
		m_tree_sets.Expand(m_primary_root, TVE_EXPAND);
		m_tree_sets.Expand(m_secondary_root, TVE_EXPAND);
		
		m_change_current = TRUE;
		select_current();
	}
	return TRUE;
}

BOOL CDlgList::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_image_list.Create(IDB_TREE, 16, 10, RGB(255, 255, 255));
	m_tree_ctrl.SetImageList(&m_image_list, TVSIL_NORMAL);
	m_tree_sets.SetImageList(&m_image_list, TVSIL_NORMAL);
	build_controls();

	return TRUE;  
}

void CDlgList::select_current()
{
	SJDataSet* p_current_dataset = mp_data_base->mp_current_dataset;
	if(p_current_dataset == NULL) return;
	select_dataset(p_current_dataset);
}

void CDlgList::select_dataset(SJDataSet* p_set)
{
	SJDataSet* p_loop_set;

	HTREEITEM level2 = m_tree_sets.GetNextItem(m_sets_root, TVGN_CHILD);
	while(level2)
	{
		HTREEITEM level3 = m_tree_sets.GetNextItem(level2, TVGN_CHILD);
		while(level3)
		{
			p_loop_set = (SJDataSet*)m_tree_sets.GetItemData(level3);
			if(p_loop_set == p_set) m_tree_sets.SelectItem(level3);

			level3 = m_tree_sets.GetNextItem(level3, TVGN_NEXT);
		}
		level2 = m_tree_sets.GetNextItem(level2, TVGN_NEXT);
	}	
}

void CDlgList::delete_below(CTreeCtrl &tree, HTREEITEM item)
{
	HTREEITEM htiChild = tree.GetNextItem(item, TVGN_CHILD);
	while(htiChild)
	{
		tree.DeleteItem(htiChild);
		htiChild = tree.GetNextItem(item, TVGN_CHILD);
//		str = tree.GetItemText(htiChild);
//		TRACE("htiChild %i item %i %s\n\n", htiChild, item, str);
	}
}

HTREEITEM CDlgList::insert_data(CTreeCtrl &tree, HTREEITEM parent, CString name, int data, int image_on, int image_off, int bold)
{
	HTREEITEM new_parent;

	new_parent = tree.InsertItem(
				TVIF_IMAGE | TVIF_PARAM | TVIF_SELECTEDIMAGE | TVIF_STATE | TVIF_TEXT,
				name,
				image_on,
				image_off,
				bold,
				BOLD,
				data,
				parent,
				TVI_LAST);

	return new_parent;
}

void CDlgList::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	int SETS_HEIGHT = cy - LIST_HEIGHT - MOVE_HEIGHT;

	if(!m_tree_sets) return;
	if(!m_tree_ctrl) return;
	m_tree_sets.MoveWindow(5, 5 + MOVE_HEIGHT, DOCK_WIDTH - 10, SETS_HEIGHT - 5);
	m_tree_ctrl.MoveWindow(5, SETS_HEIGHT + MOVE_HEIGHT + 5, DOCK_WIDTH - 10, LIST_HEIGHT - 5);
}

void CDlgList::OnSelchangedTreedata(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(!m_change_current) return;

	HTREEITEM p_item = m_tree_sets.GetSelectedItem();
	int data = m_tree_sets.GetItemData(p_item);
	
	if(data > -1) // CHANGE CURRENT
	{	
		AfxGetMainWnd()->SendMessageToDescendants(MSG_PARAMS, FROM_DIALOG);
		mp_data_base->change_current((SJDataSet*)data);
		AfxGetMainWnd()->SendMessageToDescendants(MSG_PARAMS, TO_CURRENT);
		((CMainFrame*)AfxGetMainWnd())->update_views();
	}
	*pResult = 0;
}

void CDlgList::OnSelchangedTreectrls(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HTREEITEM p_ctrls_item = m_tree_ctrl.GetSelectedItem();
	int ctrls_data = m_tree_ctrl.GetItemData(p_ctrls_item);

	HTREEITEM p_sets_item = m_tree_sets.GetSelectedItem();
	int sets_data = 0;
	if(p_sets_item) sets_data = m_tree_sets.GetItemData(p_sets_item);

	if(ctrls_data > -1)
	{
		((CMainFrame*)AfxGetMainWnd())->m_sheet.SetActivePage(ctrls_data);
	}
	*pResult = 0;
}
