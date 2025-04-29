// ProductionDlg.cpp
#include "pch.h"
#include "ProductionDlg.h"
#include "DashboardDlg.h"
#include "EquipDlg.h"
#include "SystemDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include <math.h>

IMPLEMENT_DYNAMIC(CProductionDlg, CDialogEx)

CProductionDlg::CProductionDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_PRODUCTION_DIALOG, pParent), m_nAnimStep(0), m_bBlinkState(false)
{
}

CProductionDlg::~CProductionDlg()
{
    // 생성한 GDI 객체 정리
    m_brushBg.DeleteObject();
    m_brushWidgetBg.DeleteObject();
    m_brushSidebarBg.DeleteObject();
    m_fontTitle.DeleteObject();
    m_fontWidgetTitle.DeleteObject();
    m_fontMenu.DeleteObject();
    m_fontContent.DeleteObject();
}

void CProductionDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_BTN_DASHBOARD, m_btnDashboard);
    DDX_Control(pDX, IDC_BTN_PRODUCTION, m_btnProduction);
    DDX_Control(pDX, IDC_BTN_EQUIP, m_btnEquipment);
    DDX_Control(pDX, IDC_BTN_SYSTEM, m_btnSystem);

    // 생산관리 위젯 버튼 추가
    DDX_Control(pDX, IDC_BTN_PLAN, m_btnPlan);
    DDX_Control(pDX, IDC_BTN_SCHEDULE, m_btnSchedule);
    DDX_Control(pDX, IDC_BTN_LIVE_STATUS, m_btnLiveStatus);
    DDX_Control(pDX, IDC_BTN_TRACK, m_btnTrack);
}

BEGIN_MESSAGE_MAP(CProductionDlg, CDialogEx)
    ON_BN_CLICKED(IDC_BTN_DASHBOARD, &CProductionDlg::OnBnClickedBtnDashboard)
    ON_BN_CLICKED(IDC_BTN_PRODUCTION, &CProductionDlg::OnBnClickedBtnProduction)
    ON_BN_CLICKED(IDC_BTN_EQUIP, &CProductionDlg::OnBnClickedBtnEquip)
    ON_BN_CLICKED(IDC_BTN_SYSTEM, &CProductionDlg::OnBnClickedBtnSystem)
    ON_BN_CLICKED(IDC_BTN_PLAN, &CProductionDlg::OnBnClickedBtnPlan)
    ON_BN_CLICKED(IDC_BTN_SCHEDULE, &CProductionDlg::OnBnClickedBtnSchedule)
    ON_BN_CLICKED(IDC_BTN_LIVE_STATUS, &CProductionDlg::OnBnClickedBtnLiveStatus)
    ON_BN_CLICKED(IDC_BTN_TRACK, &CProductionDlg::OnBnClickedBtnTrack)
    ON_WM_CTLCOLOR()
    ON_WM_PAINT()
    ON_WM_DRAWITEM()
    ON_WM_TIMER()
    ON_WM_DESTROY()
END_MESSAGE_MAP()

void CProductionDlg::OnBnClickedBtnDashboard()
{
    KillTimer(1002);
    this->EndDialog(IDCANCEL);
    CDashboardDlg dlg;
    dlg.DoModal();
}

void CProductionDlg::OnBnClickedBtnProduction()
{
    // 생산관리 버튼은 현재 화면이므로 아무 동작 안함
}

void CProductionDlg::OnBnClickedBtnEquip()
{
    KillTimer(1002);
    this->EndDialog(IDCANCEL);
    CEquipDlg dlg;
    dlg.DoModal();
}

void CProductionDlg::OnBnClickedBtnSystem()
{
    KillTimer(1002);
    this->EndDialog(IDCANCEL);
    CSystemDlg dlg;
    dlg.DoModal();
}

void CProductionDlg::OnBnClickedBtnPlan()
{
    // 생산 계획 수립 버튼 클릭 처리
    MessageBox(_T("생산 계획 수립 화면으로 이동합니다."), _T("알림"), MB_OK | MB_ICONINFORMATION);
    // 여기에 실제 기능 구현
}

void CProductionDlg::OnBnClickedBtnSchedule()
{
    // 작업 지시 및 일정 관리 버튼 클릭 처리
    MessageBox(_T("작업 지시 및 일정 관리 화면으로 이동합니다."), _T("알림"), MB_OK | MB_ICONINFORMATION);
    // 여기에 실제 기능 구현
}

void CProductionDlg::OnBnClickedBtnLiveStatus()
{
    // 실시간 생산 진행 상황 버튼 클릭 처리
    MessageBox(_T("실시간 생산 진행 상황 화면으로 이동합니다."), _T("알림"), MB_OK | MB_ICONINFORMATION);
    // 여기에 실제 기능 구현
}

