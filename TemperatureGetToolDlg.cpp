
// TemperatureGetToolDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "TemperatureGetTool.h"
#include "TemperatureGetToolDlg.h"
#include "afxdialogex.h"
#include "CXmlGet.h"
#include "CChartCtrlUsr.h"
#include <locale.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define BTN_NUM_MAX 6

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
	ON_COMMAND(ID_BUTTON_1, &CTemperatureGetToolDlg::OnToolBarPic)
	ON_COMMAND(ID_BUTTON_2, &CTemperatureGetToolDlg::OnToolBarCalc)
	ON_COMMAND(ID_BUTTON_3, &CTemperatureGetToolDlg::OnToolBarClear)
	ON_COMMAND(ID_BUTTON_4, &CTemperatureGetToolDlg::OnToolBarOpen)
	ON_COMMAND(ID_BUTTON_5, &CTemperatureGetToolDlg::OnToolBarSave)
	ON_COMMAND(ID_BUTTON_6, &CTemperatureGetToolDlg::OnToolBarExit)
	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolBarTips)
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_WM_NCHITTEST()
END_MESSAGE_MAP()


// CTemperatureGetToolDlg 消息处理程序

// 从资源加载图标函数
BOOL CTemperatureGetToolDlg::LoadImageFromResource(CImage* pImage, UINT nResID, LPCTSTR lpTyp)
{
	if (pImage == NULL)
		return false;

	pImage->Destroy();
	// 查找资源
	HRSRC hRsrc = ::FindResource(AfxGetResourceHandle(), MAKEINTRESOURCE(nResID), lpTyp);
	if (hRsrc == NULL)
		return false;
	// 加载资源
	HGLOBAL hImgData = ::LoadResource(AfxGetResourceHandle(), hRsrc);
	if (hImgData == NULL) {
		::FreeResource(hImgData);
		return false;
	}

	// 锁定内存中的指定资源
	LPVOID lpVoid = ::LockResource(hImgData);
	LPSTREAM pStream = NULL;
	DWORD dwSize = ::SizeofResource(AfxGetResourceHandle(), hRsrc);
	HGLOBAL hNew = ::GlobalAlloc(GHND, dwSize);
	LPBYTE lpByte = (LPBYTE)::GlobalLock(hNew);
	::memcpy(lpByte, lpVoid, dwSize);
	// 解除内存中的指定资源
	::GlobalUnlock(hNew);
	// 从指定内存创建流对象
	HRESULT ht = ::CreateStreamOnHGlobal(hNew, TRUE, &pStream);
	if (ht != S_OK) {
		GlobalFree(hNew);
	}
	else {
		// 加载图片
		pImage->Load(pStream);
		GlobalFree(hNew);
	}
	// 释放资源
	::FreeResource(hImgData);
	return true;
}

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

	// 创建倒角
	RECT rc;
	GetClientRect(&rc); //获取客户区 上下左右 位置
	m_rgn.CreateRoundRectRgn(rc.left, rc.top, rc.right, rc.bottom, 9, 9); //矩形圆角
	SetWindowRgn(m_rgn, TRUE); //椭圆

	// 设置为只保留客户区风格
	DWORD dwStyle = GetStyle();//获取旧样式  
	DWORD dwNewStyle = WS_OVERLAPPED | WS_VISIBLE | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
	dwNewStyle &= dwStyle;//按位与将旧样式去掉  
	SetWindowLong(m_hWnd, GWL_STYLE, dwNewStyle);//设置成新的样式  
	DWORD dwExStyle = GetExStyle();//获取旧扩展样式  
	DWORD dwNewExStyle = WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR;
	dwNewExStyle &= dwExStyle;//按位与将旧扩展样式去掉  
	SetWindowLong(m_hWnd, GWL_EXSTYLE, dwNewExStyle);//设置新的扩展样式  
	SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);		// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	OnInitListCtrl();
	OnInitProgress();
	OnInitToolBar();
	OnInitBackground();
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
	int nRet = (int)dlg.DoModal();

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

	if (FALSE == bRet) return bRet;

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
	m_list.SetExtendedStyle(dwStyle);

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
	TRY {
		CString clip_buf;
		CString strText;
		POSITION pos = m_list.GetFirstSelectedItemPosition();

		if (pos == NULL) {
			TRACE(_T("No items were selected!\n"));
		}
		else {
			while (pos) {
				int nItem = m_list.GetNextSelectedItem(pos);
				strText = m_list.GetItemText(nItem, 0);
				int nCount = m_list.GetHeaderCtrl()->GetItemCount();

				for (int i = 1; i < nCount; ++i) {
					strText = strText + CString("\t") + m_list.GetItemText(nItem, i);
				}
				clip_buf += strText + CString("\n");
			}
		}
		// 复制到剪切板
		if (!clip_buf.IsEmpty()) {
			if (OpenClipboard()) {
				EmptyClipboard();
				TCHAR* pszData;
				HGLOBAL hClipboardData = GlobalAlloc(GMEM_DDESHARE, ((long)clip_buf.GetLength() + 1) * sizeof(TCHAR));

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
	CATCH_ALL(e) {
		e->ReportError();
		return;
	}
	END_CATCH_ALL
}

void CTemperatureGetToolDlg::OnKeydownList(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
	if ((::GetKeyState(VK_CONTROL) & 0x8000) && (pLVKeyDow->wVKey == 'C' || pLVKeyDow->wVKey == 'c')) {
		OnCopyClick();
	}
	*pResult = 0;
}

void CTemperatureGetToolDlg::OnMenuSave()
{
	static TCHAR szFilter[] =
		_T("XML Files (*.xls)|*.xls|")
		_T("All Files (*.*)|*.*||");

	CFileDialog dlg(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		szFilter, NULL, 0, NULL);

	int nRet = (int)dlg.DoModal();
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

	setlocale(LC_CTYPE, ("chs")); // 设置中文输出
	file.WriteString(_T("序号\t时间\t原始数据\t温度/℃\t湿度/RH%\n")); // 设置表头标题内容

	CString strText, strBuf;
	int row = 0;
	pThis->m_progress.SetRange32(0, nItem);
	pThis->m_progress.SetPos(0);

	// 逐行导出
	while (row < nItem) {
		strText = pThis->m_list.GetItemText(row, 0);
		int nCount = pThis->m_list.GetHeaderCtrl()->GetItemCount();

		for (int i = 1; i < nCount; ++i) {
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
	static TCHAR szFilter[] =
		_T("XML Files (*.xls)|*.xls|")
		_T("All Files (*.*)|*.*||");

	CFileDialog dlg(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		szFilter, NULL, 0, NULL);

	int nRet = (int)dlg.DoModal();
	CString savePath;

	if (nRet == IDOK) {
		savePath = dlg.GetPathName();
		// 判断是否有文件后缀，没有则追加xls后缀
		if (savePath.Find(_T(".xls")) < 0) {
			savePath += _T(".xls");
		}
		if (m_filePath.IsEmpty()) { // 先前未存，调用导出函数保存文件
			ReportExcel(savePath);
		}
		else { // 另存为，直接使用copy命令拷贝一份
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
	int temp_arry[4];

	if (hexl == NULL || hexh == NULL) return -1;

	temp_arry[3] = hexl[3]; // hexh="0x69" hexl="0xef" -> 0x69ef
	temp_arry[2] = hexl[2];
	temp_arry[1] = hexh[3];
	temp_arry[0] = hexh[2];

	size_t len = sizeof(temp_arry) / sizeof(int);
	for (size_t i = 0; i < len; i++) {
		if ((temp_arry[i] >= 'a') && (temp_arry[i] <= 'f')) {
			temp_arry[i] = temp_arry[i] - 'a' + 10;
		}
		else if ((temp_arry[i] >= 'A') && (temp_arry[i] <= 'F')) {
			temp_arry[i] = temp_arry[i] - 'A' + 10;
		}
		else {
			temp_arry[i] = temp_arry[i] - '0';
		}
		res = (res << 4) + temp_arry[i];
	}

	if (res != 0 && !type) res -= 20000;

	return res;
}

// 分离报文中的温度数据和湿度数据
void CTemperatureGetToolDlg::calc(char* pbuf, double* out_temp, double* out_humid)
{
	const char* d = " ";
	char* p;
	char buf[8][5] = { {0} };
	int i = 0;
	p = strtok(pbuf, d);

	while (p) {
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
	pThis->m_pbuf = pThis->CStringtochar(pThis->m_fileInfo); // 获取窗口this指针

	char buf[512] = { 0 };
	char* p_addr = pThis->m_pbuf;
	int i = pThis->m_list.GetItemCount();
	double temp = 0.0;
	double humid = 0.0;
	TCHAR no[64] = {0};
	TCHAR strTmp[64] = {0}, strHumid[64] = {0};
	int offset = 0;
	while (1) {
		offset = pThis->m_xmlObj.GetXMLBuffer_Str(p_addr, "Abs", buf); // 提取时间字段内容
		if (offset == -1) break;

		pThis->m_time = buf;
		offset = pThis->m_xmlObj.GetXMLBuffer_Str(p_addr, "Data", buf); // 提取数据字段内容
		pThis->m_data = buf;

		calc(buf, &temp, &humid);
		_stprintf_s(strTmp, sizeof(strTmp) / 2, _T("%5.2lf"), temp);
		_stprintf_s(strHumid, sizeof(strHumid) / 2, _T("%4.2lf"), humid);

		_stprintf_s(no, sizeof(no) / 2, _T("%d"), i + 1);
		pThis->m_list.InsertItem(i, (LPCTSTR)no);
		pThis->m_list.SetItemText(i, 1, pThis->m_time);
		pThis->m_list.SetItemText(i, 2, pThis->m_data);
		pThis->m_list.SetItemText(i, 3, (LPCTSTR)strTmp);
		pThis->m_list.SetItemText(i, 4, (LPCTSTR)strHumid);

		p_addr = (char*)offset;
		pThis->m_list.SendMessage(WM_VSCROLL, SB_BOTTOM, NULL);
		++i;
	}

	pThis->m_fileInfo.Empty();
	pThis->m_time.Empty();
	pThis->m_data.Empty();
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

	ShellExecuteEx(&ShExecInfo); // 通过外部程序打开导出的文件
}

void CTemperatureGetToolDlg::OnInitProgress()
{
	m_progress.SetPos(0);
	m_progress.SetBarColor(RGB(0, 255, 0));
}

void CTemperatureGetToolDlg::OnInitToolBar(void)
{
	// 1.注册工具栏
	m_ToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP |
		CBRS_TOOLTIPS | CBRS_SIZE_DYNAMIC);
	
	// 2.创建图像列表
	m_ImageList.Create(64, 64, ILC_COLOR32 | ILC_MASK, 0, 0);
	CBitmap bmp;
	for (int i = 0; i < BTN_NUM_MAX; ++i) {
		bmp.LoadBitmap(IDB_BITMAP1 + i);
		m_ImageList.Add(&bmp, RGB(255, 255, 255));
		bmp.DeleteObject();
	}

	// 3.分配按钮ID
	UINT nArray[BTN_NUM_MAX];
	for (int i = 0; i < BTN_NUM_MAX; ++i) {
		nArray[i] = ID_BUTTON_1 + i;
	}
	m_ToolBar.SetButtons(nArray, BTN_NUM_MAX);
	m_ToolBar.SetSizes(CSize(72, 72), CSize(64, 64));

	// 4.设置图像列表
	m_ToolBar.EnableToolTips();
	m_ToolBar.GetToolBarCtrl().SetImageList(&m_ImageList);

	// 移动窗口
	CRect rect_wnd;
	GetClientRect(rect_wnd);
	CRect rect(0, 10, 435, 80 + 5);
	rect.OffsetRect(rect_wnd.right / 2 - rect.right / 2, 0);
	m_ToolBar.MoveWindow(rect); 

	// RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
}

void CTemperatureGetToolDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	m_fileInfo.Empty();
	m_data.Empty();
	m_time.Empty();
	m_filePath.Empty();
	if (m_pbuf != NULL) delete []m_pbuf;
}

void CTemperatureGetToolDlg::OnToolBarPic()
{
	CChartCtrlUsr charCtrl;
	CArray<double> xArry, yArry;
	long nItem = 0;
	TCHAR buf[128] = {0};
	double x, y;

	nItem = m_list.GetItemCount();
	if (nItem) {
		for (long i = 0; i < nItem; ++i) {
			m_list.GetItemText(i, 0, buf, sizeof(buf));
			x = _ttof(buf);
			m_list.GetItemText(i, 3, buf, sizeof(buf));
			y = _ttof(buf);

			xArry.Add(x);
			yArry.Add(y);
		}
		charCtrl.AddDataToBuf(xArry.GetData(), yArry.GetData(), xArry.GetSize());
	}
	charCtrl.DoModal();

	xArry.RemoveAll();
	yArry.RemoveAll();
}

void CTemperatureGetToolDlg::OnToolBarCalc()
{
	PROCESS_INFORMATION pi;
	STARTUPINFO si;

	memset(&pi, 0, sizeof(PROCESS_INFORMATION));
	memset(&si, 0, sizeof(STARTUPINFO));

	si.cb = sizeof(STARTUPINFO);
	si.wShowWindow = SW_SHOW;
	si.dwFlags = STARTF_USESHOWWINDOW;

	::CreateProcess(_T("C://windows//system32//calc.exe"), NULL, NULL, FALSE,
		NULL, NULL, NULL, NULL, &si, &pi);

	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

void CTemperatureGetToolDlg::OnToolBarClear()
{
	if (m_list.GetItemCount() != 0)
		m_list.DeleteAllItems();
}

void CTemperatureGetToolDlg::OnToolBarOpen()
{
	OnFileOpen();
}

void CTemperatureGetToolDlg::OnToolBarSave()
{
	OnMenuSave();
}

void CTemperatureGetToolDlg::OnToolBarExit()
{
	OnClose();
}

BOOL CTemperatureGetToolDlg::OnToolBarTips(UINT id, NMHDR* pNMHDR, LRESULT* pResult)
{
	TOOLTIPTEXT* pTTT = (TOOLTIPTEXT*)pNMHDR;
	UINT nID = pNMHDR->idFrom;
	UINT nIndex = m_ToolBar.CommandToIndex(nID);
	switch (nIndex)
	{
	case 0:
		m_strTips.Format(_T("打开曲线图"));
		break;    
	case 1:
		m_strTips.Format(_T("计算器"));
		break;
	case 2:
		m_strTips.Format(_T("清除列表数据"));
		break;
	case 3:
		m_strTips.Format(_T("加载xml文件"));
	break;
	case 4:
		m_strTips.Format(_T("保存文件"));
		break;
	case 5:
		m_strTips.Format(_T("退出应用"));
		break;
	default:
		break;
	}
	pTTT->lpszText = m_strTips.GetBuffer(m_strTips.GetLength());
	pTTT->hinst = AfxGetResourceHandle();
	return TRUE;
}


void CTemperatureGetToolDlg::OnInitBackground()
{
	CImage img;
	//img.Load(_T("./res/bg.png"));
	LoadImageFromResource(&img, IDB_PNG1);

	CBitmap bmp;
	bmp.Attach(img.Detach());
	m_brush.CreatePatternBrush(&bmp);
}

HBRUSH CTemperatureGetToolDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	return m_brush;
}

LRESULT CTemperatureGetToolDlg::OnNcHitTest(CPoint point)
{
	return HTCAPTION;
}
