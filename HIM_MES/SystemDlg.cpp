// SystemDlg.cpp
#include "pch.h"
#include "SystemDlg.h"
#include "DashboardDlg.h"
#include "EquipDlg.h"
#include "ProductionDlg.h"
#include "afxdialogex.h"
#include "resource.h"

IMPLEMENT_DYNAMIC(CSystemDlg, CDialogEx)

CSystemDlg::CSystemDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_SYSTEM_DIALOG, pParent), m_nAnimStep(0), m_bBlinkState(false)
{
}

CSystemDlg::~CSystemDlg()
{
    // 타이머가 있다면 제거

    // 생성한 GDI 객체 정리
    m_brushBg.DeleteObject();
    m_brushWidgetBg.DeleteObject();
    m_brushSidebarBg.DeleteObject();
    m_fontTitle.DeleteObject();
    m_fontWidgetTitle.DeleteObject();
    m_fontMenu.DeleteObject();
    m_fontContent.DeleteObject();
}

void CSystemDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_BTN_DASHBOARD, m_btnDashboard);
    DDX_Control(pDX, IDC_BTN_PRODUCTION, m_btnProduction);
    DDX_Control(pDX, IDC_BTN_EQUIP, m_btnEquipment);
    DDX_Control(pDX, IDC_BTN_SYSTEM, m_btnSystem);

    // 시스템 구성 위젯 버튼 추가
    DDX_Control(pDX, IDC_BTN_USER, m_btnUser);
    DDX_Control(pDX, IDC_BTN_CONFIG, m_btnConfig);
    DDX_Control(pDX, IDC_BTN_LOG, m_btnLog);
    DDX_Control(pDX, IDC_BTN_BACKUP_RESTORE, m_btnBackupRestore);
}

BEGIN_MESSAGE_MAP(CSystemDlg, CDialogEx)
    ON_BN_CLICKED(IDC_BTN_DASHBOARD, &CSystemDlg::OnBnClickedBtnDashboard)
    ON_BN_CLICKED(IDC_BTN_PRODUCTION, &CSystemDlg::OnBnClickedBtnProduction)
    ON_BN_CLICKED(IDC_BTN_EQUIP, &CSystemDlg::OnBnClickedBtnEquip)
    ON_BN_CLICKED(IDC_BTN_SYSTEM, &CSystemDlg::OnBnClickedBtnSystem)
    ON_BN_CLICKED(IDC_BTN_USER, &CSystemDlg::OnBnClickedBtnUser)
    ON_BN_CLICKED(IDC_BTN_CONFIG, &CSystemDlg::OnBnClickedBtnConfig)
    ON_BN_CLICKED(IDC_BTN_LOG, &CSystemDlg::OnBnClickedBtnLog)
    ON_BN_CLICKED(IDC_BTN_BACKUP_RESTORE, &CSystemDlg::OnBnClickedBtnBackupRestore)
    ON_WM_CTLCOLOR()
    ON_WM_PAINT()
    ON_WM_DRAWITEM()
    ON_WM_TIMER()
    ON_WM_DESTROY()
END_MESSAGE_MAP()

void CSystemDlg::OnBnClickedBtnDashboard()
{
    KillTimer(1004);
    this->EndDialog(IDCANCEL);
    CDashboardDlg dlg;
    dlg.DoModal();
}

void CSystemDlg::OnBnClickedBtnProduction()
{
    KillTimer(1004);
    this->EndDialog(IDCANCEL);
    CProductionDlg dlg;
    dlg.DoModal();
}

void CSystemDlg::OnBnClickedBtnEquip()
{
    KillTimer(1004);
    this->EndDialog(IDCANCEL);
    CEquipDlg dlg;
    dlg.DoModal();
}

void CSystemDlg::OnBnClickedBtnSystem()
{
    // 시스템 구성 버튼은 현재 화면이므로 아무 동작 안함
}

void CSystemDlg::OnBnClickedBtnUser()
{
    // 사용자 권한 관리 버튼 클릭 처리
    MessageBox(_T("사용자 권한 관리 화면으로 이동합니다."), _T("알림"), MB_OK | MB_ICONINFORMATION);
    // 여기에 실제 기능 구현
}

