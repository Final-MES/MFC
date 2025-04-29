// DashboardDlg.cpp
#include "pch.h"
#include "DashboardDlg.h"
#include "EquipDlg.h"
#include "ProductionDlg.h"
#include "SystemDlg.h"
#include "afxdialogex.h"
#include "resource.h"

IMPLEMENT_DYNAMIC(CDashboardDlg, CDialogEx)

CDashboardDlg::CDashboardDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_DASHBOARD_DIALOG, pParent), m_nAnimStep(0), m_bBlinkState(false)
{
}

CDashboardDlg::~CDashboardDlg()
{
    // 타이머가 있다면 제거
    /*KillTimer(1001);*/

    // 생성한 GDI 객체 정리
    m_brushBg.DeleteObject();
    m_brushWidgetBg.DeleteObject();
    m_brushSidebarBg.DeleteObject();
    m_fontTitle.DeleteObject();
    m_fontWidgetTitle.DeleteObject();
    m_fontMenu.DeleteObject();
    m_fontContent.DeleteObject();
}

void CDashboardDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_BTN_DASHBOARD, m_btnDashboard);
    DDX_Control(pDX, IDC_BTN_PRODUCTION, m_btnProduction);
    DDX_Control(pDX, IDC_BTN_EQUIP, m_btnEquipment);
    DDX_Control(pDX, IDC_BTN_SYSTEM, m_btnSystem);

    // 대시보드 위젯 버튼 추가
    DDX_Control(pDX, IDC_BTN_PROD_STAT, m_btnProdStat);
    DDX_Control(pDX, IDC_BTN_KPI, m_btnKPI);
    DDX_Control(pDX, IDC_BTN_REALTIME, m_btnRealtime);
    DDX_Control(pDX, IDC_BTN_ALERT, m_btnAlert);
}

BEGIN_MESSAGE_MAP(CDashboardDlg, CDialogEx)
    ON_BN_CLICKED(IDC_BTN_DASHBOARD, &CDashboardDlg::OnBnClickedBtnDashboard)
    ON_BN_CLICKED(IDC_BTN_PRODUCTION, &CDashboardDlg::OnBnClickedBtnProduction)
    ON_BN_CLICKED(IDC_BTN_EQUIP, &CDashboardDlg::OnBnClickedBtnEquip)
    ON_BN_CLICKED(IDC_BTN_SYSTEM, &CDashboardDlg::OnBnClickedBtnSystem)
    ON_BN_CLICKED(IDC_BTN_PROD_STAT, &CDashboardDlg::OnBnClickedBtnProdStat)
    ON_BN_CLICKED(IDC_BTN_KPI, &CDashboardDlg::OnBnClickedBtnKpi)
    ON_BN_CLICKED(IDC_BTN_REALTIME, &CDashboardDlg::OnBnClickedBtnRealtime)
    ON_BN_CLICKED(IDC_BTN_ALERT, &CDashboardDlg::OnBnClickedBtnAlert)
    ON_WM_CTLCOLOR()
    ON_WM_PAINT()
    ON_WM_DRAWITEM()
    ON_WM_TIMER()
    ON_WM_DESTROY()


END_MESSAGE_MAP()

void CDashboardDlg::OnBnClickedBtnDashboard()
{
    // 대시보드 버튼은 현재 화면이므로 아무 동작 안함
}

void CDashboardDlg::OnBnClickedBtnProduction()
{
    KillTimer(1001);
    this->EndDialog(IDCANCEL);
    CProductionDlg dlg;
    dlg.DoModal();
}

void CDashboardDlg::OnBnClickedBtnEquip()
{
    KillTimer(1001);
    this->EndDialog(IDCANCEL);
    CEquipDlg dlg;
    dlg.DoModal();
}

void CDashboardDlg::OnBnClickedBtnSystem()
{
    KillTimer(1001);
    this->EndDialog(IDCANCEL);
    CSystemDlg dlg;
    dlg.DoModal();
}

void CDashboardDlg::OnBnClickedBtnProdStat()
{
    // 전체 생산 현황 버튼 클릭 처리
    MessageBox(_T("전체 생산 현황 화면으로 이동합니다."), _T("알림"), MB_OK | MB_ICONINFORMATION);
    // 여기에 실제 기능 구현
}

