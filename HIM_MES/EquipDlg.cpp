// EquipDlg.cpp
#include "pch.h"
#include "EquipDlg.h"
#include "DashboardDlg.h"
#include "ProductionDlg.h"
#include "SystemDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include <math.h>

IMPLEMENT_DYNAMIC(CEquipDlg, CDialogEx)

CEquipDlg::CEquipDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_EQUIP_DIALOG, pParent), m_nAnimStep(0), m_bBlinkState(false)
{
}

CEquipDlg::~CEquipDlg()
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

void CEquipDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_BTN_DASHBOARD, m_btnDashboard);
    DDX_Control(pDX, IDC_BTN_PRODUCTION, m_btnProduction);
    DDX_Control(pDX, IDC_BTN_EQUIP, m_btnEquipment);
    DDX_Control(pDX, IDC_BTN_SYSTEM, m_btnSystem);

    // 설비관리 위젯 버튼 추가
    DDX_Control(pDX, IDC_BTN_RUN_STATUS, m_btnRunStatus);
    DDX_Control(pDX, IDC_BTN_MAINT_PLAN, m_btnMaintPlan);
    DDX_Control(pDX, IDC_BTN_MONITORING, m_btnMonitoring);
    DDX_Control(pDX, IDC_BTN_HISTORY, m_btnHistory);
}

BEGIN_MESSAGE_MAP(CEquipDlg, CDialogEx)
    ON_BN_CLICKED(IDC_BTN_DASHBOARD, &CEquipDlg::OnBnClickedBtnDashboard)
    ON_BN_CLICKED(IDC_BTN_PRODUCTION, &CEquipDlg::OnBnClickedBtnProduction)
    ON_BN_CLICKED(IDC_BTN_EQUIP, &CEquipDlg::OnBnClickedBtnEquip)
    ON_BN_CLICKED(IDC_BTN_SYSTEM, &CEquipDlg::OnBnClickedBtnSystem)
    ON_BN_CLICKED(IDC_BTN_RUN_STATUS, &CEquipDlg::OnBnClickedBtnRunStatus)
    ON_BN_CLICKED(IDC_BTN_MAINT_PLAN, &CEquipDlg::OnBnClickedBtnMaintPlan)
    ON_BN_CLICKED(IDC_BTN_MONITORING, &CEquipDlg::OnBnClickedBtnMonitoring)
    ON_BN_CLICKED(IDC_BTN_HISTORY, &CEquipDlg::OnBnClickedBtnHistory)
    ON_WM_CTLCOLOR()
    ON_WM_PAINT()
    ON_WM_DRAWITEM()
    ON_WM_TIMER()
    ON_WM_DESTROY()
END_MESSAGE_MAP()

BOOL CEquipDlg::OnEraseBkgnd(CDC* pDC)
{
    return CDialogEx::OnEraseBkgnd(pDC);
}
void CEquipDlg::OnBnClickedBtnDashboard()
{
    KillTimer(1003);
    EndDialog(IDCANCEL);
    CDashboardDlg dlg;
    dlg.DoModal();
}

void CEquipDlg::OnBnClickedBtnProduction()
{
    KillTimer(1003);
    EndDialog(IDCANCEL);
    CProductionDlg dlg;
    dlg.DoModal();
}

void CEquipDlg::OnBnClickedBtnEquip()
{
    // 설비관리 버튼은 현재 화면이므로 아무 동작 안함
}

void CEquipDlg::OnBnClickedBtnSystem()
{
    KillTimer(1003);
    EndDialog(IDCANCEL);
    CSystemDlg dlg;
    dlg.DoModal();
}

void CEquipDlg::OnBnClickedBtnRunStatus()
{
    // 설비 가동 현황 버튼 클릭 처리
    MessageBox(_T("설비 가동 현황 화면으로 이동합니다."), _T("알림"), MB_OK | MB_ICONINFORMATION);
    // 여기에 실제 기능 구현
}

void CEquipDlg::OnBnClickedBtnMaintPlan()
{
    // 예방 정비 계획 버튼 클릭 처리
    MessageBox(_T("예방 정비 계획 화면으로 이동합니다."), _T("알림"), MB_OK | MB_ICONINFORMATION);
    // 여기에 실제 기능 구현
}

void CEquipDlg::OnBnClickedBtnMonitoring()
{
    // 설비 성능 모니터링 버튼 클릭 처리
    MessageBox(_T("설비 성능 모니터링 화면으로 이동합니다."), _T("알림"), MB_OK | MB_ICONINFORMATION);
    // 여기에 실제 기능 구현
}

void CEquipDlg::OnBnClickedBtnHistory()
{
    // 고장 및 정비 이력 관리 버튼 클릭 처리
    MessageBox(_T("고장 및 정비 이력 관리 화면으로 이동합니다."), _T("알림"), MB_OK | MB_ICONINFORMATION);
    // 여기에 실제 기능 구현
}

