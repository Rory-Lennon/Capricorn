#pragma once

class CDlgList : public CDialog
{
public:

	CDlgList();   // standard constructor
	void build_controls();	
	HTREEITEM insert_data(CTreeCtrl &tree, HTREEITEM parent, CString name, int data, int image_on, int image_off, int bold);	
	void select_dataset(SJDataSet* p_set);
	void select_current();
	void delete_below(CTreeCtrl &tree, HTREEITEM item);	

	HTREEITEM m_primary_root;
	HTREEITEM m_secondary_root;

	int m_change_current;

	SJDataBase* mp_data_base;
	CImageList m_image_list;

	HTREEITEM m_controls_root;
	HTREEITEM m_sets_root;

	//{{AFX_DATA(CDlgList)
	enum { IDD = IDD_LIST };
	CTreeCtrl m_tree_sets;
	CTreeCtrl m_tree_ctrl;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CDlgList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CDlgList)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelchangedTreectrls(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangedTreedata(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg LONG on_params(WPARAM	wParam, LPARAM	lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
