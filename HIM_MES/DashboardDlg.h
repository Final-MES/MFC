// DashboardDlg.h
#pragma once

#include "afxdialogex.h"

class CDashboardDlg : public CDialogEx
{
    DECLARE_DYNAMIC(CDashboardDlg)

public:
    CDashboardDlg(CWnd* pParent = nullptr);
    virtual ~CDashboardDlg();

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_DASHBOARD_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnDestroy();






    // 각 위젯에 아이콘 그리기 함수
    void DrawProductionIcon(CDC* pDC, CRect rect);
    void DrawKPIIcon(CDC* pDC, CRect rect);
    void DrawRealtimeIcon(CDC* pDC, CRect rect);
    void DrawAlertIcon(CDC* pDC, CRect rect);

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

    // 위젯 버튼들
    CButton m_btnProdStat;   // 생산 현황
    CButton m_btnKPI;        // 성과 지표
    CButton m_btnRealtime;   // 실시간 데이터
    CButton m_btnAlert;      // 긴급 알림

    // 애니메이션 변수
    int m_nAnimStep;         // 애니메이션 단계
    bool m_bBlinkState;      // 깜빡임 상태

    DECLARE_MESSAGE_MAP()

public:
    afx_msg void OnBnClickedBtnDashboard();
    afx_msg void OnBnClickedBtnProduction();
    afx_msg void OnBnClickedBtnEquip();
    afx_msg void OnBnClickedBtnSystem();
    afx_msg void OnBnClickedBtnProdStat();
    afx_msg void OnBnClickedBtnKpi();
    afx_msg void OnBnClickedBtnRealtime();
    afx_msg void OnBnClickedBtnAlert();
};