BOOL CEquipDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // 다이얼로그 제목 설정
    SetWindowText(_T("설비관리 - HIM MES"));

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
    m_btnRunStatus.SetFont(&m_fontWidgetTitle);
    m_btnMaintPlan.SetFont(&m_fontWidgetTitle);
    m_btnMonitoring.SetFont(&m_fontWidgetTitle);
    m_btnHistory.SetFont(&m_fontWidgetTitle);

    // 현재 선택된 메뉴 강조
    m_btnEquipment.EnableWindow(FALSE);

    // 위젯 버튼 스타일 설정
    m_btnRunStatus.ModifyStyle(0, BS_OWNERDRAW);
    m_btnMaintPlan.ModifyStyle(0, BS_OWNERDRAW);
    m_btnMonitoring.ModifyStyle(0, BS_OWNERDRAW);
    m_btnHistory.ModifyStyle(0, BS_OWNERDRAW);

    // 위젯 버튼들의 위치와 크기도 조정
    int contentStartX = sidebarWidth + 10;
    int contentWidth = clientRect.Width() - contentStartX - 20;
    int widgetWidth = (contentWidth - 10) / 2;
    int widgetHeight = (clientRect.Height() - 40) / 2;

    m_btnRunStatus.MoveWindow(contentStartX, 20, widgetWidth, widgetHeight - 10);
    m_btnMaintPlan.MoveWindow(contentStartX + widgetWidth + 10, 20, widgetWidth, widgetHeight - 10);
    m_btnMonitoring.MoveWindow(contentStartX, widgetHeight + 20, widgetWidth, widgetHeight - 10);
    m_btnHistory.MoveWindow(contentStartX + widgetWidth + 10, widgetHeight + 20, widgetWidth, widgetHeight - 10);

    // 애니메이션 타이머 설정 (300ms마다 갱신)
    SetTimer(1003, 700, NULL);

    // 깜빡임 방지를 위한 WS_EX_COMPOSITED 스타일 추가
    ModifyStyleEx(0, WS_EX_COMPOSITED);

    return TRUE;
}

void CEquipDlg::OnTimer(UINT_PTR nIDEvent)
{
    if (nIDEvent == 1003)
    {
        // 애니메이션 스텝 증가
        m_nAnimStep = (m_nAnimStep + 1) % 10;
        m_bBlinkState = !m_bBlinkState;

        // 위젯 버튼 영역만 갱신 (한 번의 Invalidate 호출로)
        CRect rcClient;
        GetClientRect(&rcClient);

        // 사이드바 너비
        int sidebarWidth = 120;

        // 콘텐츠 영역만 갱신 (사이드바는 제외)
        CRect rcContent(sidebarWidth, 0, rcClient.right, rcClient.bottom);
        InvalidateRect(rcContent, FALSE);
    }

    CDialogEx::OnTimer(nIDEvent);
}

void CEquipDlg::OnDestroy()
{
    KillTimer(1003);
    CDialogEx::OnDestroy();
}

void CEquipDlg::OnPaint()
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
    m_btnEquipment.GetWindowRect(&btnRect);
    ScreenToClient(&btnRect);

    // 선택된 버튼 왼쪽에 강조 바 그리기
    CRect accentBarRect(0, btnRect.top, 5, btnRect.bottom);
    dc.FillSolidRect(accentBarRect, RGB(41, 182, 246)); // 밝은 파란색

    dc.SelectObject(pOldFont);
    CDialogEx::OnPaint();
}

HBRUSH CEquipDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

void CEquipDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    // 위젯 버튼 그리기
    if (nIDCtl == IDC_BTN_RUN_STATUS || nIDCtl == IDC_BTN_MAINT_PLAN ||
        nIDCtl == IDC_BTN_MONITORING || nIDCtl == IDC_BTN_HISTORY)
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
        case IDC_BTN_RUN_STATUS:
            headerColor = RGB(0, 128, 255);  // 설비 가동 현황용 파란색
            break;
        case IDC_BTN_MAINT_PLAN:
            headerColor = RGB(255, 165, 0);  // 예방 정비 계획용 주황색
            break;
        case IDC_BTN_MONITORING:
            headerColor = RGB(50, 205, 50);  // 설비 성능 모니터링용 녹색
            break;
        case IDC_BTN_HISTORY:
            headerColor = RGB(220, 20, 60);  // 고장 및 정비 이력 관리용 빨간색
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
        case IDC_BTN_RUN_STATUS:
            DrawRunStatusIcon(&dc, contentRect);
            break;
        case IDC_BTN_MAINT_PLAN:
            DrawMaintPlanIcon(&dc, contentRect);
            break;
        case IDC_BTN_MONITORING:
            DrawMonitoringIcon(&dc, contentRect);
            break;
        case IDC_BTN_HISTORY:
            DrawHistoryIcon(&dc, contentRect);
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

