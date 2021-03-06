
// ZhangYueXiaoShuoDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "ZhangYueXiaoShuo.h"
#include "ZhangYueXiaoShuoDlg.h"
#include "afxdialogex.h"
#include "afxinet.h"
#include "omp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CZhangYueXiaoShuoDlg 对话框



CZhangYueXiaoShuoDlg::CZhangYueXiaoShuoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ZHANGYUEXIAOSHUO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CZhangYueXiaoShuoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCEDITBROWSE1, m_EditBrowse);
}

BEGIN_MESSAGE_MAP(CZhangYueXiaoShuoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CZhangYueXiaoShuoDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CZhangYueXiaoShuoDlg 消息处理程序

BOOL CZhangYueXiaoShuoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_EditBrowse.EnableFileBrowseButton(_T(""), _T("Text Files(*.txt)|*.txt|"));
	GetDlgItem(IDC_EUrl)->SetWindowText(_T("http://m.zhangyue.com/nextchapter/10882381/*****?p2=104155&width=924&nextRowId=1"));
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CZhangYueXiaoShuoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CZhangYueXiaoShuoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CZhangYueXiaoShuoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CZhangYueXiaoShuoDlg::OnBnClickedButton1()
{
	CString Reponse;	//网页返回内容
	CString TitleName, Ttxt;	//章节标题、内容
	CString url;
	CString ChapterLstr, ChapterRstr, Chapterstr;
	int ChapterL, ChapterR, Chapter;
	GetDlgItem(IDC_EUrl)->GetWindowText(url);
	GetDlgItem(IDC_EChapterL)->GetWindowText(ChapterLstr);
	GetDlgItem(IDC_EChapterR)->GetWindowText(ChapterRstr);
	ChapterL = _ttoi(ChapterLstr);
	ChapterR = _ttoi(ChapterRstr);

	Chapter = ChapterL;
	do
	{
		Chapterstr.Format(_T("%d"), Chapter);
		CString urlTmp = url;
		urlTmp.Replace(_T("*****"), Chapterstr);
		Reponse = WebGet(urlTmp);
		TitleName = ChapterName(Reponse);
		Ttxt = WenBenTiQuPaiXv(Reponse);
		if (Ttxt == _T(""))
		{
			MessageBox(_T("获取内容为空"));
			return;
		}
		CString Content;	//写入txt文件内容
		Content = TitleName + _T("\r\n") + Ttxt + _T("\r\n\r\n");
		SaveFile(Content);
		Chapter++;
	} while (Chapter <= ChapterR);

}

//获取章节名
CString CZhangYueXiaoShuoDlg::ChapterName(CString YuanShiTXT)
{
	int nameL;
	int nameR;
	CString name;
	nameL = YuanShiTXT.Find(_T("\"chapterName\":\""));
	nameR = YuanShiTXT.Find(_T("\",\"pageButton\""));
	name = YuanShiTXT.Mid(nameL + 15, nameR - nameL - 15);
	return name;
}


//提取正文div内的left、top、文字，并进行排序
CString CZhangYueXiaoShuoDlg::WenBenTiQuPaiXv(CString YuanShiTXT)
{
	int leftL;	//left左侧Flag
	int leftR;	//left右侧Flag、top左侧Flag
	int txtL;	//文本左侧Flag、top右侧Flag
	int txtR;	//文本右侧Flag
	int subscript = 0;	//数组下标
	CAtxt.SetSize(0, 1);	//CStringArray初始化

	int i, j, temp, temp2;
	CString temp3;

	do
	{
		leftL = YuanShiTXT.Find(_T("left:"));
		leftR = YuanShiTXT.Find(_T("px; top:"));
		txtL = YuanShiTXT.Find(_T("px;\\\">"));
		txtR = YuanShiTXT.Find(_T("<\\/span>"));
		if (leftL != -1)
		{
			left[subscript] = _ttoi(YuanShiTXT.Mid(leftL + 5, leftR - leftL - 5));
			top[subscript] = _ttoi(YuanShiTXT.Mid(leftR + 8, txtL - leftR - 8));
			CAtxt.Add(YuanShiTXT.Mid(txtL + 6, txtR - txtL - 6));
			YuanShiTXT = YuanShiTXT.Mid(txtR + 8, YuanShiTXT.GetLength() - txtR - 8);
			subscript++;
		}
	} while (leftL != -1);


	//对top排序

	for (j = 0; j < subscript - 1; j++) {
		//外循环一次，就排好一个数，并放在后面，
		//所以比较前面n-j-1个元素即可
		for (i = 0; i < subscript - j - 1; i++) {
			if (top[i] > top[i + 1]) {
				temp = top[i];			temp2 = left[i];		temp3 = CAtxt.GetAt(i);
				top[i] = top[i + 1];	left[i] = left[i + 1];	CAtxt.SetAt(i, CAtxt.GetAt(i + 1));
				top[i + 1] = temp;		left[i + 1] = temp2;	CAtxt.SetAt(i + 1, temp3);
			}
		}
	}


	//对left排序
	int n = 1;	//当前行（同top值）的字数
	int m = 0;	//已排序的个数
	for (int k = m; k < subscript; k++)
	{
		if (top[k] == top[k + 1])	//判断是否在同一行
		{
			n++;	//计算同一行的字数
		}
		else
		{	//对同一行的n个字，根据left进行排序
			for (j = 0; j < n - 1; j++) {
				for (i = 0; i < n - j - 1; i++) {
					if (left[m + i] > left[m + i + 1]) {
						temp = left[m + i];			temp3 = CAtxt.GetAt(m + i);
						left[m + i] = left[m + i + 1];	CAtxt.SetAt(m + i, CAtxt.GetAt(m + i + 1));
						left[m + i + 1] = temp;		CAtxt.SetAt(m + i + 1, temp3);
					}
				}
			}
			m += n;
			n = 1;
		}
	}

	//输出文本
	CString txt(_T(""));
	CString Debugtxt(_T(""));
	for (i = 0; i < CAtxt.GetCount(); i++)
	{
		if (CAtxt.GetAt(i) == _T("\\n"))
		{
			if (top[i - 1] == top[i])
			{
				txt = txt.Left(txt.GetLength() - 2);	//Unicoede字符集下减1，多字符集减2
				txt += _T("\r\n\t");
				txt += CAtxt.GetAt(i - 1);
			}
			else
			{
				txt += _T("\r\n\t");
			}
		}
		else
		{
			if (i == 0 && CAtxt.GetAt(i) == _T(" "))
			{
				txt += _T("\t");
			}
			else
			{
				txt += CAtxt.GetAt(i);
			}
		}
		CString strleft, strtop;
		strleft.Format(_T("%d"), left[i]);
		strtop.Format(_T("%d"), top[i]);
		Debugtxt += strleft + _T("\t") + strtop + _T("\t") + CAtxt.GetAt(i) + _T("\r\n");
	}
	return txt;
	//GetDlgItem(IDC_ES)->SetWindowText(txt);
}


//从网页获取HTML文本
//http://m.zhangyue.com/nextchapter/10882381/1?p2=104155&width=537&nextRowId=1
CString CZhangYueXiaoShuoDlg::WebGet(CString Url)
{
	CString WebResponse;
	CString YuanShiTXT;


	CInternetSession c;
	CHttpFile * p = NULL;
	p = (CHttpFile*)c.OpenURL(Url);   //打开一个URL
	CString str;
	CString info = _T("");
	while (p->ReadString(str))   //读取网页数据 
	{
		info += str;
	}
	c.Close();
	WebResponse = DeleteBackslash(info);
	return WebResponse;
}

void CZhangYueXiaoShuoDlg::SaveFile(CString Content)
{
	CString path;
	GetDlgItem(IDC_MFCEDITBROWSE1)->GetWindowText(path);
	if (path.Right(4) != _T(".txt"))
	{
		path += _T(".txt");
	}
	CFile cfile;
	cfile.Open(path, CFile::modeCreate |
		CFile::modeReadWrite | CFile::modeNoTruncate);
	cfile.SeekToEnd();//先定位到文件尾部
	cfile.Write(Content,Content.GetLength());
	cfile.Close();
}

CString CZhangYueXiaoShuoDlg::DeleteBackslash(CString strin)	//待处理CString型字符串
{
	CString str = strin;	//进行遍历替换的字符串
	while (str.Find(_T("\\u")) >= 0) {
		int iFirst = str.Find(_T("\\u"));	//查询第一个\\位置
		CString firstUnicode = (str.Mid(iFirst, 6));	//从str中取出第一个\\uXXXX
		char s[6];	//存放第一个\\uXXXX的数组
		for (int i = 0; i<firstUnicode.GetLength(); i++)
		{
			s[i] = firstUnicode.GetAt(i);	//将firstUnicode中的字符一个个取出来放进数组s
		}
		wchar_t ws[2];	//存放宽型字符
		sscanf_s(s, "\\u%04hx", &ws[0]);	//将\u加上s中的数字(以四位十六进制形式)存储在ws中
		ws[1] = 0;	//设置结束符
		CString strtmp = str.Mid(0, iFirst) + ws + str.Mid(iFirst + 6, str.GetLength() - iFirst - 6);
		str = strtmp;
	}
	return str;
}
