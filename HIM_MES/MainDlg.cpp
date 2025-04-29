#include "pch.h"
#include "HIM_MES.h"
#include "MainDlg.h"
#include "afxdialogex.h"
#include <afxext.h> 
#include "DashboardDlg.h"
#include "ProductionDlg.h"
#include "EquipDlg.h"
#include "SystemDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// MainDlg 다이얼로그

IMPLEMENT_DYNAMIC(MainDlg, CDialogEx)

MainDlg::MainDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_MAIN_DIALOG, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

MainDlg::~MainDlg()
{
    // 생성한 GDI 객체 정리
    m_brushBg.DeleteObject();
    m_brushButtonBg.DeleteObject();
    m_fontMenu.DeleteObject();
}

void MainDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_BTN_DASHBOARD, m_btnDashboard);
    DDX_Control(pDX, IDC_BTN_PRODUCTION, m_btnProduction);
    DDX_Control(pDX, IDC_BTN_FACILITY, m_btnEquipment); // 주의: ID가 FACILITY로 정의됨
    DDX_Control(pDX, IDC_BTN_SYSTEM, m_btnSystem); 
}

BEGIN_MESSAGE_MAP(MainDlg, CDialogEx)
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_WM_CTLCOLOR()
    ON_BN_CLICKED(IDC_BTN_DASHBOARD, &MainDlg::OnBnClickedBtnDashboard)
    ON_BN_CLICKED(IDC_BTN_PRODUCTION, &MainDlg::OnBnClickedBtnProduction)
    ON_BN_CLICKED(IDC_BTN_FACILITY, &MainDlg::OnBnClickedBtnEquipment)
    ON_BN_CLICKED(IDC_BTN_SYSTEM, &MainDlg::OnBnClickedBtnSystem)
    ON_WM_DRAWITEM()
END_MESSAGE_MAP()

BOOL MainDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // 다이얼로그 제목 설정
    SetWindowText(_T("메인 - HIM MES"));

    // 아이콘 설정
    SetIcon(m_hIcon, TRUE);
    SetIcon(m_hIcon, FALSE);

    // 배경색 설정
    m_brushBg.CreateSolidBrush(RGB(245, 248, 255));        // 연한 하늘색 배경
    m_brushButtonBg.CreateSolidBrush(RGB(235, 245, 255));  // 버튼 배경색
    m_brushStatusBg.CreateSolidBrush(RGB(227, 242, 253));  // 상태표시줄 배경색

    // 폰트 설정
    m_fontMenu.CreatePointFont(100, _T("맑은 고딕"));
    m_fontStatus.CreatePointFont(10, _T("맑은 고딕"));

    // 메뉴 버튼 스타일 설정 (Owner-draw)
    m_btnDashboard.ModifyStyle(0, BS_OWNERDRAW);
    m_btnProduction.ModifyStyle(0, BS_OWNERDRAW);
    m_btnEquipment.ModifyStyle(0, BS_OWNERDRAW);
    m_btnSystem.ModifyStyle(0, BS_OWNERDRAW);

    // 버튼 크기 및 위치 수정 (Owner-draw 스타일에 맞게)
    // 버튼 간격과 크기를 균일하게 조정
    CRect rect;
    GetClientRect(&rect);

    int btnWidth = 200;  // 버튼 너비
    int btnHeight = 200; // 버튼 높이
    int hGap = 30;       // 가로 간격
    int vGap = 30;       // 세로 간격
    int hMargin = (rect.Width() - 2 * btnWidth - hGap) / 2;    // 좌우 여백
    int vMargin = (rect.Height() - 2 * btnHeight - vGap - 30) / 2;  // 상하 여백 (상태표시줄 공간 확보)

    // 버튼 위치 설정
    m_btnDashboard.MoveWindow(hMargin, vMargin, btnWidth, btnHeight);
    m_btnProduction.MoveWindow(hMargin + btnWidth + hGap, vMargin, btnWidth, btnHeight);
    m_btnEquipment.MoveWindow(hMargin, vMargin + btnHeight + vGap, btnWidth, btnHeight);
    m_btnSystem.MoveWindow(hMargin + btnWidth + hGap, vMargin + btnHeight + vGap, btnWidth, btnHeight);

    // 상태 표시줄 생성 (CStatusBar 사용)
    m_statusBar.Create(this);
    UINT indicators[] = { ID_SEPARATOR, ID_SEPARATOR, ID_SEPARATOR };
    m_statusBar.SetIndicators(indicators, 3);
    m_statusBar.SetPaneInfo(0, ID_SEPARATOR, SBPS_NORMAL, 200);
    m_statusBar.SetPaneInfo(1, ID_SEPARATOR, SBPS_NORMAL, 170);
    m_statusBar.SetPaneInfo(2, ID_SEPARATOR, SBPS_NORMAL, 300);

    // 크기 조정하여 표시
    RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);

    // 상태 표시줄 높이 조절
    CRect rcStatusBar;
    m_statusBar.GetWindowRect(&rcStatusBar);
    ScreenToClient(&rcStatusBar);
    rcStatusBar.top -= 10; // 높이 5픽셀 증가
    m_statusBar.MoveWindow(&rcStatusBar);


    // 패널에 텍스트 설정
    m_statusBar.SetPaneText(0, _T("사용자: 관리자"));
    m_statusBar.SetPaneText(1, _T("버전: 1.0.0"));

    // 현재 시간 표시
    CTime currentTime = CTime::GetCurrentTime();
    CString strTime;
    strTime.Format(_T("최종 접속: %04d-%02d-%02d %02d:%02d"),
        currentTime.GetYear(), currentTime.GetMonth(), currentTime.GetDay(),
        currentTime.GetHour(), currentTime.GetMinute());
    m_statusBar.SetPaneText(2, strTime);


    return TRUE;
}

void MainDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this);

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {   
        CDialogEx::OnPaint();
    }
}

HBRUSH MainDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    UINT id = pWnd->GetDlgCtrlID();

    if (nCtlColor == CTLCOLOR_DLG)
    {
        return m_brushBg;  // 다이얼로그 배경색
    }

    // 일반 Static 컨트롤 배경색
    if (nCtlColor == CTLCOLOR_STATIC)
    {
        pDC->SetBkMode(TRANSPARENT);
        return m_brushBg;
    }

    return CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
}

HCURSOR MainDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

void MainDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    if (lpDrawItemStruct->CtlType != ODT_BUTTON)
    {
        CDialogEx::OnDrawItem(nIDCtl, lpDrawItemStruct);
        return;
    }

    CDC dc;
    dc.Attach(lpDrawItemStruct->hDC);

    CRect rect = lpDrawItemStruct->rcItem;
    UINT state = lpDrawItemStruct->itemState;
    CString strText;

    // 버튼 ID에 따라 텍스트 설정
    switch (nIDCtl)
    {
    case IDC_BTN_DASHBOARD:
        strText = _T("대시보드");
        break;
    case IDC_BTN_PRODUCTION:
        strText = _T("생산 관리");
        break;
    case IDC_BTN_FACILITY:
        strText = _T("설비 관리");
        break;
    case IDC_BTN_SYSTEM:
        strText = _T("시스템 구성");
        break;
    default:
        break;
    }

    // 버튼 배경 그리기
    COLORREF bgColor = RGB(255, 255, 255);        // 기본 흰색
    COLORREF borderColor = RGB(0, 93, 255);       // 파란색 테두리
    COLORREF iconColor = RGB(0, 93, 255);         // 아이콘 색상
    COLORREF textColor = RGB(0, 93, 255);         // 텍스트 색상

    if (state & ODS_SELECTED)
    {
        // 버튼이 눌렸을 때
        bgColor = RGB(227, 242, 253);  // 더 진한 연한 파란색
    }
    else if (state & ODS_FOCUS || state & ODS_HOTLIGHT)
    {
        // 포커스가 있거나 마우스 오버 상태
        bgColor = RGB(235, 245, 255);  // 연한 파란색
    }

    // 버튼 배경 채우기
    dc.FillSolidRect(rect, bgColor);

    // 테두리 그리기 (마우스 오버 시에만 점선 테두리, 나머지는 실선)
    CPen borderPen;
    if (state & ODS_FOCUS || state & ODS_HOTLIGHT)
    {
        // 점선 테두리용 펜 생성 (마우스 오버 시)
        LOGBRUSH lb;
        lb.lbStyle = BS_SOLID;
        lb.lbColor = borderColor;
        lb.lbHatch = 0;
        borderPen.CreatePen(PS_DASH | PS_GEOMETRIC, 2, &lb);
    }
    else
    {
        // 실선 테두리 (일반 상태)
        borderPen.CreatePen(PS_SOLID, 2, borderColor);
    }

    CPen* pOldPen = dc.SelectObject(&borderPen);
    dc.Rectangle(rect);

    // 아이콘 영역
    CRect iconRect = rect;
    iconRect.bottom = rect.top + (rect.Height() * 2 / 3);
    iconRect.DeflateRect(rect.Width() / 4, rect.Height() / 6);

    // 아이콘 배경
    dc.FillSolidRect(iconRect, RGB(235, 245, 255));  // 연한 파란색 배경

    // 아이콘 그리기
    CBrush iconBrush(iconColor);
    CBrush* pOldBrush = dc.SelectObject(&iconBrush);

    CPoint center = iconRect.CenterPoint();

    switch (nIDCtl)
    {
    case IDC_BTN_DASHBOARD:
    {
        // 대시보드 아이콘 (원형 + 가로 선 3개)
        int radius = min(iconRect.Width(), iconRect.Height()) / 2 - 5;
        dc.Ellipse(center.x - radius, center.y - radius,
            center.x + radius, center.y + radius);

        // 가로 선 3개
        int lineWidth = radius * 1.2;
        int lineHeight = radius / 6;
        int lineSpacing = radius / 3;

        CRect line1(center.x - lineWidth / 2, center.y - lineSpacing - lineHeight / 2,
            center.x + lineWidth / 2, center.y - lineSpacing + lineHeight / 2);

        CRect line2(center.x - lineWidth / 2, center.y - lineHeight / 2,
            center.x + lineWidth / 2, center.y + lineHeight / 2);

        CRect line3(center.x - lineWidth / 2, center.y + lineSpacing - lineHeight / 2,
            center.x + lineWidth / 2, center.y + lineSpacing + lineHeight / 2);

        dc.FillSolidRect(line1, RGB(255, 255, 255));
        dc.FillSolidRect(line2, RGB(255, 255, 255));
        dc.FillSolidRect(line3, RGB(255, 255, 255));
    }
    break;

    case IDC_BTN_PRODUCTION:
    {
        // 생산 관리 아이콘 (다이아몬드)
        int size = min(iconRect.Width(), iconRect.Height()) / 2;
        POINT diamond[4] = {
            {center.x, center.y - size},  // 상
            {center.x + size, center.y},  // 우
            {center.x, center.y + size},  // 하
            {center.x - size, center.y}   // 좌
        };
        dc.Polygon(diamond, 4);

        // 중앙 원
        int innerRadius = size / 3;
        dc.SelectObject(GetStockObject(WHITE_BRUSH));
        dc.Ellipse(center.x - innerRadius, center.y - innerRadius,
            center.x + innerRadius, center.y + innerRadius);
    }
    break;

    case IDC_BTN_FACILITY:
    {
        // 설비 관리 아이콘 (육각형)
        int size = min(iconRect.Width(), iconRect.Height()) / 2;
        POINT hexagon[6];
        for (int i = 0; i < 6; i++) {
            double angle = i * 60.0 * 3.14159265358979323846 / 180.0;
            hexagon[i].x = center.x + (int)(size * cos(angle));
            hexagon[i].y = center.y + (int)(size * sin(angle));
        }
        dc.Polygon(hexagon, 6);

        // 중앙 삼각형
        int innerSize = size / 2;
        POINT triangle[3] = {
            {center.x, center.y - innerSize},
            {center.x + innerSize, center.y + innerSize / 2},
            {center.x - innerSize, center.y + innerSize / 2}
        };
        dc.SelectObject(GetStockObject(WHITE_BRUSH));
        dc.Polygon(triangle, 3);
    }
    break;

    case IDC_BTN_SYSTEM:
    {
        // 시스템 구성 아이콘 (사람 + 막대)
        // 사람 머리 (원)
        int headRadius = min(iconRect.Width(), iconRect.Height()) / 4;
        dc.Ellipse(center.x - headRadius, center.y - headRadius - headRadius / 2,
            center.x + headRadius, center.y + headRadius - headRadius / 2);

        // 막대 3개
        int barWidth = headRadius * 0.8;
        int barHeight = headRadius * 0.8;
        int barSpacing = barWidth + barWidth / 3;

        // 중앙 막대
        CRect bar2(center.x - barWidth / 2, center.y + headRadius / 2,
            center.x + barWidth / 2, center.y + headRadius / 2 + barHeight);

        // 좌측 막대 
        CRect bar1(center.x - barWidth / 2 - barSpacing, center.y + headRadius / 2,
            center.x + barWidth / 2 - barSpacing, center.y + headRadius / 2 + barHeight);

        // 우측 막대
        CRect bar3(center.x - barWidth / 2 + barSpacing, center.y + headRadius / 2,
            center.x + barWidth / 2 + barSpacing, center.y + headRadius / 2 + barHeight);

        dc.FillSolidRect(bar1, iconColor);
        dc.FillSolidRect(bar2, iconColor);
        dc.FillSolidRect(bar3, iconColor);
    }
    break;
    }

    // 텍스트 영역
    CRect textRect = rect;
    textRect.top = rect.top + (rect.Height() * 2 / 3);

    // 텍스트 그리기
    dc.SetBkMode(TRANSPARENT);
    dc.SetTextColor(textColor);

    CFont* pOldFont = dc.SelectObject(&m_fontMenu);
    dc.DrawText(strText, textRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    // 리소스 복원
    dc.SelectObject(pOldPen);
    dc.SelectObject(pOldBrush);
    dc.SelectObject(pOldFont);
    dc.Detach();
}

// 버튼 클릭 이벤트 핸들러 
void MainDlg::OnBnClickedBtnDashboard()
{
    CDashboardDlg dlg;
    dlg.DoModal();  // 대시보드 창 열기
}

void MainDlg::OnBnClickedBtnProduction()
{
    CProductionDlg dlg;
    dlg.DoModal();  // 생산관리 창 열기
}

void MainDlg::OnBnClickedBtnEquipment()  // 함수명 주의
{
    CEquipDlg dlg;
    dlg.DoModal();  // 설비관리 창 열기
}

void MainDlg::OnBnClickedBtnSystem()
{
    CSystemDlg dlg;
    dlg.DoModal();  // 시스템 구성 창 열기
}