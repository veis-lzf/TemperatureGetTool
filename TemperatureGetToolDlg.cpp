
// TemperatureGetToolDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "TemperatureGetTool.h"
#include "TemperatureGetToolDlg.h"
#include "afxdialogex.h"
#include "CXmlGet.h"
#include <locale.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx {
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
public:

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


// CTemperatureGetToolDlg 对话框
CTemperatureGetToolDlg::CTemperatureGetToolDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TEMPERATUREGETTOOL_DIALOG, pParent)
{
	m_pbuf = NULL;
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

CTemperatureGetToolDlg::~CTemperatureGetToolDlg()
{
}

void CTemperatureGetToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_list);
	DDX_Control(pDX, IDC_PROGRESS1, m_progress);
}

BEGIN_MESSAGE_MAP(CTemperatureGetToolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_RCLICK, IDC_LIST, &CTemperatureGetToolDlg::OnRclickList)
	ON_COMMAND(ID_32771, &CTemperatureGetToolDlg::OnCopyClick)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST, &CTemperatureGetToolDlg::OnKeydownList)
	ON_COMMAND(ID_32776, &CTemperatureGetToolDlg::OnMenuExit)
	ON_COMMAND(ID_32775, &CTemperatureGetToolDlg::OnMenuSave)
	ON_WM_CLOSE()
	ON_COMMAND(ID_32774, &CTemperatureGetToolDlg::OnMenuOpen)
	ON_COMMAND(ID_32777, &CTemperatureGetToolDlg::OnAboutShow)
	ON_COMMAND(ID_32782, &CTemperatureGetToolDlg::OnMenuSaveAs)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CTemperatureGetToolDlg 消息处理程序

BOOL CTemperatureGetToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);

	if (pSysMenu != nullptr) {
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);

		if (!strAboutMenu.IsEmpty()) {
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);		// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	OnInitListCtrl();
	OnInitProgress();
	m_Accelerator = ::LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_ACCELERATOR1));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