void CSystemDlg::OnBnClickedBtnConfig()
{
    // 시스템 환경 설정 버튼 클릭 처리
    MessageBox(_T("시스템 환경 설정 화면으로 이동합니다."), _T("알림"), MB_OK | MB_ICONINFORMATION);
    // 여기에 실제 기능 구현
}

void CSystemDlg::OnBnClickedBtnLog()
{
    // 로그 및 감사 추적 버튼 클릭 처리
    MessageBox(_T("로그 및 감사 추적 화면으로 이동합니다."), _T("알림"), MB_OK | MB_ICONINFORMATION);
    // 여기에 실제 기능 구현
}

void CSystemDlg::OnBnClickedBtnBackupRestore()
{
    // 데이터 백업 및 복원 버튼 클릭 처리
    MessageBox(_T("데이터 백업 및 복원 화면으로 이동합니다."), _T("알림"), MB_OK | MB_ICONINFORMATION);
    // 여기에 실제 기능 구현
}

BOOL CSystemDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // 다이얼로그 제목 설정
    SetWindowText(_T("시스템 구성 - HIM MES"));

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
    m_btnUser.SetFont(&m_fontWidgetTitle);
    m_btnConfig.SetFont(&m_fontWidgetTitle);
    m_btnLog.SetFont(&m_fontWidgetTitle);
    m_btnBackupRestore.SetFont(&m_fontWidgetTitle);

    // 현재 선택된 메뉴 강조
    m_btnSystem.EnableWindow(FALSE);

    // 위젯 버튼 스타일 설정
    m_btnUser.ModifyStyle(0, BS_OWNERDRAW);
    m_btnConfig.ModifyStyle(0, BS_OWNERDRAW);
    m_btnLog.ModifyStyle(0, BS_OWNERDRAW);
    m_btnBackupRestore.ModifyStyle(0, BS_OWNERDRAW);

    // 위젯 버튼들의 위치와 크기도 조정
    int contentStartX = sidebarWidth + 10;
    int contentWidth = clientRect.Width() - contentStartX - 20;
    int widgetWidth = (contentWidth - 10) / 2;
    int widgetHeight = (clientRect.Height() - 40) / 2;

    m_btnUser.MoveWindow(contentStartX, 20, widgetWidth, widgetHeight - 10);
    m_btnConfig.MoveWindow(contentStartX + widgetWidth + 10, 20, widgetWidth, widgetHeight - 10);
    m_btnLog.MoveWindow(contentStartX, widgetHeight + 20, widgetWidth, widgetHeight - 10);
    m_btnBackupRestore.MoveWindow(contentStartX + widgetWidth + 10, widgetHeight + 20, widgetWidth, widgetHeight - 10);

    // 애니메이션 타이머 설정 (300ms마다 갱신)
    SetTimer(1004, 700, NULL);

    // 깜빡임 방지를 위한 WS_EX_COMPOSITED 스타일 추가
    ModifyStyleEx(0, WS_EX_COMPOSITED);

    return TRUE;
}

void CSystemDlg::OnTimer(UINT_PTR nIDEvent)
{
    if (nIDEvent == 1004)
    {
        // 애니메이션 스텝 증가
        m_nAnimStep = (m_nAnimStep + 1) % 10;
        m_bBlinkState = !m_bBlinkState;

        // 위젯 영역 갱신 (각 위젯마다 별도 갱신)
        CRect rcWidget;

        // 모든 위젯 갱신
        m_btnUser.GetWindowRect(&rcWidget);
        ScreenToClient(&rcWidget);
        InvalidateRect(&rcWidget);

        m_btnConfig.GetWindowRect(&rcWidget);
        ScreenToClient(&rcWidget);
        InvalidateRect(&rcWidget);

        m_btnLog.GetWindowRect(&rcWidget);
        ScreenToClient(&rcWidget);
        InvalidateRect(&rcWidget);

        m_btnBackupRestore.GetWindowRect(&rcWidget);
        ScreenToClient(&rcWidget);
        InvalidateRect(&rcWidget);
    }

    CDialogEx::OnTimer(nIDEvent);
}