void CDashboardDlg::OnBnClickedBtnKpi()
{
    // 핵심 성과 지표 버튼 클릭 처리
    MessageBox(_T("핵심 성과 지표 화면으로 이동합니다."), _T("알림"), MB_OK | MB_ICONINFORMATION);
    // 여기에 실제 기능 구현
}

void CDashboardDlg::OnBnClickedBtnRealtime()
{
    // 실시간 데이터 분석 버튼 클릭 처리
    MessageBox(_T("실시간 데이터 분석 화면으로 이동합니다."), _T("알림"), MB_OK | MB_ICONINFORMATION);
    // 여기에 실제 기능 구현
}

void CDashboardDlg::OnBnClickedBtnAlert()
{
    // 긴급 알림 버튼 클릭 처리
    MessageBox(_T("긴급 알림 화면으로 이동합니다."), _T("알림"), MB_OK | MB_ICONINFORMATION);
    // 여기에 실제 기능 구현
}

BOOL CDashboardDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // 다이얼로그 제목 설정
    SetWindowText(_T("대시보드 - HIM MES"));

    // 배경색 설정
    m_brushBg.CreateSolidBrush(RGB(245, 248, 255));        // 연한 하늘색 배경
    m_brushWidgetBg.CreateSolidBrush(RGB(255, 255, 255));  // 위젯 배경색
    m_brushSidebarBg.CreateSolidBrush(RGB(50, 63, 79));    // 사이드바 배경색 (진한 남색)

    // 폰트 설정
    m_fontTitle.CreatePointFont(120, _T("맑은 고딕 Bold"));
    m_fontWidgetTitle.CreatePointFont(100, _T("맑은 고딕"));
    m_fontMenu.CreatePointFont(90, _T("맑은 고딕"));
    m_fontContent.CreatePointFont(90, _T("맑은 고딕"));

    // 메뉴 버튼들의 위치와 크기를 정확하게 조정
    CRect clientRect;
    GetClientRect(&clientRect);

    // 사이드바 너비
    int sidebarWidth = 120;

    // 메뉴 버튼 위치 및 크기 조정
    int btnHeight = 36;
    int btnMargin = 15;
    int btnY = 100; // 첫 버튼 위치

    // 모든 메뉴 버튼을 동일한 크기와 위치로 정렬
    m_btnDashboard.MoveWindow(10, btnY, sidebarWidth - 20, btnHeight);
    m_btnProduction.MoveWindow(10, btnY + btnHeight + btnMargin, sidebarWidth - 20, btnHeight);
    m_btnEquipment.MoveWindow(10, btnY + (btnHeight + btnMargin) * 2, sidebarWidth - 20, btnHeight);
    m_btnSystem.MoveWindow(10, btnY + (btnHeight + btnMargin) * 3, sidebarWidth - 20, btnHeight);

    // 타이틀 라벨 위치 조정
    CWnd* pTitle = GetDlgItem(IDC_STATIC_MENU_TITLE);
    if (pTitle)
    {
        pTitle->MoveWindow(10, 40, sidebarWidth - 20, 30);
    }

    // 메뉴 버튼 폰트 설정
    m_btnDashboard.SetFont(&m_fontMenu);
    m_btnProduction.SetFont(&m_fontMenu);
    m_btnEquipment.SetFont(&m_fontMenu);
    m_btnSystem.SetFont(&m_fontMenu);

    // 위젯 버튼 폰트 설정
    m_btnProdStat.SetFont(&m_fontWidgetTitle);
    m_btnKPI.SetFont(&m_fontWidgetTitle);
    m_btnRealtime.SetFont(&m_fontWidgetTitle);
    m_btnAlert.SetFont(&m_fontWidgetTitle);

    // 현재 선택된 메뉴 강조
    m_btnDashboard.EnableWindow(FALSE);

    // 위젯 버튼 스타일 설정
    m_btnProdStat.ModifyStyle(0, BS_OWNERDRAW);
    m_btnKPI.ModifyStyle(0, BS_OWNERDRAW);
    m_btnRealtime.ModifyStyle(0, BS_OWNERDRAW);
    m_btnAlert.ModifyStyle(0, BS_OWNERDRAW);

    // 위젯 버튼들의 위치와 크기도 조정
    int contentStartX = sidebarWidth + 10;
    int contentWidth = clientRect.Width() - contentStartX - 20;
    int widgetWidth = (contentWidth - 10) / 2;
    int widgetHeight = (clientRect.Height() - 40) / 2;

    m_btnProdStat.MoveWindow(contentStartX, 20, widgetWidth, widgetHeight - 10);
    m_btnKPI.MoveWindow(contentStartX + widgetWidth + 10, 20, widgetWidth, widgetHeight - 10);
    m_btnRealtime.MoveWindow(contentStartX, widgetHeight + 20, widgetWidth, widgetHeight - 10);
    m_btnAlert.MoveWindow(contentStartX + widgetWidth + 10, widgetHeight + 20, widgetWidth, widgetHeight - 10);

    // 애니메이션 타이머 설정 (300ms마다 갱신)
    SetTimer(1001, 700, NULL);

    // 깜빡임 방지를 위한 WS_EX_COMPOSITED 스타일 추가
    ModifyStyleEx(0, WS_EX_COMPOSITED);

    return TRUE;
}