BOOL CTemperatureGetToolDlg::PreTranslateMessage(MSG* pMsg)
{
	if (m_Accelerator) {
		if (::TranslateAccelerator(m_hWnd, m_Accelerator, pMsg)) {
			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CTemperatureGetToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTemperatureGetToolDlg::OnPaint()
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
HCURSOR CTemperatureGetToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTemperatureGetToolDlg::OnFileOpen()
{
	// 文件类型过滤器
	static TCHAR szFilter[] =
		_T("XML Files (*.xml)|*.xml|")
		_T("All Files (*.*)|*.*||");

	// 1. 初始化文件对话框
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		szFilter, NULL, 0, NULL);

	// 2. 打开文件对话框
	CString strFileName;
	int nRet = dlg.DoModal();

	if (nRet == IDOK) {
		strFileName = dlg.GetPathName(); // 获取文件路径+名称
		//TRACE(strFileName);
	}

	else return;

	// 3. 打开文件
	BOOL bRet = ReadFile(strFileName);

	if (FALSE == bRet) {
		//TRACE(_T("读取文件失败！"));
		return;
	}

	m_pThread = AfxBeginThread(&MyControllingFunction, this, THREAD_PRIORITY_NORMAL, 0, 0, NULL);

}

// 打开并读取文件
BOOL CTemperatureGetToolDlg::ReadFile(CString strPath)
{
	// 打开文件
	CFile file;
	BOOL bRet = file.Open(strPath, CFile::modeRead);

	if (FALSE == bRet)
	{
		return bRet;
	}

	// 区分文件类型Unicode、ASNI、UTF-8
	char sType[4];
	file.Read(sType, 4);

	switch (MAKEWORD(sType[1], sType[0]))
	{
	case 0xEFBB:
		ReadUTF8(file);
		break;

	case  0xFFFE:
		ReadUnicode(file);
		break;

	default:
		ReadANSIFile(file);
		break;
	}

	file.Close();

	return bRet;
}

// ANSI文件读取
void CTemperatureGetToolDlg::ReadANSIFile(CFile& file)
{
	file.Seek(0, CFile::begin);
	UINT nLen = (UINT)file.GetLength();
	char* pBuf = new char[nLen + 1];
	file.Read(pBuf, nLen);
	pBuf[nLen] = '\0';
	m_fileInfo = CString(pBuf);
	delete[]pBuf;
}

// UTF-8文件读取
void CTemperatureGetToolDlg::ReadUTF8(CFile& file)
{
	file.Seek(3, CFile::begin);
	UINT nLen = (UINT)file.GetLength();
	char* pBuf = new char[nLen + 1];
	nLen = file.Read(pBuf, nLen);
	pBuf[nLen] = '\0';

	TCHAR* pwBuf = new TCHAR[nLen];
	MultiByteToWideChar(CP_UTF8, NULL, pBuf, -1, pwBuf, nLen);
	m_fileInfo = CString(pwBuf);
	delete[]pBuf;
	delete[]pwBuf;
}

// Unicode文件读取
void CTemperatureGetToolDlg::ReadUnicode(CFile& file)
{
	file.Seek(2, CFile::begin);
	UINT nLen = (UINT)file.GetLength();
	TCHAR* pBuf = new TCHAR[nLen / 2 + 1];
	int n = file.Read(pBuf, nLen);
	pBuf[n / 2] = _T('\0');
	m_fileInfo = CString(pBuf);
	delete[]pBuf;
}

char* CTemperatureGetToolDlg::CStringtochar(CString str)
{
	char* ptr;
#ifdef _UNICODE
	LONG len;
	len = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
	ptr = new char[len + 1];
	memset(ptr, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, str, -1, ptr, len + 1, NULL, NULL);
#else
	ptr = new char[str.GetAllocLength() + 1];
	sprintf(ptr, _T("%s"), str);
#endif
	return ptr;
}

void CTemperatureGetToolDlg::OnInitListCtrl()
{
	DWORD dwStyle = m_list.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT; // 选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES; // 网格线（只适用与report风格的listctrl）
	m_list.SetExtendedStyle(dwStyle); //设置扩展风格

	m_list.InsertColumn(0, _T("No."), LVCFMT_LEFT, 80);
	m_list.InsertColumn(1, _T("Time"), LVCFMT_LEFT, 300);
	m_list.InsertColumn(2, _T("Data"), LVCFMT_LEFT, 350);
	m_list.InsertColumn(3, _T("Temp/℃"), LVCFMT_LEFT, 100);
	m_list.InsertColumn(4, _T("Humid/RH%"), LVCFMT_LEFT, 120);
}

void CTemperatureGetToolDlg::OnRclickList(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CMenu popMenu;
	popMenu.LoadMenu(IDR_MENU1);
	CPoint posMouse;
	GetCursorPos(&posMouse);
	CMenu* popup = popMenu.GetSubMenu(0);
	popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, posMouse.x, posMouse.y, this);
	popMenu.Detach();
	popMenu.DestroyMenu();

	*pResult = 0;
}

void CTemperatureGetToolDlg::OnCopyClick()
{
	TRY
	{
		// 获取单击所在的行号
		CString clip_buf;
		CString strText;
		POSITION pos = m_list.GetFirstSelectedItemPosition();

		if (pos == NULL) {
			TRACE(_T("No items were selected!\n"));
		}

		else
		{
			while (pos)
			{
				int nItem = m_list.GetNextSelectedItem(pos);
				strText = m_list.GetItemText(nItem, 0);
				int nCount = m_list.GetHeaderCtrl()->GetItemCount();

				for (int i = 1; i < nCount; ++i)
				{
					strText = strText + CString("\t") + m_list.GetItemText(nItem, i);
				}

				clip_buf += strText + CString("\n");
			}
		}

		// 复制剪切板
		if (!clip_buf.IsEmpty()) {
			if (OpenClipboard()) {
				EmptyClipboard();
				TCHAR* pszData;
				HGLOBAL hClipboardData = GlobalAlloc(GMEM_DDESHARE, (clip_buf.GetLength() + 1) * sizeof(TCHAR));

				if (hClipboardData) {
					pszData = (TCHAR*)GlobalLock(hClipboardData);

					if (pszData == NULL) return;

					_tcscpy(pszData, clip_buf);
					GlobalUnlock(hClipboardData);
					SetClipboardData(CF_UNICODETEXT, hClipboardData);//根据相应的数据选择第一个参数，（CF_TEXT）
				}

				CloseClipboard();
			}
		}
	}
		CATCH_ALL(e)
	{
		e->ReportError();
		return;
	}
	END_CATCH_ALL
}

void CTemperatureGetToolDlg::OnKeydownList(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);

	// TODO: 在此添加控件通知处理程序代码
	if ((::GetKeyState(VK_CONTROL) & 0x8000) && (pLVKeyDow->wVKey == 'C' || pLVKeyDow->wVKey == 'c'))
	{
		OnCopyClick();
	}

	*pResult = 0;
}