void CProductionDlg::OnBnClickedBtnTrack()
{
    // 생산 실적 추적 버튼 클릭 처리
    MessageBox(_T("생산 실적 추적 화면으로 이동합니다."), _T("알림"), MB_OK | MB_ICONINFORMATION);
    // 여기에 실제 기능 구현
}

BOOL CProductionDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // 다이얼로그 제목 설정
    SetWindowText(_T("생산관리 - HIM MES"));

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
    m_btnPlan.SetFont(&m_fontWidgetTitle);
    m_btnSchedule.SetFont(&m_fontWidgetTitle);
    m_btnLiveStatus.SetFont(&m_fontWidgetTitle);
    m_btnTrack.SetFont(&m_fontWidgetTitle);

    // 현재 선택된 메뉴 강조
    m_btnProduction.EnableWindow(FALSE);

    // 위젯 버튼 스타일 설정
    m_btnPlan.ModifyStyle(0, BS_OWNERDRAW);
    m_btnSchedule.ModifyStyle(0, BS_OWNERDRAW);
    m_btnLiveStatus.ModifyStyle(0, BS_OWNERDRAW);
    m_btnTrack.ModifyStyle(0, BS_OWNERDRAW);

    // 위젯 버튼들의 위치와 크기도 조정
    int contentStartX = sidebarWidth + 10;
    int contentWidth = clientRect.Width() - contentStartX - 20;
    int widgetWidth = (contentWidth - 10) / 2;
    int widgetHeight = (clientRect.Height() - 40) / 2;

    m_btnPlan.MoveWindow(contentStartX, 20, widgetWidth, widgetHeight - 10);
    m_btnSchedule.MoveWindow(contentStartX + widgetWidth + 10, 20, widgetWidth, widgetHeight - 10);
    m_btnLiveStatus.MoveWindow(contentStartX, widgetHeight + 20, widgetWidth, widgetHeight - 10);
    m_btnTrack.MoveWindow(contentStartX + widgetWidth + 10, widgetHeight + 20, widgetWidth, widgetHeight - 10);

    // 애니메이션 타이머 설정 (700ms마다 갱신)
    SetTimer(1002, 700, NULL);

    // 깜빡임 방지를 위한 WS_EX_COMPOSITED 스타일 추가
    ModifyStyleEx(0, WS_EX_COMPOSITED);

    return TRUE;
}

void CProductionDlg::OnTimer(UINT_PTR nIDEvent)
{
    if (nIDEvent == 1002)
    {
        // 애니메이션 스텝 증가
        m_nAnimStep = (m_nAnimStep + 1) % 10;
        m_bBlinkState = !m_bBlinkState;

        // 위젯 영역 갱신 (각 위젯마다 별도 갱신)
        CRect rcWidget;

        // 모든 위젯 갱신
        m_btnPlan.GetWindowRect(&rcWidget);
        ScreenToClient(&rcWidget);
        InvalidateRect(&rcWidget);

        m_btnSchedule.GetWindowRect(&rcWidget);
        ScreenToClient(&rcWidget);
        InvalidateRect(&rcWidget);

        m_btnLiveStatus.GetWindowRect(&rcWidget);
        ScreenToClient(&rcWidget);
        InvalidateRect(&rcWidget);

        m_btnTrack.GetWindowRect(&rcWidget);
        ScreenToClient(&rcWidget);
        InvalidateRect(&rcWidget);
    }

    CDialogEx::OnTimer(nIDEvent);
}

void CProductionDlg::OnDestroy()
{
    KillTimer(1002);
    CDialogEx::OnDestroy();
}

void CProductionDlg::OnPaint()
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
    m_btnProduction.GetWindowRect(&btnRect);
    ScreenToClient(&btnRect);

    // 선택된 버튼 왼쪽에 강조 바 그리기
    CRect accentBarRect(0, btnRect.top, 5, btnRect.bottom);
    dc.FillSolidRect(accentBarRect, RGB(41, 182, 246)); // 밝은 파란색

    dc.SelectObject(pOldFont);
    CDialogEx::OnPaint();
}

HBRUSH CProductionDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

void CProductionDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    // 위젯 버튼 그리기
    if (nIDCtl == IDC_BTN_PLAN || nIDCtl == IDC_BTN_SCHEDULE ||
        nIDCtl == IDC_BTN_LIVE_STATUS || nIDCtl == IDC_BTN_TRACK)
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
        case IDC_BTN_PLAN:
            headerColor = RGB(30, 144, 255);  // 도지 블루
            break;
        case IDC_BTN_SCHEDULE:
            headerColor = RGB(60, 179, 113);  // 미디엄 시그린
            break;
        case IDC_BTN_LIVE_STATUS:
            headerColor = RGB(106, 90, 205); // 슬레이트 블루
            break;
        case IDC_BTN_TRACK:
            headerColor = RGB(255, 120, 0);   // 다크 오렌지
            break;
        default:
            headerColor = RGB(0, 93, 255);    // 기본 파란색
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
        case IDC_BTN_PLAN:
            DrawPlanIcon(&dc, contentRect);
            break;
        case IDC_BTN_SCHEDULE:
            DrawScheduleIcon(&dc, contentRect);
            break;
        case IDC_BTN_LIVE_STATUS:
            DrawLiveStatusIcon(&dc, contentRect);
            break;
        case IDC_BTN_TRACK:
            DrawTrackIcon(&dc, contentRect);
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