void CDashboardDlg::OnTimer(UINT_PTR nIDEvent)
{
    if (nIDEvent == 1001)
    {
        // 애니메이션 스텝 증가
        m_nAnimStep = (m_nAnimStep + 1) % 10;
        m_bBlinkState = !m_bBlinkState;

        // 위젯 영역 갱신 (각 위젯마다 별도 갱신)
        CRect rcWidget;

        // 전체 생산 현황, KPI, 실시간 데이터 위젯은 갱신
        m_btnProdStat.GetWindowRect(&rcWidget);
        ScreenToClient(&rcWidget);
        InvalidateRect(&rcWidget);

        m_btnKPI.GetWindowRect(&rcWidget);
        ScreenToClient(&rcWidget);
        InvalidateRect(&rcWidget);

        m_btnRealtime.GetWindowRect(&rcWidget);
        ScreenToClient(&rcWidget);
        InvalidateRect(&rcWidget);

        // 중요: 긴급 알림 위젯은 갱신하지 않음 (플리커 방지)
        // m_btnAlert 위젯은 타이머에 의한 갱신 제외
    }

    CDialogEx::OnTimer(nIDEvent);
}

void CDashboardDlg::OnPaint()
{
    CPaintDC dc(this);

    CRect rect;
    GetClientRect(&rect);

    // 사이드바 영역 계산
    int sidebarWidth = 120;
    CRect sidebarRect(0, 0, sidebarWidth, rect.Height());

    // 사이드바 배경 그리기
    dc.FillSolidRect(sidebarRect, RGB(50, 63, 79)); // 진한 남색

    // 제목 그리기
    CFont* pOldFont = dc.SelectObject(&m_fontTitle);
    dc.SetTextColor(RGB(255, 255, 255)); // 흰색 텍스트
    dc.SetBkMode(TRANSPARENT);

    // HIM MES 제목은 static 컨트롤로 이미 배치되어 있음

    // 버튼 강조 효과
    // 현재 선택된 메뉴 배경 그리기
    CRect btnRect;
    m_btnDashboard.GetWindowRect(&btnRect);
    ScreenToClient(&btnRect);

    // 선택된 버튼 왼쪽에 강조 바 그리기
    CRect accentBarRect(0, btnRect.top, 5, btnRect.bottom);
    dc.FillSolidRect(accentBarRect, RGB(41, 182, 246)); // 밝은 파란색

    dc.SelectObject(pOldFont);
    CDialogEx::OnPaint();
}
void CDashboardDlg::OnDestroy()
{
    KillTimer(1001);
    CDialogEx::OnDestroy();
}
HBRUSH CDashboardDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    UINT id = pWnd->GetDlgCtrlID();

    if (nCtlColor == CTLCOLOR_DLG)
    {
        return m_brushBg;  // 다이얼로그 배경색
    }

    // 버튼 배경색
    if (nCtlColor == CTLCOLOR_BTN)
    {
        if (id == IDC_BTN_DASHBOARD || id == IDC_BTN_PRODUCTION ||
            id == IDC_BTN_EQUIP || id == IDC_BTN_SYSTEM)
        {
            pDC->SetBkMode(TRANSPARENT);
            pDC->SetTextColor(RGB(255, 255, 255)); // 흰색 텍스트
            return m_brushSidebarBg;
        }
    }

    // 메뉴 제목 텍스트 색상
    if (nCtlColor == CTLCOLOR_STATIC && id == IDC_STATIC_MENU_TITLE)
    {
        pDC->SetTextColor(RGB(255, 255, 255)); // 흰색 텍스트
        pDC->SetBkMode(TRANSPARENT);
        return m_brushSidebarBg;
    }

    // 일반 Static 컨트롤 배경색
    if (nCtlColor == CTLCOLOR_STATIC)
    {
        pDC->SetBkMode(TRANSPARENT);
        return m_brushBg;
    }

    return CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
}

void CDashboardDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    // 위젯 버튼 그리기
    if (nIDCtl == IDC_BTN_PROD_STAT || nIDCtl == IDC_BTN_KPI ||
        nIDCtl == IDC_BTN_REALTIME || nIDCtl == IDC_BTN_ALERT)
    {
        CDC dc;
        dc.Attach(lpDrawItemStruct->hDC);

        // 버튼 영역
        CRect rect = lpDrawItemStruct->rcItem;
        BOOL isSelected = lpDrawItemStruct->itemState & ODS_SELECTED;

        // 버튼 텍스트 가져오기
        CString text;
        GetDlgItem(nIDCtl)->GetWindowText(text);

        // 헤더 색상 설정
        COLORREF headerColor;
        switch (nIDCtl)
        {
        case IDC_BTN_PROD_STAT:
            headerColor = RGB(0, 93, 255);  // 파란색
            break;
        case IDC_BTN_KPI:
            headerColor = RGB(255, 69, 0);  // 붉은색
            break;
        case IDC_BTN_REALTIME:
            headerColor = RGB(46, 139, 87); // 녹색
            break;
        case IDC_BTN_ALERT:
            headerColor = RGB(255, 140, 0); // 주황색
            break;
        default:
            headerColor = RGB(0, 93, 255);  // 기본 파란색
        }

        // 그림자 효과
        CRect shadowRect = rect;
        shadowRect.OffsetRect(3, 3);
        dc.FillSolidRect(shadowRect, RGB(230, 230, 230));

        // 버튼 배경
        dc.FillSolidRect(rect, RGB(255, 255, 255));

        // 버튼 테두리
        CPen pen(PS_SOLID, 1, RGB(230, 230, 230));
        CPen* pOldPen = dc.SelectObject(&pen);
        dc.Rectangle(rect);

        // 헤더 영역
        CRect headerRect = rect;
        headerRect.bottom = headerRect.top + 40;
        dc.FillSolidRect(headerRect, headerColor);

        // 텍스트 그리기
        dc.SetBkMode(TRANSPARENT);
        dc.SetTextColor(RGB(255, 255, 255)); // 흰색 텍스트

        // 타이틀 텍스트 영역
        CRect titleRect = headerRect;
        titleRect.left += 15; // 왼쪽 여백

        CFont* pOldFont = dc.SelectObject(&m_fontWidgetTitle);
        dc.DrawText(text, titleRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

        // 위젯 내용 영역
        CRect contentRect = rect;
        contentRect.top = headerRect.bottom + 10;
        contentRect.DeflateRect(20, 0, 20, 20);

        // 위젯 별 아이콘 그리기
        switch (nIDCtl)
        {
        case IDC_BTN_PROD_STAT:
            DrawProductionIcon(&dc, contentRect);
            break;
        case IDC_BTN_KPI:
            DrawKPIIcon(&dc, contentRect);
            break;
        case IDC_BTN_REALTIME:
            DrawRealtimeIcon(&dc, contentRect);
            break;
        case IDC_BTN_ALERT:
            DrawAlertIcon(&dc, contentRect);
            break;
        }

        // 리소스 복원
        dc.SelectObject(pOldPen);
        dc.SelectObject(pOldFont);
        dc.Detach();
        return;
    }

    CDialogEx::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

// 전체 생산 현황 - 컨베이어 벨트와 제품 아이콘
void CDashboardDlg::DrawProductionIcon(CDC* pDC, CRect rect)
{
    // 배경 영역 - 가운데 정렬 위해 너비 계산
    int iconWidth = 200;
    int iconHeight = 80;

    // 가운데 배치 계산
    int centerX = (rect.left + rect.right) / 2;
    int centerY = (rect.top + rect.bottom - 40) / 2; // 텍스트 공간 고려

    CRect iconRect(
        centerX - iconWidth / 2,
        centerY - iconHeight / 2,
        centerX + iconWidth / 2,
        centerY + iconHeight / 2
    );

    // 컨베이어 벨트 그리기
    CBrush beltBrush(RGB(220, 220, 220));
    CBrush* pOldBrush = pDC->SelectObject(&beltBrush);

    CRect topBelt(iconRect.left, iconRect.top, iconRect.right, iconRect.top + 8);
    CRect bottomBelt(iconRect.left, iconRect.bottom - 8, iconRect.right, iconRect.bottom);

    pDC->Rectangle(topBelt);
    pDC->Rectangle(bottomBelt);

    // 지지대 그리기
    CBrush supportBrush(RGB(0, 93, 255));
    pDC->SelectObject(&supportBrush);

    CRect leftSupport(iconRect.left + 10, topBelt.bottom, iconRect.left + 20, bottomBelt.top);
    CRect rightSupport(iconRect.right - 20, topBelt.bottom, iconRect.right - 10, bottomBelt.top);

    pDC->Rectangle(leftSupport);
    pDC->Rectangle(rightSupport);

    // 상자 그리기 (애니메이션 적용)
    for (int i = 0; i < 4; i++) {
        // 애니메이션 위치 계산
        int boxPos = (i * 40 + m_nAnimStep * 4) % (iconRect.Width() - 30);

        CRect box(iconRect.left + 5 + boxPos, topBelt.bottom + 5,
            iconRect.left + 25 + boxPos, bottomBelt.top - 5);

        // 파란색으로 상자 채우기
        pDC->FillSolidRect(box, RGB(0, 93, 255));
        pDC->Rectangle(box);
    }

    // 생산 현황 정보 표시 추가
    pDC->SelectObject(&m_fontContent);
    pDC->SetTextColor(RGB(60, 60, 60));

    // 현재 생산 상태 정보 표시
    CRect textRect1(rect.left, iconRect.bottom + 10, rect.right, iconRect.bottom + 30);
    pDC->DrawText(_T("라인 A: 생산량 78/120 (65%)"), textRect1, DT_CENTER | DT_SINGLELINE);

    CRect textRect2(rect.left, textRect1.bottom, rect.right, textRect1.bottom + 20);

    // 상태에 따라 색상 변경
    if (m_bBlinkState) {
        pDC->SetTextColor(RGB(200, 0, 0)); // 빨간색으로 깜빡임
    }
    else {
        pDC->SetTextColor(RGB(60, 60, 60));
    }
    pDC->DrawText(_T("라인 B: 생산량 45/80 (56%) - 지연"), textRect2, DT_CENTER | DT_SINGLELINE);

    pDC->SelectObject(pOldBrush);
}
// 핵심 성과 지표 - 게이지와 차트 아이콘
void CDashboardDlg::DrawKPIIcon(CDC* pDC, CRect rect)
{
    // 게이지 위치 계산 - 가운데 배치
    int gaugeSize = 120;
    int centerX = (rect.left + rect.right) / 2;
    int centerY = (rect.top + rect.bottom - 60) / 2; // 텍스트 공간 고려

    CRect gaugeBg(
        centerX - gaugeSize / 2,
        centerY - gaugeSize / 2,
        centerX + gaugeSize / 2,
        centerY + gaugeSize / 2
    );

    CPoint center(centerX, centerY);
    int radius = gaugeSize / 2;

    // 게이지 배경 그리기
    CPen grayPen(PS_SOLID, 2, RGB(200, 200, 200));
    CPen* pOldPen = pDC->SelectObject(&grayPen);

    pDC->Arc(center.x - radius, center.y - radius,
        center.x + radius, center.y + radius,
        center.x + radius, center.y,
        center.x - radius, center.y);

    // 게이지 채우기 (92% 정도로 표시) - 애니메이션 효과 추가
    CPen redPen(PS_SOLID, 3, RGB(255, 69, 0));
    pDC->SelectObject(&redPen);

    // 애니메이션에 따라 약간 움직이는 게이지
    double angleOffset = (m_nAnimStep % 3 - 1) * 0.03; // -0.03 ~ +0.03 라디안
    double baseAngle = 3.14 * 0.15 + angleOffset; // 기본 위치 (약 27도)

    pDC->Arc(center.x - radius, center.y - radius,
        center.x + radius, center.y + radius,
        center.x + radius, center.y,
        center.x - (int)(radius * 0.1), center.y - (int)(radius * 0.9));

    // 눈금 표시
    pDC->MoveTo(center.x - radius, center.y);
    pDC->LineTo(center.x - radius + 10, center.y);

    pDC->MoveTo(center.x + radius, center.y);
    pDC->LineTo(center.x + radius - 10, center.y);

    pDC->MoveTo(center.x, center.y - radius);
    pDC->LineTo(center.x, center.y - radius + 10);

    // 바늘 그리기 (좌우 움직임 추가)
    CPen needlePen(PS_SOLID, 2, RGB(255, 69, 0));
    pDC->SelectObject(&needlePen);

    // 화살표 위치 계산 및 그리기 - 애니메이션 효과 강화
    double needleAngle = baseAngle + angleOffset;

    pDC->MoveTo(center.x, center.y);
    pDC->LineTo(center.x + (int)(radius * 0.7 * cos(needleAngle)),
        center.y - (int)(radius * 0.7 * sin(needleAngle)));

    // 중앙 원 그리기
    CBrush centerBrush(RGB(255, 69, 0));
    CBrush* pOldBrush = pDC->SelectObject(&centerBrush);
    pDC->Ellipse(center.x - 5, center.y - 5, center.x + 5, center.y + 5);

    // KPI 값 표시
    CRect valueRect(rect.left, center.y + radius + 10, rect.right, center.y + radius + 30);
    pDC->SetTextColor(RGB(60, 60, 60));

    // 값에 애니메이션 효과 추가
    CString valueText;
    int displayValue = 92 + (m_nAnimStep % 3 - 1); // 91~93 사이 변동
    valueText.Format(_T("효율: %d%%"), displayValue);
    pDC->DrawText(valueText, valueRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    // 추가 KPI 정보
    CRect infoRect(rect.left, valueRect.bottom, rect.right, valueRect.bottom + 20);
    pDC->DrawText(_T("품질: 88% | 가동률: 67%"), infoRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    pDC->SelectObject(pOldPen);
    pDC->SelectObject(pOldBrush);
}

// 실시간 데이터 분석 - 데이터 그래프와 분석 아이콘
void CDashboardDlg::DrawRealtimeIcon(CDC* pDC, CRect rect)
{
    // 데이터 차트 배경 - 가운데 배치
    int chartWidth = 280;
    int chartHeight = 100;
    int centerX = (rect.left + rect.right) / 2;
    int centerY = (rect.top + rect.bottom - 40) / 2; // 텍스트 공간 고려

    CRect chartBg(
        centerX - chartWidth / 2,
        centerY - chartHeight / 2,
        centerX + chartWidth / 2,
        centerY + chartHeight / 2
    );

    pDC->FillSolidRect(chartBg, RGB(245, 245, 245));
    pDC->Rectangle(chartBg);

    // X, Y축 그리기
    CPen axisPen(PS_SOLID, 1, RGB(150, 150, 150));
    CPen* pOldPen = pDC->SelectObject(&axisPen);

    // X축
    pDC->MoveTo(chartBg.left + 5, chartBg.bottom - 5);
    pDC->LineTo(chartBg.right - 5, chartBg.bottom - 5);

    // Y축
    pDC->MoveTo(chartBg.left + 5, chartBg.bottom - 5);
    pDC->LineTo(chartBg.left + 5, chartBg.top + 5);

    // 그래프 데이터 포인트 (실시간 효과를 위해 애니메이션 변수 사용)
    int baseDataPoints[] = { 60, 45, 70, 55, 80, 65, 75, 50 };
    int pointCount = sizeof(baseDataPoints) / sizeof(int);

    // 애니메이션에 따라 더 큰 변동 추가
    int variation = (m_nAnimStep % 5 - 2) * 3; // -6 ~ +6 사이 변동

    // 꺾은선 그래프 그리기
    CPen graphPen(PS_SOLID, 2, RGB(46, 139, 87)); // 녹색
    pDC->SelectObject(&graphPen);

    int xStep = (chartBg.Width() - 15) / (pointCount - 1);
    int yBase = chartBg.bottom - 5;

    // 데이터 포인트 조정 (모든 포인트에 변동 적용해서 움직임 증가)
    int dataPoints[8];
    for (int i = 0; i < pointCount; i++) {
        // 각 포인트마다 다른 변동폭 적용 (더 자연스러운 움직임)
        int pointVariation = variation * ((i % 3) - 1); // -6, 0, +6 주기로 변동
        dataPoints[i] = baseDataPoints[i] + pointVariation;
    }

    // 선 그리기
    for (int i = 0; i < pointCount - 1; i++) {
        pDC->MoveTo(chartBg.left + 5 + i * xStep, yBase - dataPoints[i]);
        pDC->LineTo(chartBg.left + 5 + (i + 1) * xStep, yBase - dataPoints[i + 1]);
    }

    // 데이터 포인트 표시
    for (int i = 0; i < pointCount; i++) {
        CRect point(
            chartBg.left + 5 + i * xStep - 3,
            yBase - dataPoints[i] - 3,
            chartBg.left + 5 + i * xStep + 3,
            yBase - dataPoints[i] + 3
        );

        // 마지막 포인트는 깜빡이는 효과 추가
        if (i == pointCount - 1) {
            // 깜빡임 상태에 따라 색상 변경
            if (m_bBlinkState) {
                CBrush highlightBrush(RGB(255, 0, 0)); // 빨간색
                pDC->SelectObject(&highlightBrush);
                pDC->Ellipse(point);
            }
            else {
                CBrush normalBrush(RGB(46, 139, 87)); // 녹색
                pDC->SelectObject(&normalBrush);
                pDC->Ellipse(point);
            }
        }
        else {
            CBrush pointBrush(RGB(46, 139, 87)); // 녹색
            pDC->SelectObject(&pointBrush);
            pDC->Ellipse(point);
        }
    }

    // 실시간 데이터 표시 개선
    CRect infoRect1(rect.left + 5, chartBg.bottom + 8, rect.right - 5, chartBg.bottom + 28);
    pDC->SetTextColor(RGB(46, 139, 87));

    // 애니메이션에 따라 값 변경
    CString infoText1;
    infoText1.Format(_T("현재 생산율: %d%%"), 92 + (m_nAnimStep % 3 - 1));
    pDC->DrawText(infoText1, infoRect1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    CRect infoRect2(rect.left + 5, infoRect1.bottom + 2, rect.right - 5, infoRect1.bottom + 22);
    pDC->SetTextColor(RGB(60, 60, 60));

    // 시간 정보 표시 (실제 시스템 시간 사용)
    SYSTEMTIME time;
    GetLocalTime(&time);
    CString infoText2;
    infoText2.Format(_T("마지막 업데이트: %02d:%02d:%02d"), time.wHour, time.wMinute, time.wSecond);
    pDC->DrawText(infoText2, infoRect2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    pDC->SelectObject(pOldPen);
}

// 긴급 알림 - 경고 아이콘과 알림 목록
void CDashboardDlg::DrawAlertIcon(CDC* pDC, CRect rect)
{
    // 배경색 변경 (어두운 빨간색으로 고정)
    CRect alertBg(rect.left + 20, rect.top + 10, rect.right - 20, rect.bottom - 30);
    pDC->FillSolidRect(alertBg, RGB(180, 0, 0));
    pDC->Rectangle(alertBg);

    // 경고 삼각형 그리기 - 가운데 배치
    int triangleSize = 80;
    int centerX = (rect.left + rect.right) / 2;
    int triangleY = rect.top + 50; // 상단에 위치

    CRect alertRect(
        centerX - triangleSize / 2,
        triangleY,
        centerX + triangleSize / 2,
        triangleY + triangleSize
    );

    // 삼각형 좌표 계산
    CPoint points[3];
    points[0].x = (alertRect.left + alertRect.right) / 2;
    points[0].y = alertRect.top;
    points[1].x = alertRect.left;
    points[1].y = alertRect.bottom;
    points[2].x = alertRect.right;
    points[2].y = alertRect.bottom;

    // 삼각형 그리기 (주황색)
    CBrush triangleBrush(RGB(255, 140, 0));
    CBrush* pOldBrush = pDC->SelectObject(&triangleBrush);

    CPen orangePen(PS_SOLID, 2, RGB(255, 140, 0));
    CPen* pOldPen = pDC->SelectObject(&orangePen);

    pDC->Polygon(points, 3);

    // 느낌표 그리기
    pDC->SetTextColor(RGB(255, 255, 255));
    CFont exclamationFont;
    exclamationFont.CreatePointFont(220, _T("Arial Bold"));
    CFont* pOldFont = pDC->SelectObject(&exclamationFont);

    CRect excRect = alertRect;
    excRect.bottom -= 10;
    pDC->DrawText(_T("!"), excRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    // 알림 카운터 (고정된 위치와 색상)
    CRect countCircle(alertRect.right - 10, alertRect.top, alertRect.right + 10, alertRect.top + 20);
    CBrush counterBrush(RGB(255, 50, 50));
    pDC->SelectObject(&counterBrush);
    pDC->Ellipse(countCircle);

    pDC->SetTextColor(RGB(255, 255, 255));
    pDC->SelectObject(&m_fontContent);
    pDC->DrawText(_T("3"), countCircle, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    // 알림 목록 텍스트 (노란색)
    pDC->SetTextColor(RGB(255, 255, 150));

    CRect listRect = alertBg;
    listRect.top = alertRect.bottom + 20;

    CRect item1(listRect.left + 15, listRect.top, listRect.right - 15, listRect.top + 20);
    CRect item2(listRect.left + 15, listRect.top + 25, listRect.right - 15, listRect.top + 45);
    CRect item3(listRect.left + 15, listRect.top + 50, listRect.right - 15, listRect.top + 70);

    // 목록 항목 앞 원형 기호 (밝은 노란색)
    CBrush bulletBrush(RGB(255, 255, 0));
    pDC->SelectObject(&bulletBrush);

    // 모든 불릿 포인트 고정 위치
    pDC->Ellipse(item1.left - 10, item1.top + 6, item1.left - 2, item1.top + 14);
    pDC->Ellipse(item2.left - 10, item2.top + 6, item2.left - 2, item2.top + 14);
    pDC->Ellipse(item3.left - 10, item3.top + 6, item3.left - 2, item3.top + 14);

    // 알림 텍스트 (더 두꺼운 폰트로 가독성 향상)
    CFont boldFont;
    boldFont.CreatePointFont(95, _T("맑은 고딕 Bold"));
    pDC->SelectObject(&boldFont);

    // 텍스트에 그림자 효과 추가 (가독성 향상)
    pDC->SetTextColor(RGB(100, 0, 0));
    CRect shadowRect1 = item1; shadowRect1.OffsetRect(1, 1);
    CRect shadowRect2 = item2; shadowRect2.OffsetRect(1, 1);
    CRect shadowRect3 = item3; shadowRect3.OffsetRect(1, 1);
    pDC->DrawText(_T("설비 A-3 과열 경고"), shadowRect1, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
    pDC->DrawText(_T("자재 B-7 재고 부족 임박"), shadowRect2, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
    pDC->DrawText(_T("정기 점검 일정 알림"), shadowRect3, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

    // 실제 텍스트 (밝은 노란색)
    pDC->SetTextColor(RGB(255, 255, 150));
    pDC->DrawText(_T("설비 A-3 과열 경고"), item1, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
    pDC->DrawText(_T("자재 B-7 재고 부족 임박"), item2, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
    pDC->DrawText(_T("정기 점검 일정 알림"), item3, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

    // 정보 표시
    CString strInfo = _T("3개의 긴급 알림이 있습니다");
    CRect textRect(rect.left, alertBg.bottom + 5, rect.right, rect.bottom);
    pDC->SetTextColor(RGB(60, 60, 60));
    pDC->DrawText(strInfo, textRect, DT_CENTER | DT_TOP | DT_SINGLELINE);

    pDC->SelectObject(pOldBrush);
    pDC->SelectObject(pOldPen);
    pDC->SelectObject(pOldFont);
    exclamationFont.DeleteObject();
    boldFont.DeleteObject();
}
