// EquipDlg.h
#pragma once

#include "afxdialogex.h"

class CEquipDlg : public CDialogEx
{
    DECLARE_DYNAMIC(CEquipDlg)

public:
    CEquipDlg(CWnd* pParent = nullptr);
    virtual ~CEquipDlg();

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_EQUIP_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnDestroy();
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);


    // 각 위젯에 아이콘 그리기 함수
    void DrawRunStatusIcon(CDC* pDC, CRect rect);
    void DrawMaintPlanIcon(CDC* pDC, CRect rect);
    void DrawMonitoringIcon(CDC* pDC, CRect rect);
    void DrawHistoryIcon(CDC* pDC, CRect rect);

    // UI 관련 멤버 변수
    CBrush m_brushBg;           // 배경색
    CBrush m_brushWidgetBg;     // 위젯 배경색
    CBrush m_brushSidebarBg;    // 사이드바 배경색
    CFont m_fontTitle;          // 제목 폰트
    CFont m_fontWidgetTitle;    // 위젯 제목 폰트
    CFont m_fontMenu;           // 메뉴 폰트
    CFont m_fontContent;        // 내용 폰트

    // 메뉴 버튼들
    CButton m_btnDashboard;
    CButton m_btnProduction;
    CButton m_btnEquipment;
    CButton m_btnSystem;

    // 설비관리 위젯 버튼들
    CButton m_btnRunStatus;      // 설비 가동 현황
    CButton m_btnMaintPlan;      // 예방 정비 계획
    CButton m_btnMonitoring;     // 설비 성능 모니터링
    CButton m_btnHistory;        // 고장 및 정비 이력 관리

    // 애니메이션 변수
    int m_nAnimStep;         // 애니메이션 단계
    bool m_bBlinkState;      // 깜빡임 상태

    DECLARE_MESSAGE_MAP()

public:
    afx_msg void OnBnClickedBtnDashboard();
    afx_msg void OnBnClickedBtnProduction();
    afx_msg void OnBnClickedBtnEquip();
    afx_msg void OnBnClickedBtnSystem();

    // 설비관리 위젯 버튼 이벤트 핸들러
    afx_msg void OnBnClickedBtnRunStatus();
    afx_msg void OnBnClickedBtnMaintPlan();
    afx_msg void OnBnClickedBtnMonitoring();
    afx_msg void OnBnClickedBtnHistory();
};