// 설비 가동 현황 아이콘 그리기
void CEquipDlg::DrawRunStatusIcon(CDC* pDC, CRect rect)
{
    // 기계 및 설비 아이콘들 그리기
    int centerX = (rect.left + rect.right) / 2;
    int centerY = (rect.top + rect.bottom - 40) / 2;

    // 기계 설비 행 개수
    int rowCount = 3;
    int colCount = 2;
    int machineSize = 60;
    int machineGap = 30; // 간격 확대 (기존 20 -> 30)

    // 기계 설비 상태 데이터 (예시)
    bool machineStatus[6] = { true, true, false, true, false, true };
    CString machineNames[6] = { _T("설비 A-1"), _T("설비 A-2"), _T("설비 B-1"),
                              _T("설비 B-2"), _T("설비 C-1"), _T("설비 C-2") };

    // 모든 설비 배치를 위한 시작 위치 계산
    int startX = centerX - ((machineSize * colCount) + (machineGap * (colCount - 1))) / 2;
    int startY = centerY - ((machineSize * rowCount) + (machineGap * (rowCount - 1))) / 2;

    // 설비 상태별 색상
    COLORREF runningColor = RGB(0, 200, 0);   // 가동 중 - 녹색
    COLORREF stoppedColor = RGB(200, 0, 0);   // 정지 - 빨간색
    COLORREF defaultColor = RGB(100, 100, 100); // 기본 - 회색

    // 애니메이션 변수에 따른 효과
    int animOffset = (m_nAnimStep % 5 - 2) * 2; // -4~4 사이 변동

    // 각 설비 그리기
    int machineIndex = 0;
    for (int row = 0; row < rowCount; row++) {
        for (int col = 0; col < colCount; col++) {
            if (machineIndex < 6) {
                int machineX = startX + col * (machineSize + machineGap);
                int machineY = startY + row * (machineSize + machineGap);

                CRect machineRect(
                    machineX, machineY,
                    machineX + machineSize, machineY + machineSize
                );

                // 기계 본체 그리기
                COLORREF bodyColor;
                if (machineStatus[machineIndex]) {
                    // 가동 중인 설비 - 애니메이션 효과
                    if (m_bBlinkState) {
                        bodyColor = RGB(0, 180, 0); // 약간 어두운 녹색
                    }
                    else {
                        bodyColor = RGB(0, 220, 0); // 밝은 녹색
                    }
                }
                else {
                    // 정지된 설비 - 빨간색
                    bodyColor = stoppedColor;
                }

                pDC->FillSolidRect(machineRect, bodyColor);
                pDC->Rectangle(machineRect);

                // 설비 내부 세부 요소 그리기
                // 설비 윈도우/화면
                CRect windowRect(
                    machineRect.left + 10, machineRect.top + 10,
                    machineRect.right - 10, machineRect.top + 25
                );
                pDC->FillSolidRect(windowRect, RGB(200, 200, 220));
                pDC->Rectangle(windowRect);

                // 설비 컨트롤 패널
                CRect panelRect(
                    machineRect.left + 15, machineRect.bottom - 25,
                    machineRect.right - 15, machineRect.bottom - 10
                );
                pDC->FillSolidRect(panelRect, RGB(40, 40, 40));
                pDC->Rectangle(panelRect);

                // 설비 상태 표시등
                CRect statusLightRect(
                    machineRect.right - 15, machineRect.top + 5,
                    machineRect.right - 5, machineRect.top + 15
                );

                // 상태에 따른 색상 및 깜빡임 효과
                if (machineStatus[machineIndex]) {
                    if (m_bBlinkState) {
                        pDC->FillSolidRect(statusLightRect, RGB(0, 255, 0));
                    }
                    else {
                        pDC->FillSolidRect(statusLightRect, RGB(0, 200, 0));
                    }
                }
                else {
                    // 정지된 설비는 빨간색 깜빡임
                    if (m_bBlinkState) {
                        pDC->FillSolidRect(statusLightRect, RGB(255, 0, 0));
                    }
                    else {
                        pDC->FillSolidRect(statusLightRect, RGB(180, 0, 0));
                    }
                }
                pDC->Ellipse(statusLightRect);

                // 작동 효과 (가동 중인 설비만)
                if (machineStatus[machineIndex]) {
                    // 가동 부품 움직임 효과
                    CRect movingPartRect(
                        machineRect.left + 20 + animOffset, machineRect.top + 35,
                        machineRect.right - 20 + animOffset, machineRect.top + 45
                    );
                    pDC->FillSolidRect(movingPartRect, RGB(180, 180, 180));
                    pDC->Rectangle(movingPartRect);
                }

                // 설비 이름 표시 - 텍스트 영역 확장 및 배경 추가
                pDC->SetTextColor(RGB(0, 0, 0)); // 더 진한 색상으로 변경
                CRect nameRect(
                    machineRect.left - 10, machineRect.bottom + 5,
                    machineRect.right + 10, machineRect.bottom + 20
                );

                // 텍스트 배경을 흰색으로 채워 가독성 향상
                pDC->FillSolidRect(nameRect, RGB(240, 240, 240));

                // 테두리 추가
                pDC->DrawEdge(nameRect, EDGE_SUNKEN, BF_RECT);

                // 굵은 폰트로 변경
                CFont boldFont;
                boldFont.CreateFont(16, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0,
                    DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
                    CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                    DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));

                CFont* pOldNameFont = pDC->SelectObject(&boldFont);
                pDC->DrawText(machineNames[machineIndex], nameRect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
                pDC->SelectObject(pOldNameFont);
                boldFont.DeleteObject();

                machineIndex++;
            }
        }
    }

    // 상태 요약 표시 - 텍스트 크기 및 가독성 향상
    CFont summaryFont;
    summaryFont.CreateFont(18, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));

    CFont* pOldFont = pDC->SelectObject(&summaryFont);
    pDC->SetTextColor(RGB(0, 0, 120)); // 진한 파란색으로 변경

    // 배경 추가
    CRect summaryRect(rect.left + 10, rect.bottom - 30, rect.right - 10, rect.bottom);
    pDC->FillSolidRect(summaryRect, RGB(235, 235, 255)); // 연한 파란색 배경
    pDC->Rectangle(summaryRect);

    CString summary;
    summary.Format(_T("총 설비 6대 중 4대 가동 중 (가동률: 66.7%%)"));
    pDC->DrawText(summary, summaryRect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

    pDC->SelectObject(pOldFont);
    summaryFont.DeleteObject();
}