void CSystemDlg::OnDestroy()
{
    KillTimer(1004);
    CDialogEx::OnDestroy();
}

void CSystemDlg::OnPaint()
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
    m_btnSystem.GetWindowRect(&btnRect);
    ScreenToClient(&btnRect);

    // 선택된 버튼 왼쪽에 강조 바 그리기
    CRect accentBarRect(0, btnRect.top, 5, btnRect.bottom);
    dc.FillSolidRect(accentBarRect, RGB(41, 182, 246)); // 밝은 파란색

    dc.SelectObject(pOldFont);
    CDialogEx::OnPaint();
}

HBRUSH CSystemDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

void CSystemDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    // 위젯 버튼 그리기
    if (nIDCtl == IDC_BTN_USER || nIDCtl == IDC_BTN_CONFIG ||
        nIDCtl == IDC_BTN_LOG || nIDCtl == IDC_BTN_BACKUP_RESTORE)
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
        case IDC_BTN_USER:
            headerColor = RGB(70, 130, 180);  // 스틸 블루
            break;
        case IDC_BTN_CONFIG:
            headerColor = RGB(72, 61, 139);   // 다크 슬레이트 블루
            break;
        case IDC_BTN_LOG:
            headerColor = RGB(0, 139, 139);   // 다크 시안
            break;
        case IDC_BTN_BACKUP_RESTORE:
            headerColor = RGB(139, 69, 19);   // 새들 브라운
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
        case IDC_BTN_USER:
            DrawUserIcon(&dc, contentRect);
            break;
        case IDC_BTN_CONFIG:
            DrawConfigIcon(&dc, contentRect);
            break;
        case IDC_BTN_LOG:
            DrawLogIcon(&dc, contentRect);
            break;
        case IDC_BTN_BACKUP_RESTORE:
            DrawBackupRestoreIcon(&dc, contentRect);
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

