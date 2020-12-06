
// TemperatureGetToolDlg.h: 头文件
//

#pragma once
#include "CXmlGet.h"

// CTemperatureGetToolDlg 对话框
class CTemperatureGetToolDlg : public CDialogEx
{
// 构造
public:
	enum btn_id
	{
		ID_BUTTON_1 = 567,
		ID_BUTTON_2,
		ID_BUTTON_3,
		ID_BUTTON_4,
		ID_BUTTON_5,
		ID_BUTTON_6,
	};
	CTemperatureGetToolDlg(CWnd* pParent = nullptr);	// 标准构造函数
	~CTemperatureGetToolDlg();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEMPERATUREGETTOOL_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	// 实现
protected:
	HICON m_hIcon;
	HACCEL m_Accelerator;
	CListCtrl m_list;
	CString m_fileInfo;
	CXmlGet m_xmlObj;
	CString m_data;
	CString m_time;
	CWinThread* m_pThread;
	CString m_filePath;
	CProgressCtrl m_progress;
	CToolBar m_ToolBar;
	CImageList m_ImageList;
	CString m_strTips;
	CBrush m_brush;
	CRgn m_rgn;
	char* m_pbuf;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnRclickList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCopyClick();
	afx_msg void OnKeydownList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMenuSave();
	afx_msg void OnAboutShow();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnMenuSaveAs();
	afx_msg void OnDestroy(void);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg LRESULT OnNcHitTest(CPoint point);

	inline void CTemperatureGetToolDlg::OnMenuExit() { OnClose(); }
	inline void CTemperatureGetToolDlg::OnOK() { }
	inline void CTemperatureGetToolDlg::OnCancel() { }
	inline void CTemperatureGetToolDlg::OnClose() { CDialogEx::OnCancel(); }
	inline void CTemperatureGetToolDlg::OnMenuOpen() { OnFileOpen(); }

	DECLARE_MESSAGE_MAP()

private:
	void OnFileOpen(void);
	BOOL ReadFile(CString strPath);
	void ReadANSIFile(CFile& file);
	void ReadUTF8(CFile& file);
	void ReadUnicode(CFile& file);
	char* CStringtochar(CString str);
	void ReportExcel(LPCTSTR strPath);
	void OnInitListCtrl(void);
	void OpenFileByPath(LPCTSTR strPath);
	void OnInitProgress(void);
	void OnInitToolBar(void);
	void OnToolBarPic(void);
	void OnToolBarCalc(void);
	void OnToolBarClear(void);
	void OnToolBarOpen(void);
	void OnToolBarSave(void);
	void OnToolBarExit(void);
	BOOL OnToolBarTips(UINT id, NMHDR* pNMHDR, LRESULT* pResult);
	BOOL LoadImageFromResource(CImage* pImage, UINT nResID, LPCTSTR lpTyp = _T("PNG"));

protected:
	static int strHexToDec(char* hexl, char* hexh, int type);
	static void calc(char* pbuf, double* out_temp, double* out_humid);
	static UINT __cdecl MyControllingFunction(LPVOID pParam);
	static UINT __cdecl ExportExcelThread(LPVOID pParam);
	void OnInitBackground();
};