// 생산 계획 수립 아이콘 그리기
void CProductionDlg::DrawPlanIcon(CDC* pDC, CRect rect)
{
    // 월간 계획표 & 일정 그래픽
    int centerX = (rect.left + rect.right) / 2;
    int centerY = (rect.top + rect.bottom - 40) / 2;

    // 배경 패널
    CRect panelRect(rect.left + 15, rect.top + 10, rect.right - 15, rect.bottom - 30);
    pDC->FillSolidRect(panelRect, RGB(248, 248, 252));
    pDC->Rectangle(panelRect);

    // 월 타이틀
    CRect monthTitleRect(panelRect.left, panelRect.top, panelRect.right, panelRect.top + 25);
    pDC->FillSolidRect(monthTitleRect, RGB(240, 240, 245));

    CFont titleFont;
    titleFont.CreateFont(16, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));
    CFont* pOldFont = pDC->SelectObject(&titleFont);

    pDC->SetTextColor(RGB(30, 80, 150));
    pDC->DrawText(_T("2025년 4월 생산 계획"), monthTitleRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    // 달력 그리드
    int calendarWidth = panelRect.Width() - 30;
    int calendarHeight = panelRect.Height() - 70;
    int calendarLeft = panelRect.left + 15;
    int calendarTop = monthTitleRect.bottom + 10;

    CRect calendarRect(calendarLeft, calendarTop,
        calendarLeft + calendarWidth,
        calendarTop + calendarHeight);

    // 그리드 배경
    pDC->FillSolidRect(calendarRect, RGB(255, 255, 255));
    pDC->Rectangle(calendarRect);

    // 요일 헤더
    int dayWidth = calendarWidth / 7;
    int headerHeight = 25;
    CRect dayHeaderRect(calendarRect.left, calendarRect.top,
        calendarRect.right, calendarRect.top + headerHeight);
    pDC->FillSolidRect(dayHeaderRect, RGB(230, 240, 250));

    // 요일 이름
    CString dayNames[7] = { _T("일"), _T("월"), _T("화"), _T("수"), _T("목"), _T("금"), _T("토") };
    CFont dayFont;
    dayFont.CreateFont(14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));
    pDC->SelectObject(&dayFont);

    for (int i = 0; i < 7; i++) {
        CRect dayRect(calendarRect.left + i * dayWidth, dayHeaderRect.top,
            calendarRect.left + (i + 1) * dayWidth, dayHeaderRect.bottom);

        // 주말은 빨간색
        if (i == 0 || i == 6) {
            pDC->SetTextColor(RGB(200, 0, 0));
        }
        else {
            pDC->SetTextColor(RGB(30, 30, 30));
        }

        pDC->DrawText(dayNames[i], dayRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }

    // 날짜 그리드
    int rows = 5; // 5주
    int cellHeight = (calendarHeight - headerHeight) / rows;

    // 세로 구분선
    for (int i = 1; i < 7; i++) {
        int x = calendarRect.left + i * dayWidth;
        pDC->MoveTo(x, calendarRect.top);
        pDC->LineTo(x, calendarRect.bottom);
    }

    // 가로 구분선
    for (int i = 1; i <= rows; i++) {
        int y = dayHeaderRect.bottom + i * cellHeight;
        pDC->MoveTo(calendarRect.left, y);
        pDC->LineTo(calendarRect.right, y);
    }

    // 날짜 표시 (4월 기준)
    int daysInMonth = 30; // 4월은 30일
    int startDay = 1; // 4월 1일은 월요일(1)로 가정
    int dayOfMonth = 1;

    CFont dateFont;
    dateFont.CreateFont(14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));
    pDC->SelectObject(&dateFont);

    // 계획된 생산일 (예시)
    bool productionDays[31] = { false };
    productionDays[2] = true;  // 3일
    productionDays[7] = true;  // 8일
    productionDays[12] = true; // 13일
    productionDays[17] = true; // 18일
    productionDays[22] = true; // 23일
    productionDays[27] = true; // 28일

    // 오늘 날짜 (예시)
    int currentDay = 15;

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < 7; col++) {
            if ((row == 0 && col < startDay) || dayOfMonth > daysInMonth) {
                continue; // 4월 시작 전이거나 4월 끝난 후
            }

            int cellLeft = calendarRect.left + col * dayWidth;
            int cellTop = dayHeaderRect.bottom + row * cellHeight;
            CRect cellRect(cellLeft, cellTop, cellLeft + dayWidth, cellTop + cellHeight);

            // 날짜 텍스트
            CString dateText;
            dateText.Format(_T("%d"), dayOfMonth);

            // 주말은 빨간색
            if (col == 0 || col == 6) {
                pDC->SetTextColor(RGB(200, 0, 0));
            }
            else {
                pDC->SetTextColor(RGB(0, 0, 0));
            }

            // 날짜 위치
            CRect dateRect(cellRect);
            dateRect.DeflateRect(3, 3);
            pDC->DrawText(dateText, dateRect, DT_LEFT | DT_TOP | DT_SINGLELINE);

            // 오늘 날짜 하이라이트
            if (dayOfMonth == currentDay) {
                CPen highlightPen(PS_SOLID, 2, RGB(30, 144, 255));
                CPen* pOldPen = pDC->SelectObject(&highlightPen);

                CRect todayRect = cellRect;
                todayRect.DeflateRect(2, 2);

                // 깜빡이는 효과
                if (m_bBlinkState) {
                    CBrush highlightBrush(RGB(230, 240, 255));
                    CBrush* pOldBrush = pDC->SelectObject(&highlightBrush);
                    pDC->Rectangle(todayRect);
                    pDC->SelectObject(pOldBrush);
                }
                else {
                    pDC->Rectangle(todayRect);
                }

                pDC->SelectObject(pOldPen);
            }

            // 계획된 생산일 표시
            if (productionDays[dayOfMonth - 1]) {
                int indicatorSize = 10;
                CRect indicatorRect(
                    cellRect.right - indicatorSize - 5,
                    cellRect.bottom - indicatorSize - 5,
                    cellRect.right - 5,
                    cellRect.bottom - 5
                );

                // 깜빡이는 효과 (현재 선택된 날짜만)
                COLORREF indicatorColor;
                if (dayOfMonth == currentDay && m_bBlinkState) {
                    indicatorColor = RGB(255, 0, 0);
                }
                else {
                    indicatorColor = RGB(30, 144, 255);
                }

                pDC->FillSolidRect(indicatorRect, indicatorColor);
                pDC->Rectangle(indicatorRect);
            }

            dayOfMonth++;
        }
    }

    // 범례
    CRect legendRect(panelRect.left + 20, calendarRect.bottom + 5,
        panelRect.right - 20, panelRect.bottom - 5);

    pDC->SetTextColor(RGB(30, 80, 150));
    CFont legendFont;
    legendFont.CreateFont(14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));
    pDC->SelectObject(&legendFont);

    // 계획된 날짜 범례
    CRect blueDotRect(legendRect.left, legendRect.top + 2,
        legendRect.left + 10, legendRect.top + 12);
    pDC->FillSolidRect(blueDotRect, RGB(30, 144, 255));
    pDC->Rectangle(blueDotRect);

    pDC->DrawText(_T("생산 계획일 (총 6일)"),
        CRect(blueDotRect.right + 5, legendRect.top,
            legendRect.right, legendRect.bottom),
        DT_LEFT | DT_VCENTER | DT_SINGLELINE);

    pDC->SelectObject(pOldFont);
    titleFont.DeleteObject();
    dayFont.DeleteObject();
    dateFont.DeleteObject();
    legendFont.DeleteObject();
}
// 작업 지시 및 일정 관리 아이콘 그리기
void CProductionDlg::DrawScheduleIcon(CDC* pDC, CRect rect)
{
    // 헤더와 패널 그리기
    int centerX = (rect.left + rect.right) / 2;
    int centerY = (rect.top + rect.bottom - 40) / 2;

    // 패널 배경
    CRect panelRect(rect.left + 10, rect.top + 5, rect.right - 10, rect.bottom - 20);
    pDC->FillSolidRect(panelRect, RGB(250, 250, 255));
    pDC->Rectangle(panelRect);

    // 헤더 영역
    CRect headerRect(panelRect.left, panelRect.top, panelRect.right, panelRect.top + 25);
    pDC->FillSolidRect(headerRect, RGB(60, 179, 113));

    CFont headerFont;
    headerFont.CreateFont(15, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));
    CFont* pOldFont = pDC->SelectObject(&headerFont);

    pDC->SetTextColor(RGB(255, 255, 255));

    // 간트 차트 영역
    CRect chartRect(panelRect.left + 10, headerRect.bottom + 10,
        panelRect.right - 10, panelRect.bottom - 30);
    pDC->FillSolidRect(chartRect, RGB(255, 255, 255));
    pDC->Rectangle(chartRect);

    // 작업 목록 영역
    int rowCount = 4;
    int rowHeight = chartRect.Height() / rowCount;
    int taskWidth = 50;

    // 헤더 영역 추가
    CRect taskHeaderRect(chartRect.left, chartRect.top - 25,
        chartRect.left + taskWidth, chartRect.top);
    pDC->FillSolidRect(taskHeaderRect, RGB(46, 139, 87)); // 진한 녹색 헤더

    pDC->SetTextColor(RGB(255, 255, 255));
    pDC->DrawText(_T("작업"), taskHeaderRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    // 진행률 헤더 영역 추가
    CRect statusHeaderRect(chartRect.left + taskWidth, chartRect.top - 25,
        chartRect.right, chartRect.top);
    pDC->FillSolidRect(statusHeaderRect, RGB(46, 139, 87)); // 진한 녹색 헤더
    pDC->DrawText(_T("상태"), statusHeaderRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    // 작업 이름 컬럼
    for (int i = 0; i < rowCount; i++) {
        CRect taskRect(chartRect.left, chartRect.top + i * rowHeight,
            chartRect.left + taskWidth, chartRect.top + (i + 1) * rowHeight);

        // 작업 이름 배경색 (번갈아가며)
        if (i % 2 == 0) {
            pDC->FillSolidRect(taskRect, RGB(230, 250, 230)); // 연한 녹색 배경
        }
        else {
            pDC->FillSolidRect(taskRect, RGB(245, 255, 245)); // 더 연한 녹색 배경
        }

        // 테두리 추가
        CPen borderPen(PS_SOLID, 1, RGB(46, 139, 87)); // 진한 녹색 테두리
        CPen* pOldPen = pDC->SelectObject(&borderPen);
        pDC->Rectangle(taskRect);
        pDC->SelectObject(pOldPen);

        // 작업 이름 텍스트
        CString taskName;
        taskName.Format(_T("작업 %d"), i + 1);

        CFont taskFont;
        taskFont.CreateFont(14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));
        pDC->SelectObject(&taskFont);

        pDC->SetTextColor(RGB(50, 100, 50)); // 진한 녹색 텍스트
        pDC->DrawText(taskName, taskRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

        taskFont.DeleteObject();
    }

    // 타임라인 영역
    CRect timelineRect(chartRect.left + taskWidth, chartRect.top,
        chartRect.right, chartRect.bottom);

    // 작업 진행바
    int barHeight = rowHeight - 10;

    // 상태별 색상 정의
    COLORREF barColors[4] = {
        RGB(0, 150, 0),     // 완료됨 - 녹색
        RGB(60, 179, 113),  // 진행 중 - 연한 녹색
        RGB(100, 149, 237), // 예정됨 - 파란색
        RGB(200, 200, 200)  // 대기 중 - 회색
    };

    // 상태별 테두리 색상 정의
    COLORREF borderColors[4] = {
        RGB(0, 100, 0),     // 완료됨 - 진한 녹색 테두리
        RGB(30, 120, 80),   // 진행 중 - 진한 녹색 테두리
        RGB(70, 100, 180),  // 예정됨 - 진한 파란색 테두리
        RGB(150, 150, 150)  // 대기 중 - 진한 회색 테두리
    };

    // 작업 진행률 (%)
    int progressValues[4] = { 100, 65, 30, 0 };
    CString statusText[4] = { _T("완료"), _T("진행 중"), _T("예정됨"), _T("대기") };

    for (int i = 0; i < rowCount; i++) {
        // 작업 상태 배경 (행 전체)
        CRect rowBgRect(timelineRect.left, chartRect.top + i * rowHeight,
            timelineRect.right, chartRect.top + (i + 1) * rowHeight);

        // 행 배경색 (번갈아가며)
        if (i % 2 == 0) {
            pDC->FillSolidRect(rowBgRect, RGB(240, 250, 240)); // 연한 녹색 배경
        }
        else {
            pDC->FillSolidRect(rowBgRect, RGB(250, 255, 250)); // 더 연한 녹색 배경
        }

        // 행 테두리
        CPen rowPen(PS_SOLID, 1, RGB(200, 230, 200));
        CPen* pOldPen = pDC->SelectObject(&rowPen);
        pDC->Rectangle(rowBgRect);
        pDC->SelectObject(pOldPen);

        // 작업 진행 바
        int barY = chartRect.top + i * rowHeight + (rowHeight - barHeight) / 2;
        int maxBarWidth = timelineRect.Width() - 20; // 여백 조정
        int barWidth = maxBarWidth * progressValues[i] / 100;

        CRect barRect(timelineRect.left + 10, barY,
            timelineRect.left + 10 + barWidth, barY + barHeight);

        // 애니메이션 효과 - 진행 중인 작업만 (두 번째 행)
        if (i == 1) {
            int animationOffset = (m_nAnimStep % 4) * 2;
            barWidth = maxBarWidth * (progressValues[i] + animationOffset) / 100;
            if (barWidth > maxBarWidth) barWidth = maxBarWidth;

            barRect.right = timelineRect.left + 10 + barWidth;
        }

        // 작업 바 배경
        pDC->FillSolidRect(barRect, barColors[i]);

        // 테두리 개선 - 상태별 색상
        CPen barPen(PS_SOLID, 2, borderColors[i]);
        pOldPen = pDC->SelectObject(&barPen);
        pDC->Rectangle(barRect);

        // 깜빡임 효과 (진행 중인 작업만)
        if (i == 1 && m_bBlinkState) {
            CPen highlightPen(PS_SOLID, 2, RGB(255, 165, 0));
            pDC->SelectObject(&highlightPen);

            CRect highlightRect = barRect;
            highlightRect.InflateRect(1, 1);
            pDC->Rectangle(highlightRect);

            pDC->SelectObject(&barPen);
        }

        // 상태 텍스트
        if (barWidth > 40) {
            // 글자색 조정 - 더 선명한 흰색
            pDC->SetTextColor(RGB(255, 255, 255));

            // 텍스트에 그림자 효과 추가
            CRect shadowRect = barRect;
            shadowRect.OffsetRect(1, 1);
            pDC->SetTextColor(RGB(30, 30, 30));
            pDC->DrawText(statusText[i], shadowRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

            // 실제 텍스트
            pDC->SetTextColor(RGB(255, 255, 255));
            pDC->DrawText(statusText[i], barRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        }
        else {
            // 바가 너무 작으면 바 오른쪽에 텍스트 표시
            CRect textRect(barRect.right + 5, barRect.top,
                barRect.right + 80, barRect.bottom);

            pDC->SetTextColor(borderColors[i]); // 상태별 색상 적용
            pDC->DrawText(statusText[i], textRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
        }

        pDC->SelectObject(pOldPen);
    }

    // 현재 날짜 마커
    int todayPos = timelineRect.left + timelineRect.Width() * 2 / 3;
    CPen todayPen(PS_SOLID, 1, RGB(255, 0, 0));
    CPen* pOldPen = pDC->SelectObject(&todayPen);

    // 깜빡임 효과
    if (m_bBlinkState) {
        pDC->MoveTo(todayPos, chartRect.top);
        pDC->LineTo(todayPos, chartRect.bottom);
    }

    // 하단 요약 정보
    CRect summaryRect(panelRect.left, chartRect.bottom + 5, panelRect.right, panelRect.bottom);

    CFont summaryFont;
    summaryFont.CreateFont(14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));
    pDC->SelectObject(&summaryFont);

    pDC->SetTextColor(RGB(60, 100, 60));
    pDC->DrawText(_T("2개 작업 완료, 1개 진행 중, 1개 예정"), summaryRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    // 리소스 정리
    pDC->SelectObject(pOldFont);
    pDC->SelectObject(pOldPen);
    headerFont.DeleteObject();
    summaryFont.DeleteObject();
}

// 실시간 생산 진행 상황 아이콘 그리기
void CProductionDlg::DrawLiveStatusIcon(CDC* pDC, CRect rect)
{
    // 배경 패널
    CRect panelRect(rect.left + 10, rect.top + 5, rect.right - 10, rect.bottom - 20);
    pDC->FillSolidRect(panelRect, RGB(240, 240, 255));
    pDC->Rectangle(panelRect);

    // 헤더 영역
    CRect headerRect(panelRect.left, panelRect.top, panelRect.right, panelRect.top + 25);
    pDC->FillSolidRect(headerRect, RGB(106, 90, 205));

    CFont headerFont;
    headerFont.CreateFont(15, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));
    CFont* pOldFont = pDC->SelectObject(&headerFont);

    pDC->SetTextColor(RGB(255, 255, 255));
    pDC->DrawText(_T("실시간 생산 진행 상황"), headerRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    // 모니터 디스플레이
    int monitorWidth = 100;
    int monitorHeight = 80;
    int centerX = (panelRect.left + panelRect.right) / 2 - 30;
    int centerY = (panelRect.top + panelRect.bottom) / 2;

    CRect monitorRect(centerX - monitorWidth / 2, centerY - monitorHeight / 2,
        centerX + monitorWidth / 2, centerY + monitorHeight / 2);

    // 모니터 프레임
    pDC->FillSolidRect(monitorRect, RGB(80, 80, 80));
    pDC->Rectangle(monitorRect);

    // 모니터 화면
    CRect screenRect = monitorRect;
    screenRect.DeflateRect(5, 5, 5, 15);
    pDC->FillSolidRect(screenRect, RGB(30, 30, 50));

    // 모니터 스탠드
    CRect standRect(centerX - 15, monitorRect.bottom - 5,
        centerX + 15, monitorRect.bottom + 15);
    pDC->FillSolidRect(standRect, RGB(50, 50, 50));
    pDC->Rectangle(standRect);

    // 그래프 데이터 (애니메이션)
    CPen graphPen(PS_SOLID, 1, RGB(0, 255, 0));
    CPen* pOldPen = pDC->SelectObject(&graphPen);

    // 데이터 포인트 (애니메이션)
    int dataPoints[6];
    for (int i = 0; i < 6; i++) {
        // 애니메이션에 따라 변동하는 데이터
        int baseHeight = 10 + i * 4;
        int variation = ((m_nAnimStep + i) % 5) - 2;
        dataPoints[i] = baseHeight + variation;
    }

    // 그래프 그리기
    int dataWidth = screenRect.Width() - 10;
    int startX = screenRect.left + 5;
    int startY = screenRect.bottom - 10;
    int step = dataWidth / 5;

    for (int i = 0; i < 5; i++) {
        pDC->MoveTo(startX + i * step, startY - dataPoints[i]);
        pDC->LineTo(startX + (i + 1) * step, startY - dataPoints[i + 1]);

        // 데이터 포인트 표시
        CRect pointRect(startX + i * step - 2, startY - dataPoints[i] - 2,
            startX + i * step + 2, startY - dataPoints[i] + 2);

        CBrush pointBrush(RGB(0, 255, 0));
        CBrush* pOldBrush = pDC->SelectObject(&pointBrush);
        pDC->Ellipse(pointRect);
        pDC->SelectObject(pOldBrush);
    }

    // 마지막 포인트 (깜빡임 효과)
    CRect lastPoint(startX + 5 * step - 3, startY - dataPoints[5] - 3,
        startX + 5 * step + 3, startY - dataPoints[5] + 3);

    if (m_bBlinkState) {
        CBrush redBrush(RGB(255, 0, 0));
        CBrush* pOldBrush = pDC->SelectObject(&redBrush);
        pDC->Ellipse(lastPoint);
        pDC->SelectObject(pOldBrush);
    }
    else {
        CBrush greenBrush(RGB(0, 200, 0));
        CBrush* pOldBrush = pDC->SelectObject(&greenBrush);
        pDC->Ellipse(lastPoint);
        pDC->SelectObject(pOldBrush);
    }

    // 설비 아이콘 (오른쪽)
    int machineWidth = 60;
    int machineHeight = 80;
    int machineX = centerX + monitorWidth / 2 + 30;

    CRect machineRect(machineX, centerY - machineHeight / 2,
        machineX + machineWidth, centerY + machineHeight / 2);

    CBrush machineBrush(RGB(120, 120, 140));
    CBrush* pOldBrush = pDC->SelectObject(&machineBrush);
    pDC->Rectangle(machineRect);

    // 설비 패널
    CRect panelRectMachine(machineRect.left + 5, machineRect.top + 10,
        machineRect.right - 5, machineRect.top + 30);
    pDC->FillSolidRect(panelRectMachine, RGB(50, 50, 70));

    // 설비 상태 LED
    CRect ledRect(machineRect.left + machineWidth / 2 - 5, machineRect.top + 50,
        machineRect.left + machineWidth / 2 + 5, machineRect.top + 60);

    // 깜빡임 효과
    if (m_bBlinkState) {
        pDC->FillSolidRect(ledRect, RGB(0, 255, 0));
    }
    else {
        pDC->FillSolidRect(ledRect, RGB(200, 200, 0));
    }
    pDC->Ellipse(ledRect);

    // 컨베이어 벨트 표현
    CRect beltRect(monitorRect.right - 10, centerY - 5,
        machineRect.left + 10, centerY + 5);
    pDC->FillSolidRect(beltRect, RGB(100, 100, 100));

    // 제품 아이템 (애니메이션)
    int itemPos = beltRect.left + (m_nAnimStep * 8) % beltRect.Width();
    if (itemPos > beltRect.right - 10) itemPos = beltRect.left;

    CRect itemRect(itemPos, centerY - 8, itemPos + 10, centerY + 8);
    pDC->FillSolidRect(itemRect, RGB(0, 120, 200));
    pDC->Rectangle(itemRect);

    // 하단 정보 표시
    CRect infoRect(panelRect.left, machineRect.bottom + 10,
        panelRect.right, panelRect.bottom);

    CFont infoFont;
    infoFont.CreateFont(14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));
    pDC->SelectObject(&infoFont);

    pDC->SetTextColor(RGB(50, 50, 150));
    pDC->DrawText(_T("A라인: 정상 가동 중 (92%)"), infoRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    // 리소스 정리
    pDC->SelectObject(pOldFont);
    pDC->SelectObject(pOldPen);
    pDC->SelectObject(pOldBrush);
    headerFont.DeleteObject();
    infoFont.DeleteObject();
}

// 생산 실적 추적 아이콘 그리기
void CProductionDlg::DrawTrackIcon(CDC* pDC, CRect rect)
{
    // 배경 패널
    CRect panelRect(rect.left + 10, rect.top + 5, rect.right - 10, rect.bottom - 20);
    pDC->FillSolidRect(panelRect, RGB(252, 248, 240));
    pDC->Rectangle(panelRect);

    // 헤더 영역
    CRect headerRect(panelRect.left, panelRect.top, panelRect.right, panelRect.top + 25);
    pDC->FillSolidRect(headerRect, RGB(255, 120, 0));

    CFont headerFont;
    headerFont.CreateFont(15, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));
    CFont* pOldFont = pDC->SelectObject(&headerFont);

    pDC->SetTextColor(RGB(255, 255, 255));
    pDC->DrawText(_T("생산 실적 분석"), headerRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    // 차트 영역
    CRect chartRect(panelRect.left + 10, headerRect.bottom + 10,
        panelRect.right - 10, panelRect.bottom - 30);
    pDC->FillSolidRect(chartRect, RGB(255, 255, 255));
    pDC->Rectangle(chartRect);

    // 축 그리기
    CPen axisPen(PS_SOLID, 2, RGB(150, 150, 150));
    CPen* pOldPen = pDC->SelectObject(&axisPen);

    int axisMargin = 30;
    int axisBottom = chartRect.bottom - axisMargin;

    // X축
    pDC->MoveTo(chartRect.left + axisMargin, axisBottom);
    pDC->LineTo(chartRect.right - 10, axisBottom);

    // Y축
    pDC->MoveTo(chartRect.left + axisMargin, chartRect.top + 10);
    pDC->LineTo(chartRect.left + axisMargin, axisBottom);

    // 막대 그래프 데이터
    int barCount = 5;
    int barWidth = (chartRect.Width() - axisMargin - 20) / barCount - 10;
    int maxHeight = axisBottom - (chartRect.top + 10);

    // 데이터 값 (애니메이션)
    int barValues[5] = { 65, 80, 92, 75, 88 };
    COLORREF barColors[5] = {
        RGB(255, 160, 0),  // 주황
        RGB(255, 130, 0),  // 주황-빨강
        RGB(255, 100, 0),  // 짙은 주황
        RGB(255, 70, 0),   // 주황-빨강
        RGB(255, 40, 0)    // 진한 빨강
    };

    // 현재 선택된 막대 (깜빡임 효과)
    int highlightedBar = (m_nAnimStep / 2) % 5;

    // 막대 그리기
    for (int i = 0; i < barCount; i++) {
        int barHeight = (int)(maxHeight * barValues[i] / 100);

        // 애니메이션 효과 - 선택된 막대는 높이 변동
        if (i == highlightedBar) {
            if (m_bBlinkState) {
                barHeight += 5;
            }
            else {
                barHeight -= 5;
            }
        }

        int barLeft = chartRect.left + axisMargin + 10 + i * (barWidth + 10);
        int barTop = axisBottom - barHeight;

        CRect barRect(barLeft, barTop, barLeft + barWidth, axisBottom);

        // 그라데이션 효과
        for (int h = 0; h < barHeight; h++) {
            int intensity = 255 - h * 50 / barHeight;
            if (intensity < 120) intensity = 120;

            COLORREF gradColor = RGB(intensity, intensity / 3, 0);
            CRect lineRect(barRect.left, barTop + h, barRect.right, barTop + h + 1);
            pDC->FillSolidRect(lineRect, gradColor);
        }

        // 막대 테두리
        pDC->Rectangle(barRect);

        // 선택된 막대 강조
        if (i == highlightedBar && m_bBlinkState) {
            CPen highlightPen(PS_SOLID, 2, RGB(255, 255, 0));
            pDC->SelectObject(&highlightPen);

            CRect highlightRect = barRect;
            highlightRect.InflateRect(2, 2);
            pDC->Rectangle(highlightRect);

            pDC->SelectObject(&axisPen);
        }

        // 데이터 값 표시
        CString valueText;
        valueText.Format(_T("%d"), barValues[i]);

        CRect valueRect(barRect.left, barRect.top - 20, barRect.right, barRect.top - 5);
        pDC->SetTextColor(RGB(100, 50, 0));
        pDC->DrawText(valueText, valueRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

        // X축 라벨
        CString monthText;
        monthText.Format(_T("%d월"), i + 1);

        CRect monthRect(barRect.left, axisBottom + 5, barRect.right, axisBottom + 20);
        pDC->SetTextColor(RGB(100, 100, 100));
        pDC->DrawText(monthText, monthRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }

    // 하단 요약 정보
    CRect summaryRect(panelRect.left, chartRect.bottom + 5, panelRect.right, panelRect.bottom);

    CFont summaryFont;
    summaryFont.CreateFont(14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));
    pDC->SelectObject(&summaryFont);

    pDC->SetTextColor(RGB(200, 80, 0));
    pDC->DrawText(_T("3월 생산량 최대 (92 단위)"), summaryRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    // 리소스 정리
    pDC->SelectObject(pOldFont);
    pDC->SelectObject(pOldPen);
    headerFont.DeleteObject();
    summaryFont.DeleteObject();
}