void CTemperatureGetToolDlg::OnMenuSave()
{
	// 文件类型过滤器
	static TCHAR szFilter[] =
		_T("XML Files (*.xls)|*.xls|")
		_T("All Files (*.*)|*.*||");

	CFileDialog dlg(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		szFilter, NULL, 0, NULL);

	int nRet = dlg.DoModal();
	CString savePath;

	if (nRet == IDOK) {
		savePath = dlg.GetPathName();

		if (savePath.Find(_T(".xls")) < 0) {
			savePath += _T(".xls");
		}
		ReportExcel(savePath);
		m_filePath = savePath;
	}

}

UINT __cdecl CTemperatureGetToolDlg::ExportExcelThread(LPVOID pParam)
{
	CTemperatureGetToolDlg *pThis = (CTemperatureGetToolDlg *)pParam;

	int nItem = pThis->m_list.GetItemCount();
	CStdioFile file(pThis->m_filePath, CFile::shareExclusive | CFile::modeWrite | CFile::modeCreate);

	setlocale(LC_CTYPE, ("chs")); //设置中文输出

	file.WriteString(_T("序号\t时间\t原始数据\t温度/℃\t湿度/RH%\n"));

	CString strText, strBuf;
	int row = 0;
	pThis->m_progress.SetRange32(0, nItem);
	pThis->m_progress.SetPos(0);
	while (row < nItem)
	{
		strText = pThis->m_list.GetItemText(row, 0);
		int nCount = pThis->m_list.GetHeaderCtrl()->GetItemCount();

		for (int i = 1; i < nCount; ++i)
		{
			strText = strText + CString("\t") + pThis->m_list.GetItemText(row, i);
		}

		strBuf = strText + CString("\n");
		file.WriteString(strBuf);
		strBuf.Delete(0, strBuf.GetLength());
		pThis->m_progress.SetPos(row + 1);
		++row;
	}

	file.Close();
	pThis->MessageBox(_T("导出成功"), _T("导出提示"), MB_ICONINFORMATION);

	pThis->OpenFileByPath(pThis->m_filePath);

	return 0;
}

void CTemperatureGetToolDlg::ReportExcel(LPCTSTR strPath)
{
	m_filePath = strPath;
	AfxBeginThread(&ExportExcelThread, this);
}

void CTemperatureGetToolDlg::OnMenuSaveAs()
{
	// 文件类型过滤器
	static TCHAR szFilter[] =
		_T("XML Files (*.xls)|*.xls|")
		_T("All Files (*.*)|*.*||");

	CFileDialog dlg(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		szFilter, NULL, 0, NULL);

	int nRet = dlg.DoModal();
	CString savePath;

	if (nRet == IDOK)
	{
		savePath = dlg.GetPathName();

		if (savePath.Find(_T(".xls")) < 0)
		{
			savePath += _T(".xls");
		}
		if (m_filePath.IsEmpty()) {
			ReportExcel(savePath);
		}
		else {
			CString strTmp;
			strTmp.Format(_T("copy %s %s"), m_filePath.GetString(), savePath.GetString());
			char* pStr = CStringtochar(strTmp);
			system(pStr);
		}
	}
}

