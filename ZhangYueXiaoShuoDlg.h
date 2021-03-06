
// ZhangYueXiaoShuoDlg.h: 头文件
//

#pragma once


// CZhangYueXiaoShuoDlg 对话框
class CZhangYueXiaoShuoDlg : public CDialogEx
{
// 构造
public:
	CZhangYueXiaoShuoDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ZHANGYUEXIAOSHUO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CString ChapterName(CString YuanShiTXT);
	CString WenBenTiQuPaiXv(CString YuanShiTXT);
	CString WebGet(CString Url);
	void SaveFile(CString Content);
	CString DeleteBackslash(CString strin);
	int top[10000] = {0};	//top数组
	int left[10000] = {0};	//left数组
	CStringArray CAtxt;	//文本数组
	CMFCEditBrowseCtrl m_EditBrowse;
};