// 예방 정비 계획 아이콘 그리기
void CEquipDlg::DrawMaintPlanIcon(CDC* pDC, CRect rect)
{
    // 달력과 체크리스트 스타일로 그리기
    int centerX = (rect.left + rect.right) / 2;
    int centerY = (rect.top + rect.bottom - 40) / 2;

    // 달력 영역
    int calWidth = 240;
    int calHeight = 120;
    CRect calRect(
        centerX - calWidth / 2, centerY - calHeight / 2 - 20,
        centerX + calWidth / 2, centerY + calHeight / 2 - 20
    );

    // 달력 배경
    pDC->FillSolidRect(calRect, RGB(255, 255, 255));
    pDC->Rectangle(calRect);

    // 달력 헤더
    CRect headerRect(calRect.left, calRect.top, calRect.right, calRect.top + 25);
    pDC->FillSolidRect(headerRect, RGB(255, 165, 0));

    // 달력 제목
    pDC->SetTextColor(RGB(255, 255, 255));
    pDC->SetBkMode(TRANSPARENT);
    CFont* pOldFont = pDC->SelectObject(&m_fontContent);
    pDC->DrawText(_T("2025년 4월 정비 계획"), headerRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    // 달력 그리드
    int cols = 7; // 일~토
    int rows = 5; // 4주
    int cellWidth = calWidth / cols;
    int cellHeight = (calHeight - 25) / rows;

    // 요일 헤더
    CString dayNames[7] = { _T("일"), _T("월"), _T("화"), _T("수"), _T("목"), _T("금"), _T("토") };
    for (int i = 0; i < cols; i++) {
        CRect dayRect(
            calRect.left + i * cellWidth,
            headerRect.bottom,
            calRect.left + (i + 1) * cellWidth,
            headerRect.bottom + 20
        );

        // 주말은 붉은색으로 표시
        if (i == 0 || i == 6) {
            pDC->SetTextColor(RGB(255, 0, 0));
        }
        else {
            pDC->SetTextColor(RGB(0, 0, 0));
        }

        pDC->DrawText(dayNames[i], dayRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }

    // 날짜 채우기
    int startDay = 1; // 1일부터 시작
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            int day = startDay + row * cols + col;
            if (day <= 30) { // 4월은 30일까지
                CRect dateRect(
                    calRect.left + col * cellWidth,
                    headerRect.bottom + 20 + row * cellHeight,
                    calRect.left + (col + 1) * cellWidth,
                    headerRect.bottom + 20 + (row + 1) * cellHeight
                );

                // 주말은 빨간색으로 표시
                if (col == 0 || col == 6) {
                    pDC->SetTextColor(RGB(200, 0, 0));
                }
                else {
                    pDC->SetTextColor(RGB(0, 0, 0));
                }

                CString dateStr;
                dateStr.Format(_T("%d"), day);
                pDC->DrawText(dateStr, dateRect, DT_RIGHT | DT_TOP | DT_SINGLELINE);

                // 정비 계획이 있는 날짜 표시 (예시 데이터)
                bool hasMaintenance = (day == 5 || day == 12 || day == 19 || day == 26); // 매주 월요일
                bool isUpcoming = (day == 5 || day == 12); // 다가오는 정비

                if (hasMaintenance) {
                    // 정비 표시 마커
                    CRect markerRect(
                        dateRect.left + 5,
                        dateRect.bottom - 10,
                        dateRect.left + 15,
                        dateRect.bottom - 2
                    );

                    // 다가오는 정비는 깜빡이는 효과
                    if (isUpcoming && m_bBlinkState) {
                        pDC->FillSolidRect(markerRect, RGB(255, 0, 0));
                    }
                    else {
                        pDC->FillSolidRect(markerRect, RGB(255, 165, 0));
                    }
                    pDC->Rectangle(markerRect);
                }
            }
        }
    }

    // 체크리스트 영역
    int listWidth = 240;
    int listHeight = 80;
    CRect listRect(
        centerX - listWidth / 2, calRect.bottom + 20,
        centerX + listWidth / 2, calRect.bottom + 20 + listHeight
    );

    // 체크리스트 배경
    pDC->FillSolidRect(listRect, RGB(250, 250, 250));
    pDC->Rectangle(listRect);

    // 체크리스트 제목
    CRect listHeaderRect(listRect.left, listRect.top, listRect.right, listRect.top + 20);
    pDC->FillSolidRect(listHeaderRect, RGB(240, 240, 240));
    pDC->SetTextColor(RGB(50, 50, 50));
    pDC->DrawText(_T("다가오는 정비 계획"), listHeaderRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    // 체크리스트 항목들
    pDC->SetTextColor(RGB(50, 50, 50));
    CString items[3] = {
        _T("A-1 설비 정기 점검 (5일)"),
        _T("B-2 설비 부품 교체 (12일)"),
        _T("공장 전체 점검 (19일)")
    };

    for (int i = 0; i < 3; i++) {
        CRect itemRect(
            listRect.left + 5, listRect.top + 25 + i * 18,
            listRect.right - 5, listRect.top + 25 + (i + 1) * 18
        );

        // 체크박스 그리기
        CRect checkRect(
            itemRect.left, itemRect.top + 2,
            itemRect.left + 14, itemRect.top + 16
        );
        pDC->Rectangle(checkRect);

        // 애니메이션에 따라 첫 항목은 깜빡이는 효과
        if (i == 0 && m_bBlinkState) {
            pDC->FillSolidRect(checkRect, RGB(255, 200, 0));
        }

        // 항목 텍스트
        CRect textRect(
            checkRect.right + 5, itemRect.top,
            itemRect.right, itemRect.bottom
        );
        pDC->DrawText(items[i], textRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
    }

    // 정보 표시
    pDC->SetTextColor(RGB(50, 50, 50));
    CRect infoRect(rect.left, listRect.bottom + 10, rect.right, rect.bottom);
    CString infoText = _T("이번 달 정비 계획: 총 3회 예정");
    pDC->DrawText(infoText, infoRect, DT_CENTER | DT_TOP | DT_SINGLELINE);

    pDC->SelectObject(pOldFont);
}
// 고장 및 정비 이력 관리 아이콘 그리기
void CEquipDlg::DrawHistoryIcon(CDC* pDC, CRect rect)
{
    // 문서, 그래프, 히스토리 시각화
    int centerX = (rect.left + rect.right) / 2;
    int centerY = (rect.top + rect.bottom - 40) / 2;

    // 레포트 문서 아이콘 - 크기 더 확대
    int docWidth = 260; // 기존 200에서 더 확대
    int docHeight = 250; // 기존 200에서 더 확대
    CRect docRect(
        centerX - docWidth / 2, centerY - docHeight / 2,
        centerX + docWidth / 2, centerY + docHeight / 2
    );

    // 문서 배경
    pDC->FillSolidRect(docRect, RGB(255, 255, 255));
    CPen docPen(PS_SOLID, 1, RGB(150, 150, 150));
    CPen* pOldPen = pDC->SelectObject(&docPen);
    pDC->Rectangle(docRect);

    // 문서 제목 영역
    CRect titleRect(docRect.left, docRect.top, docRect.right, docRect.top + 25);
    pDC->FillSolidRect(titleRect, RGB(220, 20, 60)); // 빨간색 헤더

    // 제목 텍스트
    pDC->SetTextColor(RGB(255, 255, 255));
    pDC->SetBkMode(TRANSPARENT);
    CFont* pOldFont = pDC->SelectObject(&m_fontContent);
    pDC->DrawText(_T("설비 정비 이력 요약"), titleRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    // 문서 내용 - 테이블 형태
    // 테이블 헤더
    CRect headerRect(docRect.left + 5, titleRect.bottom + 5, docRect.right - 5, titleRect.bottom + 25);
    pDC->FillSolidRect(headerRect, RGB(240, 240, 240));

    // 컬럼 구분 - 내용 컬럼 확장
    int col1Width = 55;  // 날짜 (약간 축소)
    int col2Width = 45;  // 설비 (약간 축소)
    int col3Width = docRect.Width() - 10 - col1Width - col2Width; // 내용 (더 넓게)

    // 컬럼 헤더 텍스트
    pDC->SetTextColor(RGB(50, 50, 50));

    CRect col1Header(headerRect.left, headerRect.top, headerRect.left + col1Width, headerRect.bottom);
    pDC->DrawText(_T("날짜"), col1Header, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    CRect col2Header(col1Header.right, headerRect.top, col1Header.right + col2Width, headerRect.bottom);
    pDC->DrawText(_T("설비"), col2Header, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    CRect col3Header(col2Header.right, headerRect.top, headerRect.right, headerRect.bottom);
    pDC->DrawText(_T("내용"), col3Header, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    // 구분선
    pDC->MoveTo(col1Header.right, headerRect.top);
    pDC->LineTo(col1Header.right, headerRect.bottom);

    pDC->MoveTo(col2Header.right, headerRect.top);
    pDC->LineTo(col2Header.right, headerRect.bottom);

    // 데이터 행 (예시) - 행 높이 증가
    struct HistoryData {
        CString date;
        CString equipment;
        CString content;
        bool isWarning;
    };

    HistoryData historyData[5] = {
        { _T("04/27"), _T("A-1"), _T("정기 점검 완료"), false },
        { _T("04/25"), _T("B-2"), _T("모터 교체"), false },
        { _T("04/22"), _T("C-1"), _T("과열 경고 - 긴급 정비 완료"), true }, // 내용 확장
        { _T("04/18"), _T("A-3"), _T("센서 조정"), false },
        { _T("04/15"), _T("B-1"), _T("필터 교체"), false }
    };

    int rowHeight = 26; // 행 높이 증가 (22 -> 26)
    for (int i = 0; i < 5; i++) {
        int rowTop = headerRect.bottom + 1 + i * rowHeight;
        CRect rowRect(docRect.left + 5, rowTop, docRect.right - 5, rowTop + rowHeight);

        // 행 구분 배경색 (교대로)
        if (i % 2 == 0) {
            pDC->FillSolidRect(rowRect, RGB(250, 250, 250));
        }
        else {
            pDC->FillSolidRect(rowRect, RGB(240, 240, 240));
        }

        // 경고 항목 강조 (빨간색 배경)
        if (historyData[i].isWarning) {
            if (m_bBlinkState) { // 깜빡임 효과
                pDC->FillSolidRect(rowRect, RGB(255, 200, 200));
            }
            else {
                pDC->FillSolidRect(rowRect, RGB(255, 220, 220));
            }
        }

        // 열 데이터
        CRect col1Data(rowRect.left, rowRect.top, rowRect.left + col1Width, rowRect.bottom);
        CRect col2Data(col1Data.right, rowRect.top, col1Data.right + col2Width, rowRect.bottom);
        CRect col3Data(col2Data.right, rowRect.top, rowRect.right, rowRect.bottom);

        // 텍스트 색상 - 경고 항목은 빨간색으로
        if (historyData[i].isWarning) {
            pDC->SetTextColor(RGB(180, 0, 0));
        }
        else {
            pDC->SetTextColor(RGB(0, 0, 0));
        }

        // 텍스트를 좀 더 작게 조정하여 잘리지 않도록 함
        CFont contentFont;
        contentFont.CreateFont(14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));

        CFont* pOldContentFont = pDC->SelectObject(&contentFont);

        // 내용 컬럼에 여백 추가
        CRect adjustedCol3Data = col3Data;
        adjustedCol3Data.left += 5; // 왼쪽 여백 추가

        pDC->DrawText(historyData[i].date, col1Data, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        pDC->DrawText(historyData[i].equipment, col2Data, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        pDC->DrawText(historyData[i].content, adjustedCol3Data, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

        pDC->SelectObject(pOldContentFont);
        contentFont.DeleteObject();

        // 구분선
        pDC->MoveTo(rowRect.left, rowRect.bottom);
        pDC->LineTo(rowRect.right, rowRect.bottom);

        pDC->MoveTo(col1Data.right, rowRect.top);
        pDC->LineTo(col1Data.right, rowRect.bottom);

        pDC->MoveTo(col2Data.right, rowRect.top);
        pDC->LineTo(col2Data.right, rowRect.bottom);
    }

    // 버튼 제거 - 대신 테이블 확장 및 정보 추가
    // 애니메이션 효과 - 문서 아이콘 상단
    CRect iconRect(docRect.right - 25, docRect.top - 5, docRect.right - 5, docRect.top + 15);
    if (m_bBlinkState) {
        CBrush notiBrush(RGB(255, 0, 0));
        CBrush* pOldBrush = pDC->SelectObject(&notiBrush);
        pDC->Ellipse(iconRect);
        pDC->SelectObject(pOldBrush);

        pDC->SetTextColor(RGB(255, 255, 255));
        pDC->DrawText(_T("!"), iconRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }

    // 요약 정보 - 디자인 개선
    CRect summaryBg(rect.left + 20, docRect.bottom + 10, rect.right - 20, rect.bottom - 5);
    pDC->FillSolidRect(summaryBg, RGB(240, 230, 230));
    pDC->Rectangle(summaryBg);

    pDC->SetTextColor(RGB(180, 0, 0)); // 진한 빨간색
    CFont summaryFont;
    summaryFont.CreateFont(16, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));

    CFont* pOldSummaryFont = pDC->SelectObject(&summaryFont);
    CString summary = _T("최근 30일간 총 정비 건수: 12건 (긴급: 1건)");
    pDC->DrawText(summary, summaryBg, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    pDC->SelectObject(pOldSummaryFont);
    summaryFont.DeleteObject();
    pDC->SelectObject(pOldFont);
    pDC->SelectObject(pOldPen);
}

// 설비 성능 모니터링 아이콘 그리기 (개선된 버전)
void CEquipDlg::DrawMonitoringIcon(CDC* pDC, CRect rect)
{
    // 기본 변수 설정
    int centerX = (rect.left + rect.right) / 2;
    int centerY = (rect.top + rect.bottom - 40) / 2;

    // 타이틀 영역
    CRect titleRect(rect.left + 20, rect.top + 10, rect.right - 20, rect.top + 30);
    pDC->SetTextColor(RGB(50, 50, 50));
    CFont* pOldFont = pDC->SelectObject(&m_fontContent);
    pDC->DrawText(_T("설비 성능 모니터링"), titleRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    // 그래프 영역
    int graphWidth = rect.Width() - 40;
    int graphHeight = 120;
    CRect graphRect(
        centerX - graphWidth / 2, centerY - graphHeight / 2 - 10,
        centerX + graphWidth / 2, centerY + graphHeight / 2 - 10
    );

    // 그래프 배경
    pDC->FillSolidRect(graphRect, RGB(240, 240, 240));
    pDC->Rectangle(graphRect);

    // Y축 레이블 영역 너비
    int yAxisWidth = 40;
    int dataAreaStartX = graphRect.left + yAxisWidth;

    // 그래프 축 그리기
    CPen axisPen(PS_SOLID, 1, RGB(80, 80, 80));
    CPen* pOldPen = pDC->SelectObject(&axisPen);

    // X축
    pDC->MoveTo(dataAreaStartX, graphRect.bottom - 20);
    pDC->LineTo(graphRect.right - 10, graphRect.bottom - 20);

    // Y축
    pDC->MoveTo(dataAreaStartX, graphRect.bottom - 20);
    pDC->LineTo(dataAreaStartX, graphRect.top + 10);

    // Y축 레이블 (%)
    CString percentLabels[3] = { _T("0%"), _T("50%"), _T("100%") };
    int yStep = (graphRect.Height() - 30) / 2;

    // Y축 레이블 배경
    CRect yLabelBg(
        graphRect.left, graphRect.top + 10,
        dataAreaStartX, graphRect.bottom - 20
    );
    pDC->FillSolidRect(yLabelBg, RGB(230, 230, 250));

    for (int i = 0; i < 3; i++) {
        CRect labelRect(
            graphRect.left + 2,
            graphRect.bottom - 20 - i * yStep - 7,
            dataAreaStartX - 5,
            graphRect.bottom - 20 - i * yStep + 7
        );

        // 레이블 강조 표시
        CRect highlightRect = labelRect;
        highlightRect.DeflateRect(0, 1);
        pDC->FillSolidRect(highlightRect, RGB(210, 210, 240));

        pDC->DrawText(percentLabels[i], labelRect, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
    }

    // 설비별 성능 데이터 (하드코딩)
    // 이름, 효율(%), 가동상태
    struct {
        LPCTSTR name;
        int efficiency;
        bool isRunning;
    } equipData[6] = {
        { _T("A-1"), 94, true },
        { _T("A-2"), 83, true },
        { _T("B-1"), 89, false }, // B-1 정지 상태
        { _T("B-2"), 90, true },
        { _T("C-1"), 81, false }, // C-1 정지 상태
        { _T("C-2"), 75, true }
    };

    // 바 그래프 그리기
    int barCount = 6;
    int barWidth = (graphRect.Width() - yAxisWidth - 30) / barCount;
    int barGap = 5;

    for (int i = 0; i < barCount; i++) {
        // 바의 위치 계산
        int barX = dataAreaStartX + 5 + i * (barWidth + barGap);
        int maxBarHeight = graphRect.Height() - 30;
        int barHeight = maxBarHeight * equipData[i].efficiency / 100;

        CRect barRect(
            barX,
            graphRect.bottom - 20 - barHeight,
            barX + barWidth - 1,
            graphRect.bottom - 20
        );

        // 바 색상 - 가동 상태에 따라 다르게 설정
        if (equipData[i].isRunning) {
            // 가동 중인 설비는 녹색으로 표시
            if (m_bBlinkState && equipData[i].efficiency > 90) {
                // 효율이 높은 설비는 밝은 녹색으로 깜빡임
                pDC->FillSolidRect(barRect, RGB(20, 220, 20));
            }
            else {
                pDC->FillSolidRect(barRect, RGB(50, 180, 50));
            }
        }
        else {
            // 정지된 설비는 빨간색으로 표시
            if (m_bBlinkState) {
                // 깜빡임 효과
                pDC->FillSolidRect(barRect, RGB(220, 50, 50));
            }
            else {
                pDC->FillSolidRect(barRect, RGB(180, 50, 50));
            }
        }

        // 바 테두리
        pDC->Rectangle(barRect);

        // 설비 이름 표시
        CFont nameFont;
        nameFont.CreateFont(12, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));

        CFont* pOldNameFont = pDC->SelectObject(&nameFont);

        CRect nameRect(
            barX,
            graphRect.bottom - 15,
            barX + barWidth,
            graphRect.bottom + 5
        );

        // 설비 이름 색상도 상태에 따라 다르게
        if (equipData[i].isRunning) {
            pDC->SetTextColor(RGB(0, 100, 0)); // 가동 중 - 진한 녹색
        }
        else {
            pDC->SetTextColor(RGB(150, 0, 0)); // 정지 - 진한 빨간색
        }
        pDC->DrawText(equipData[i].name, nameRect, DT_CENTER | DT_TOP | DT_SINGLELINE);

        // 가동률 표시
        CString percentText;
        percentText.Format(_T("%d%%"), equipData[i].efficiency);

        CRect percentRect(
            barX,
            barRect.top - 15,
            barX + barWidth,
            barRect.top
        );

        // 가동상태에 따른 색상
        if (equipData[i].isRunning) {
            pDC->SetTextColor(RGB(0, 120, 0)); // 진한 녹색
        }
        else {
            pDC->SetTextColor(RGB(180, 0, 0)); // 진한 빨간색
        }

        pDC->DrawText(percentText, percentRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

        // 상태 표시 아이콘 추가
        CRect statusRect(
            barX + barWidth / 2 - 6,
            barRect.top - 30,
            barX + barWidth / 2 + 6,
            barRect.top - 18
        );

        if (equipData[i].isRunning) {
            // 가동 중 - 깜빡이는 녹색 원
            CBrush statusBrush;
            if (m_bBlinkState) {
                statusBrush.CreateSolidBrush(RGB(0, 220, 0));
            }
            else {
                statusBrush.CreateSolidBrush(RGB(0, 180, 0));
            }
            CBrush* pOldBrush = pDC->SelectObject(&statusBrush);
            pDC->Ellipse(statusRect);
            pDC->SelectObject(pOldBrush);
            statusBrush.DeleteObject();
        }
        else {
            // 정지 - 깜빡이는 빨간색 사각형
            if (m_bBlinkState) {
                pDC->FillSolidRect(statusRect, RGB(220, 0, 0));
            }
            else {
                pDC->FillSolidRect(statusRect, RGB(180, 0, 0));
            }
            pDC->Rectangle(statusRect);
        }

        pDC->SelectObject(pOldNameFont);
        nameFont.DeleteObject();
    }

    // 범례
    CRect legendBg(
        centerX - 120, graphRect.bottom + 15,
        centerX + 120, graphRect.bottom + 35
    );
    pDC->FillSolidRect(legendBg, RGB(245, 245, 245));
    pDC->Rectangle(legendBg);


    // 범례 내부 가동 중/정지 체크박스 박스
    int checkboxSize = 10;
    int textPadding = 5;
    int legendPadding = 15;
    int boxStartX = legendBg.left + 45; // 체크박스 시작 위치 조정

    // 가동 중 체크박스
    CRect runningBox(
        boxStartX, legendBg.top + (legendBg.Height() - checkboxSize) / 2,
        boxStartX + checkboxSize, legendBg.top + (legendBg.Height() + checkboxSize) / 2
    );
    // 가동 중 - 녹색 채우기
    pDC->FillSolidRect(runningBox, RGB(50, 180, 50));
    pDC->Rectangle(runningBox);

    // 가동 중 텍스트
    CRect runningTextRect(
        runningBox.right + textPadding, legendBg.top,
        runningBox.right + textPadding + 40, legendBg.bottom
    );
    pDC->SetTextColor(RGB(0, 100, 0));
    pDC->DrawText(_T("가동 중"), runningTextRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

    // 정지 체크박스
    CRect stoppedBox(
        runningTextRect.right + legendPadding, legendBg.top + (legendBg.Height() - checkboxSize) / 2,
        runningTextRect.right + legendPadding + checkboxSize, legendBg.top + (legendBg.Height() + checkboxSize) / 2
    );
    // 정지 - 빨간색 채우기
    pDC->FillSolidRect(stoppedBox, RGB(180, 50, 50));
    pDC->Rectangle(stoppedBox);

    // 정지 텍스트
    CRect stoppedTextRect(
        stoppedBox.right + textPadding, legendBg.top,
        stoppedBox.right + textPadding + 30, legendBg.bottom
    );
    pDC->SetTextColor(RGB(150, 0, 0));
    pDC->DrawText(_T("정지"), stoppedTextRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
}