void CTemperatureGetToolDlg::OnAboutShow()
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}
// 转换温湿度数据位10进制显示
// type:0表示温度数据，1表示湿度数据
int CTemperatureGetToolDlg::strHexToDec(char* hexl, char* hexh, int type)
{
	int res = 0;
	int lh, ll, hl, hh;

	if (hexl == NULL || hexh == NULL) return -1;

	lh = hexl[2] - '0';
	ll = hexl[3] - '0';
	hh = hexh[2] - '0';
	hl = hexh[3] - '0';

	res = (hh * 16 * 16 * 16 + hl * 16 * 16 + lh * 16 + ll);

	if (res != 0 && !type) res -= 20000;

	return res;
}

void CTemperatureGetToolDlg::calc(char* pbuf, double* out_temp, double* out_humid)
{
	const char* d = " ";
	char* p;
	char buf[8][5] = { {0} };
	int i = 0;
	p = strtok(pbuf, d);

	while (p)
	{
		strcpy_s(buf[i], 5, p);
		p = strtok(NULL, d);
		++i;
	}

	int tl = strHexToDec(buf[0], buf[1], 0);
	int th = strHexToDec(buf[2], buf[3], 0);
	*out_temp = ((th << 16) | tl) / 100.0;

	int hl = strHexToDec(buf[4], buf[5], 1);
	int hh = strHexToDec(buf[6], buf[7], 1);
	*out_humid = ((hh << 16) | hl) / 100.0;
}

UINT __cdecl CTemperatureGetToolDlg::MyControllingFunction(LPVOID pParam)
{
	CTemperatureGetToolDlg* pThis = (CTemperatureGetToolDlg*)pParam;
	char buf[512] = { 0 };
	pThis->m_pbuf = pThis->CStringtochar(pThis->m_fileInfo);
	char* p_addr = pThis->m_pbuf;
	int i = pThis->m_list.GetItemCount();
	double temp = 0.0;
	double humid = 0.0;
	CString no;
	CString strTmp, strHumid;
	int offset = 0;

	while (1) {
		offset = pThis->m_xmlObj.GetXMLBuffer_Str(p_addr, "Abs", buf);
		if (offset == -1)
			break;

		pThis->m_time = buf;
		offset = pThis->m_xmlObj.GetXMLBuffer_Str(p_addr, "Data", buf);
		pThis->m_data = buf;

		calc(buf, &temp, &humid);
		strTmp.Format(_T("%5.2lf"), temp);
		strHumid.Format(_T("%4.2lf"), humid);

		no.Format(_T("%d"), i + 1);
		pThis->m_list.InsertItem(i, no);
		pThis->m_list.SetItemText(i, 1, pThis->m_time);
		pThis->m_list.SetItemText(i, 2, pThis->m_data);
		pThis->m_list.SetItemText(i, 3, strTmp);
		pThis->m_list.SetItemText(i, 4, strHumid);

		p_addr = (char*)offset;
		pThis->m_list.SendMessage(WM_VSCROLL, SB_BOTTOM, NULL);
		++i;
	}
	delete []pThis->m_pbuf;
	pThis->m_pbuf = NULL;

	return 0;
}

void CTemperatureGetToolDlg::OpenFileByPath(LPCTSTR strPath)
{
	SHELLEXECUTEINFO ShExecInfo;
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = NULL;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = NULL;
	ShExecInfo.lpFile = strPath;
	ShExecInfo.lpParameters = NULL;
	ShExecInfo.lpDirectory = NULL;
	ShExecInfo.nShow = SW_MAXIMIZE;
	ShExecInfo.hInstApp = NULL;

	ShellExecuteEx(&ShExecInfo);
}

void CTemperatureGetToolDlg::OnInitProgress()
{
	m_progress.SetPos(0);
	m_progress.SetBarColor(RGB(0, 255, 0));
}


void CTemperatureGetToolDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	m_fileInfo.Delete(0, m_fileInfo.GetLength()); // 释放申请的空间
	if (m_pbuf != NULL)
		delete[]m_pbuf;
}