// 사용자 권한 관리 아이콘 그리기
void CSystemDlg::DrawUserIcon(CDC* pDC, CRect rect)
{
    // 사용자 아이콘들 그리기
    int centerX = (rect.left + rect.right) / 2;
    int centerY = (rect.top + rect.bottom - 40) / 2;

    // 사용자 유형 및 색상
    struct UserType {
        CString name;
        COLORREF color;
        int count;
    };

    UserType users[3] = {
        { _T("관리자"), RGB(0, 0, 128), 2 },
        { _T("일반"), RGB(0, 70, 180), 10 }, // "일반 사용자"에서 "일반"으로 변경하여 잘림 방지
        { _T("손님"), RGB(100, 150, 220), 3 }
    };

    // 사용자 아이콘들 배치 - 간격 넓히기
    int iconSize = 60;
    int iconGap = 95; // 간격 증가 (80 -> 95)
    int startX = centerX - (iconGap * (3 - 1)) / 2;

    for (int i = 0; i < 3; i++) {
        int iconX = startX + i * iconGap;
        int iconY = centerY - 20;

        // 사용자 아이콘 외부 원
        CBrush bgBrush(RGB(240, 240, 255));
        CBrush* pOldBrush = pDC->SelectObject(&bgBrush);
        pDC->Ellipse(iconX - iconSize / 2, iconY - iconSize / 2,
            iconX + iconSize / 2, iconY + iconSize / 2);

        // 사용자 아이콘 머리 부분
        CBrush headBrush(users[i].color);
        pDC->SelectObject(&headBrush);
        int headSize = iconSize / 2;
        pDC->Ellipse(iconX - headSize / 2, iconY - headSize / 2,
            iconX + headSize / 2, iconY + headSize / 2);

        // 사용자 유형 텍스트 - 폰트 크기 조정
        CFont nameFont;
        nameFont.CreatePointFont(85, _T("맑은 고딕")); // 폰트 크기 축소
        CFont* pOldFont = pDC->SelectObject(&nameFont);

        pDC->SetTextColor(RGB(50, 50, 50));
        CRect nameRect(iconX - iconSize / 2, iconY + iconSize / 2 + 5,
            iconX + iconSize / 2, iconY + iconSize / 2 + 25);
        pDC->DrawText(users[i].name, nameRect, DT_CENTER | DT_SINGLELINE);

        // 사용자 수 텍스트
        CString countStr;
        countStr.Format(_T("%d명"), users[i].count);
        CRect countRect(nameRect.left, nameRect.bottom, nameRect.right, nameRect.bottom + 20);
        pDC->DrawText(countStr, countRect, DT_CENTER | DT_SINGLELINE);

        pDC->SelectObject(pOldFont);
        nameFont.DeleteObject();
        pDC->SelectObject(pOldBrush);
    }

    // 사용자 통계 정보
    CRect statsRect(rect.left, rect.bottom - 30, rect.right, rect.bottom);
    pDC->FillSolidRect(statsRect, RGB(240, 240, 240));
    pDC->Rectangle(statsRect);

    pDC->SetTextColor(RGB(50, 50, 50));
    CString statsText = _T("총 사용자: 15명 (관리자: 2, 일반: 10, 손님: 3)");
    pDC->DrawText(statsText, statsRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

// 시스템 환경 설정 아이콘 그리기
void CSystemDlg::DrawConfigIcon(CDC* pDC, CRect rect)
{
    // 배경 영역
    pDC->FillSolidRect(rect, RGB(248, 248, 250));
    CPen borderPen(PS_SOLID, 1, RGB(200, 200, 210));
    CPen* pOldPen = pDC->SelectObject(&borderPen);
    pDC->Rectangle(rect);

    // 설정 아이콘 및 시스템 상태 표시
    int centerX = (rect.left + rect.right) / 2;
    int topY = rect.top + 40;

    // 설정 톱니바퀴 그리기 - 더 세련된 디자인
    int gearSize = 80;
    CRect gearRect(centerX - gearSize / 2, topY, centerX + gearSize / 2, topY + gearSize);

    // 그림자 효과
    CRect shadowRect = gearRect;
    shadowRect.OffsetRect(3, 3);
    CBrush shadowBrush(RGB(220, 220, 230));
    CBrush* pOldBrush = pDC->SelectObject(&shadowBrush);
    pDC->Ellipse(shadowRect);

    // 외부 원
    CPen gearPen(PS_SOLID, 2, RGB(72, 61, 139)); // 더 얇고 선명한 선
    pDC->SelectObject(&gearPen);
    CBrush gearBrush(RGB(248, 248, 255)); // 더 밝은 배경
    pDC->SelectObject(&gearBrush);
    pDC->Ellipse(gearRect);

    // 내부 원
    int innerSize = gearSize * 2 / 3;
    CRect innerRect(centerX - innerSize / 2, topY + gearSize / 2 - innerSize / 2,
        centerX + innerSize / 2, topY + gearSize / 2 + innerSize / 2);
    pDC->Ellipse(innerRect);

    // 톱니 - 더 날카롭고 선명하게
    int toothCount = 8;
    double radius = gearSize / 2;
    double innerRadius = innerSize / 2;
    for (int i = 0; i < toothCount; i++) {
        double angle = 2 * 3.14159 * i / toothCount + m_nAnimStep * 0.05; // 애니메이션 회전
        int x1 = centerX + int(radius * cos(angle));
        int y1 = topY + gearSize / 2 + int(radius * sin(angle));
        int x2 = centerX + int(innerRadius * cos(angle));
        int y2 = topY + gearSize / 2 + int(innerRadius * sin(angle));
        pDC->MoveTo(x1, y1);
        pDC->LineTo(x2, y2);
    }

    // 테이블 스타일 업그레이드 - 보라색 테두리의 깔끔한 테이블
    CRect tableRect(rect.left + 20, topY + gearSize + 20, rect.right - 20, rect.bottom - 20);

    // 테이블 외곽선 - 더 선명한 보라색
    CPen tablePen(PS_SOLID, 1, RGB(72, 61, 139));
    pDC->SelectObject(&tablePen);
    pDC->Rectangle(tableRect);

    // 테이블 항목들 - 라이센스 텍스트 수정
    struct StatusItem {
        CString name;
        CString value;
        COLORREF statusColor;
    };

    StatusItem items[3] = {
        { _T("데이터베이스 연결"), _T("정상"), RGB(0, 180, 0) },
        { _T("서버 상태"), _T("정상 가동 중"), RGB(0, 180, 0) },
        { _T("라이센스"), _T("유효 (2026년)"), RGB(0, 180, 0) } // 텍스트 짧게 수정
    };

    int rowHeight = tableRect.Height() / 3;
    for (int i = 0; i < 3; i++) {
        CRect rowRect(tableRect.left, tableRect.top + i * rowHeight,
            tableRect.right, tableRect.top + (i + 1) * rowHeight);

        // 행 구분선 - 얇고 세련된 선
        if (i > 0) {
            CPen separatorPen(PS_SOLID, 1, RGB(220, 220, 235));
            pDC->SelectObject(&separatorPen);
            pDC->MoveTo(rowRect.left, rowRect.top);
            pDC->LineTo(rowRect.right, rowRect.top);
            pDC->SelectObject(&tablePen);
        }

        // 상태 표시등 - 더 선명한 LED 스타일
        CRect statusRect(rowRect.left + 15, rowRect.top + rowHeight / 2 - 5,
            rowRect.left + 25, rowRect.top + rowHeight / 2 + 5);

        // 발광 효과
        if (m_bBlinkState && i == 0) { // 첫 번째 항목에 깜빡임 효과
            CRect glowRect = statusRect;
            glowRect.InflateRect(2, 2);
            CBrush glowBrush(RGB(200, 255, 200));
            pDC->SelectObject(&glowBrush);
            pDC->Ellipse(glowRect);
        }

        CBrush statusBrush(items[i].statusColor);
        pDC->SelectObject(&statusBrush);
        pDC->Ellipse(statusRect);

        // 이름 텍스트 - 더 선명한 서체
        CFont nameFont;
        nameFont.CreateFont(15, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));
        CFont* pOldFont = pDC->SelectObject(&nameFont);

        pDC->SetTextColor(RGB(72, 61, 139)); // 보라색 글자
        CRect nameRect(statusRect.right + 10, rowRect.top, rowRect.right - 100, rowRect.bottom);
        pDC->DrawText(items[i].name, nameRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

        // 값 텍스트 - 더 선명한 녹색
        CFont valueFont;
        valueFont.CreateFont(15, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));
        pDC->SelectObject(&valueFont);
        pDC->SetTextColor(RGB(0, 120, 0));

        CRect valueRect(nameRect.right, rowRect.top, rowRect.right - 15, rowRect.bottom);
        pDC->DrawText(items[i].value, valueRect, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);

        pDC->SelectObject(pOldFont);
        nameFont.DeleteObject();
        valueFont.DeleteObject();
    }

    pDC->SelectObject(pOldPen);
    pDC->SelectObject(pOldBrush);
}


// 로그 및 감사 추적 아이콘 그리기
void CSystemDlg::DrawLogIcon(CDC* pDC, CRect rect)
{
    // 배경 영역
    pDC->FillSolidRect(rect, RGB(248, 248, 250));
    CPen borderPen(PS_SOLID, 1, RGB(200, 200, 210));
    CPen* pOldPen = pDC->SelectObject(&borderPen);
    pDC->Rectangle(rect);

    // 로그 목록 전체 영역 - 약간의 여백 추가
    CRect outerTableRect(rect.left + 15, rect.top + 20, rect.right - 15, rect.bottom - 40);
    pDC->FillSolidRect(outerTableRect, RGB(244, 244, 248));
    pDC->Rectangle(outerTableRect);

    // 실제 테이블 영역
    CRect tableRect(outerTableRect.left + 5, outerTableRect.top + 5,
        outerTableRect.right - 5, outerTableRect.bottom - 5);

    // 테이블 외곽선 - 티얼색 계열
    CPen tablePen(PS_SOLID, 1, RGB(0, 139, 139));
    pDC->SelectObject(&tablePen);
    pDC->Rectangle(tableRect);

    // 테이블 헤더 - 깔끔한 배경
    int headerHeight = 30;
    CRect headerRect(tableRect.left, tableRect.top, tableRect.right, tableRect.top + headerHeight);
    pDC->FillSolidRect(headerRect, RGB(235, 235, 240));

    // 헤더 구분선
    pDC->MoveTo(tableRect.left, headerRect.bottom);
    pDC->LineTo(tableRect.right, headerRect.bottom);

    // 시간/이벤트 열 구분
    int timeColWidth = 130;
    pDC->MoveTo(tableRect.left + timeColWidth, tableRect.top);
    pDC->LineTo(tableRect.left + timeColWidth, tableRect.bottom);

    // 헤더 텍스트 - 더 선명한 서체
    CFont headerFont;
    headerFont.CreateFont(16, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));
    CFont* pOldFont = pDC->SelectObject(&headerFont);

    // 시간 열 헤더
    pDC->SetTextColor(RGB(0, 139, 139)); // 티얼색 글자
    CRect timeHeader(tableRect.left, tableRect.top, tableRect.left + timeColWidth, headerRect.bottom);
    pDC->DrawText(_T("시간"), timeHeader, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    // 이벤트 열 헤더
    CRect eventHeader(timeHeader.right, tableRect.top, tableRect.right, headerRect.bottom);
    pDC->DrawText(_T("이벤트"), eventHeader, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    // 로그 항목 데이터 - 색상 조정
    struct LogEntry {
        CString time;
        CString event;
        COLORREF textColor;
        bool isHighlighted; // 배경색 강조 여부
    };

    LogEntry logs[5] = {
        { _T("2025-04-28 09:15"), _T("시스템 시작"), RGB(0, 100, 200), false },
        { _T("2025-04-27 18:30"), _T("사용자 로그아웃"), RGB(200, 0, 0), true },
        { _T("2025-04-27 16:22"), _T("데이터 변경"), RGB(200, 150, 0), false },
        { _T("2025-04-27 15:18"), _T("보고서 생성"), RGB(100, 0, 150), true },
        { _T("2025-04-27 14:05"), _T("사용자 로그인"), RGB(0, 100, 200), false }
    };

    // 로그 항목 그리기 - 모든 행에 통일된 배경색 적용
    int dataAreaHeight = tableRect.Height() - headerHeight;
    int rowHeight = dataAreaHeight / 5;
    for (int i = 0; i < 5; i++) {
        CRect rowRect(tableRect.left, tableRect.top + headerHeight + i * rowHeight,
            tableRect.right, tableRect.top + headerHeight + (i + 1) * rowHeight);

        // 모든 행에 통일된 회색 배경 적용
        if (logs[i].isHighlighted) {
            // 강조 행은 약간 더 진한 회색
            pDC->FillSolidRect(rowRect, RGB(235, 235, 240));
        }
        else {
            // 나머지 행은 연한 회색
            pDC->FillSolidRect(rowRect, RGB(245, 245, 248));
        }

        // 행 구분선 - 얇고 밝은 선
        pDC->MoveTo(rowRect.left, rowRect.bottom);
        pDC->LineTo(rowRect.right, rowRect.bottom);

        // 시간 텍스트
        CFont timeFont;
        timeFont.CreateFont(15, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));
        pDC->SelectObject(&timeFont);

        pDC->SetTextColor(RGB(80, 80, 100));
        CRect timeCell(rowRect.left + 5, rowRect.top, timeHeader.right - 5, rowRect.bottom);
        pDC->DrawText(logs[i].time, timeCell, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

        // 이벤트 텍스트
        CFont eventFont;
        eventFont.CreateFont(15, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));
        pDC->SelectObject(&eventFont);
        pDC->SetTextColor(logs[i].textColor);

        CRect eventCell(timeHeader.right + 10, rowRect.top, rowRect.right - 5, rowRect.bottom);
        pDC->DrawText(logs[i].event, eventCell, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

        timeFont.DeleteObject();
        eventFont.DeleteObject();
    }

    // 최신 로그 깜빡임 효과 (첫 번째 항목)
    if (m_bBlinkState) {
        CRect highlightRect(tableRect.left, tableRect.top + headerHeight,
            tableRect.right, tableRect.top + headerHeight + rowHeight);
        CPen highlightPen(PS_SOLID, 2, RGB(0, 139, 139));
        pDC->SelectObject(&highlightPen);
        CBrush nullBrush;
        nullBrush.CreateStockObject(NULL_BRUSH);
        CBrush* pOldHighlightBrush = pDC->SelectObject(&nullBrush);
        pDC->Rectangle(highlightRect);
        pDC->SelectObject(pOldHighlightBrush);
    }

    // 로그 통계 정보 - 더 깔끔한 스타일
    CRect statsRect(rect.left + 15, outerTableRect.bottom + 10, rect.right - 15, rect.bottom - 10);
    pDC->SelectObject(&tablePen);
    pDC->Rectangle(statsRect);
    pDC->FillSolidRect(statsRect, RGB(244, 244, 248));

    // 통계 텍스트
    CFont statsFont;
    statsFont.CreateFont(15, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));
    pDC->SelectObject(&statsFont);
    pDC->SetTextColor(RGB(0, 139, 139));

    CString statsText;
    statsText.Format(_T("금일 로그: %d건 | 주간 로그: %d건"), 15, 122);
    pDC->DrawText(statsText, statsRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    pDC->SelectObject(pOldFont);
    statsFont.DeleteObject();
    headerFont.DeleteObject();
    pDC->SelectObject(pOldPen);
}

// 데이터 백업 및 복원 아이콘 그리기
void CSystemDlg::DrawBackupRestoreIcon(CDC* pDC, CRect rect)
{
    // 백업 및 복원 아이콘 그리기
    int centerX = (rect.left + rect.right) / 2;
    int centerY = (rect.top + rect.bottom - 60) / 2;

    // 데이터베이스 아이콘 (왼쪽)
    int dbWidth = 70;
    int dbHeight = 80;
    CRect dbRect(centerX - dbWidth - 20, centerY - dbHeight / 2,
        centerX - 20, centerY + dbHeight / 2);

    // 데이터베이스 몸체
    CBrush dbBrush(RGB(139, 69, 19)); // 갈색
    CBrush* pOldBrush = pDC->SelectObject(&dbBrush);
    CPen dbPen(PS_SOLID, 2, RGB(100, 50, 0));
    CPen* pOldPen = pDC->SelectObject(&dbPen);

    // 데이터베이스 실린더 모양 (타원+사각형+타원)
    CRect topOval(dbRect.left, dbRect.top, dbRect.right, dbRect.top + 20);
    pDC->Ellipse(topOval);

    CRect body(dbRect.left, dbRect.top + 10, dbRect.right, dbRect.bottom - 10);
    pDC->Rectangle(body);

    CRect bottomOval(dbRect.left, dbRect.bottom - 20, dbRect.right, dbRect.bottom);
    pDC->Ellipse(bottomOval);

    // 데이터베이스 줄무늬
    CPen stripePen(PS_SOLID, 1, RGB(255, 200, 150));
    pDC->SelectObject(&stripePen);
    int stripeCount = 3;
    int stripeGap = (dbRect.Height() - 40) / (stripeCount + 1);
    for (int i = 1; i <= stripeCount; i++) {
        int y = dbRect.top + 20 + i * stripeGap;
        pDC->MoveTo(dbRect.left, y);
        pDC->LineTo(dbRect.right, y);
    }

    // 백업 미디어 아이콘 (오른쪽)
    int driveWidth = 60;
    int driveHeight = 40;
    CRect driveRect(centerX + 20, centerY - driveHeight / 2,
        centerX + 20 + driveWidth, centerY + driveHeight / 2);

    // 백업 드라이브 몸체
    CBrush driveBrush(RGB(80, 80, 80));
    pDC->SelectObject(&driveBrush);
    CPen drivePen(PS_SOLID, 2, RGB(50, 50, 50));
    pDC->SelectObject(&drivePen);
    pDC->Rectangle(driveRect);

    // 드라이브 슬롯
    CRect slotRect(driveRect.left + 10, driveRect.top + 5,
        driveRect.right - 10, driveRect.top + 15);
    pDC->FillSolidRect(slotRect, RGB(30, 30, 30));
    pDC->Rectangle(slotRect);

    // 드라이브 LED
    CRect ledRect(driveRect.right - 15, driveRect.bottom - 15,
        driveRect.right - 5, driveRect.bottom - 5);
    if (m_bBlinkState) {
        pDC->FillSolidRect(ledRect, RGB(0, 255, 0));
    }
    else {
        pDC->FillSolidRect(ledRect, RGB(0, 150, 0));
    }
    pDC->Ellipse(ledRect);

    // 백업 방향 화살표
    CPen arrowPen(PS_SOLID, 3, RGB(139, 69, 19));
    pDC->SelectObject(&arrowPen);

    // 애니메이션 위치 계산
    int arrowOffset = (m_nAnimStep % 5) * 2; // 0~8 사이 이동

    // 중앙 라인
    pDC->MoveTo(dbRect.right, centerY);
    pDC->LineTo(driveRect.left, centerY);

    // 화살표 헤드 (애니메이션 적용)
    if (m_bBlinkState) { // 왼쪽 방향 (복원)
        int arrowX = dbRect.right + 20 + arrowOffset;
        pDC->MoveTo(arrowX, centerY - 10);
        pDC->LineTo(arrowX - 15, centerY);
        pDC->LineTo(arrowX, centerY + 10);
    }
    else { // 오른쪽 방향 (백업)
        int arrowX = driveRect.left - 20 - arrowOffset;
        pDC->MoveTo(arrowX, centerY - 10);
        pDC->LineTo(arrowX + 15, centerY);
        pDC->LineTo(arrowX, centerY + 10);
    }

    // 백업 상태 프로그레스 바
    CRect progressRect(rect.left + 20, centerY + dbHeight / 2 + 20,
        rect.right - 20, centerY + dbHeight / 2 + 40);
    pDC->FillSolidRect(progressRect, RGB(220, 220, 220));
    pDC->Rectangle(progressRect);

    // 진행 상태 (75% 완료)
    int progressWidth = progressRect.Width() * 3 / 4;
    CRect filledRect(progressRect.left, progressRect.top,
        progressRect.left + progressWidth, progressRect.bottom);
    pDC->FillSolidRect(filledRect, RGB(139, 69, 19));

    // 백업 정보 테이블
    CRect infoRect(rect.left + 20, progressRect.bottom + 10, rect.right - 20, rect.bottom - 10);

    // 정보 항목들
    struct BackupInfo {
        CString label;
        CString value;
    };

    BackupInfo info[3] = {
        { _T("마지막 백업:"), _T("2025-04-27 23:00") },
        { _T("다음 예정 백업:"), _T("2025-04-28 23:00") },
        { _T("백업 상태:"), _T("정상") }
    };

    // 정보 그리기
    int rowHeight = infoRect.Height() / 3;
    for (int i = 0; i < 3; i++) {
        CRect rowRect(infoRect.left, infoRect.top + i * rowHeight,
            infoRect.right, infoRect.top + (i + 1) * rowHeight);

        // 레이블
        pDC->SetTextColor(RGB(80, 80, 80));
        CRect labelRect(rowRect.left, rowRect.top, rowRect.left + 100, rowRect.bottom);
        pDC->DrawText(info[i].label, labelRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

        // 값 (마지막 항목은 색상 강조)
        if (i == 2) { // 백업 상태
            pDC->SetTextColor(RGB(0, 150, 0));
        }
        else {
            pDC->SetTextColor(RGB(50, 50, 50));
        }

        CRect valueRect(labelRect.right, rowRect.top, rowRect.right, rowRect.bottom);
        pDC->DrawText(info[i].value, valueRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
    }

    pDC->SelectObject(pOldPen);
    pDC->SelectObject(pOldBrush);
}