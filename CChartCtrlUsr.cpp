// CChartCtrlUsr.cpp: 实现文件
//

#include "pch.h"
#include "TemperatureGetTool.h"
#include "TemperatureGetToolDlg.h"
#include "CChartCtrlUsr.h"
#include "afxdialogex.h"
#include "ChartCtrl\ChartCtrl.h"
#include "ChartCtrl\PointsOrdering.h"
#include "ChartCtrl\ChartLineSerie.h"


// CChartCtrlUsr 对话框

IMPLEMENT_DYNAMIC(CChartCtrlUsr, CDialogEx)

CChartCtrlUsr::CChartCtrlUsr(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PIC_DLG, pParent)
{
	m_BackColor = RGB(0, 0, 0);
	m_GridColor = RGB(255, 255, 255);
	m_TextColor = RGB(255, 255, 255);
	m_SerieColor = RGB(0, 80, 255);
	m_LineWidth = 2;

	m_xAuto = true;
	m_yAuto = true;

	m_right = 100;
	m_left = 0;
	m_top = 90;
	m_bottom = -60;

	m_Title = _T("Draw Demo");
}

CChartCtrlUsr::~CChartCtrlUsr()
{
}

void CChartCtrlUsr::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHARTCTRL, m_ChartCtrl);
}


BEGIN_MESSAGE_MAP(CChartCtrlUsr, CDialogEx)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CChartCtrlUsr 消息处理程序


BOOL CChartCtrlUsr::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	/*
	CArray<double> Xarry, Yarry;
	for (int i = 0; i < 361; i++)
	{
		double X = 10 * sin(i / 360.0 * 2 * 3.141592);
		double Y = 10 * cos((i - 60) / 360.0 * 2 * 3.141592);

		Xarry.Add(X);
		Yarry.Add(Y);
	}

	AddDataToBuf(Xarry.GetData(), Yarry.GetData(), Xarry.GetSize());
	DrawLine();
	*/
	DrawLine();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CChartCtrlUsr::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDialogEx::OnTimer(nIDEvent);
}

void CChartCtrlUsr::DrawLine()
{
	if (m_nSize == 0) return;

	// Disable the refresh of the control (avoid multiple refresh).
	m_ChartCtrl.EnableRefresh(false);
	// Create a bottom and left axes
	CChartStandardAxis* pBottomAxis = m_ChartCtrl.CreateStandardAxis(CChartCtrl::BottomAxis);
	CChartStandardAxis* pLeftAxis = m_ChartCtrl.CreateStandardAxis(CChartCtrl::LeftAxis);

	if(m_xAuto)
		pBottomAxis->SetAutomatic(true);
	else
		pBottomAxis->SetMinMax(m_left, m_right);

	if (m_yAuto)
		pLeftAxis->SetAutomatic(true);
	else
		pLeftAxis->SetMinMax(m_bottom, m_top);

	// Add a new series of type line to the control and add data to it
	CChartLineSerie* m_pLineSeries; m_pLineSeries = m_ChartCtrl.CreateLineSerie();

	// Specifies that the points in the series are not ordered (needed to be able
	// to draw an ellipse).
	m_pLineSeries->SetSeriesOrdering(poNoOrdering);

	double X, Y;
	for (long i = 0; i < m_nSize; i++)
	{
		m_XValues.GetElement(&i, &X);
		m_YValues.GetElement(&i, &Y);
		m_pLineSeries->AddPoint(X, Y);
	}

	// Specifies a sunken border for the control
	m_ChartCtrl.SetEdgeType(EDGE_SUNKEN);

	// Config Axis
	AxisCfg();

	// Sets the color of the title, change the font to Times New Roman
	// and add a string
	AddTitle(m_Title);

	// Change the color of the line series
	m_pLineSeries->SetColor(m_SerieColor);
	m_pLineSeries->SetWidth(m_LineWidth);

	// Finally re-enable the refresh of the control. This will refresh the
	// control if any refresh was still 'pending'.
	m_ChartCtrl.EnableRefresh(true);
}


void CChartCtrlUsr::SetMinMaxAxis(double& pxMin, double& pxMax, double& pyMin, double& pyMax, bool xAuto /*= true*/, bool yAuto /*= true*/)
{
	m_xAuto = xAuto;
	m_yAuto = yAuto;
	m_left = pxMin;
	m_right = pxMax;
	m_bottom = pyMin;
	m_top = pyMax;
}

void CChartCtrlUsr::AddTitle(const TChartString &p_title)
{
	m_ChartCtrl.GetTitle()->SetColor(m_TextColor);
	m_ChartCtrl.GetTitle()->SetFont(140, _T("Times New Roman"));
	m_ChartCtrl.GetTitle()->AddString(p_title);
}

void CChartCtrlUsr::AxisCfg()
{
	// Sets the color of the border and the back color
	m_ChartCtrl.SetBorderColor(m_TextColor);
	m_ChartCtrl.SetBackColor(m_BackColor);

	//Sets the color of the different elements of the bottom axis
	m_ChartCtrl.GetBottomAxis()->SetAxisColor(m_TextColor);
	m_ChartCtrl.GetBottomAxis()->SetTextColor(m_TextColor);
	m_ChartCtrl.GetBottomAxis()->GetGrid()->SetColor(m_GridColor);

	// Sets the color of the different elements of the left axis
	m_ChartCtrl.GetLeftAxis()->SetAxisColor(m_TextColor);
	m_ChartCtrl.GetLeftAxis()->SetTextColor(m_TextColor);
	m_ChartCtrl.GetLeftAxis()->GetGrid()->SetColor(m_GridColor);
}

void CChartCtrlUsr::AddDataToBuf(double* pX, double* pY, long nNum)
{
	long i(0);
	DWORD wLength = m_nSize = nNum;
	m_XValues.Create(VT_R8, 1, &wLength);
	m_YValues.Create(VT_R8, 1, &wLength);

	for (i = 0; i < nNum; i++) {
		m_XValues.PutElement(&i, pX + i);
		m_YValues.PutElement(&i, pY + i);
	}
}
