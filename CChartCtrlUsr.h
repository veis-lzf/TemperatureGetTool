#pragma once

#include "ChartCtrl\ChartCtrl.h"

// CChartCtrlUsr 对话框

class CChartCtrlUsr : public CDialogEx
{
	DECLARE_DYNAMIC(CChartCtrlUsr)

public:
	CChartCtrlUsr(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CChartCtrlUsr();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PIC_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	
protected:
	COLORREF m_BackColor;
	COLORREF m_GridColor;
	COLORREF m_TextColor;
	COLORREF m_SerieColor;
	UINT m_LineWidth;
	TChartString m_Title;
	double m_left, m_right, m_top, m_bottom;
	bool m_xAuto, m_yAuto;
	COleSafeArray m_XValues;
	COleSafeArray m_YValues;
	CChartCtrl m_ChartCtrl;
	long m_nSize;

private:
	void AddTitle(const TChartString& p_title);
	void AxisCfg(void);

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void DrawLine(void);
	void AddDataToBuf(double* pX, double* pY, long nNum);
	void SetMinMaxAxis(double& pxMin, double& pxMax, double& pyMin, double& pyMax, bool xAuto = true, bool yAuto = true);

	
	inline void SetLineColor(COLORREF col)
	{
		m_SerieColor = col;
	}
	inline void SetTextColor(COLORREF col)
	{
		m_TextColor = col;
	}
	inline void SetGridColor(COLORREF col)
	{
		m_GridColor = col;
	}
	inline void SetBackColor(COLORREF col)
	{
		m_BackColor = col;
	}
	inline void SetLineWidth(UINT LineWidth)
	{
		m_LineWidth = LineWidth;
	}
	inline void SetTitle(const TChartString& title)
	{
		m_Title = title;
	}

};
