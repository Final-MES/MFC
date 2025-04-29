// ProductionDlg.h
#pragma once

#include "afxdialogex.h"

class CProductionDlg : public CDialogEx
{
    DECLARE_DYNAMIC(CProductionDlg)

public:
    CProductionDlg(CWnd* pParent = nullptr);
    virtual ~CProductionDlg();

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_PRODUCTION_DIALOG };
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
    void DrawPlanIcon(CDC* pDC, CRect rect);
    void DrawScheduleIcon(CDC* pDC, CRect rect);
    void DrawLiveStatusIcon(CDC* pDC, CRect rect);
    void DrawTrackIcon(CDC* pDC, CRect rect);

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

    // 생산관리 위젯 버튼들
    CButton m_btnPlan;           // 생산 계획 수립
    CButton m_btnSchedule;       // 작업 지시 및 일정 관리
    CButton m_btnLiveStatus;     // 실시간 생산 진행 상황
    CButton m_btnTrack;          // 생산 실적 추적

    // 애니메이션 변수
    int m_nAnimStep;         // 애니메이션 단계
    bool m_bBlinkState;      // 깜빡임 상태

    DECLARE_MESSAGE_MAP()

public:
    afx_msg void OnBnClickedBtnDashboard();
    afx_msg void OnBnClickedBtnProduction();
    afx_msg void OnBnClickedBtnEquip();
    afx_msg void OnBnClickedBtnSystem();

    // 생산관리 위젯 버튼 이벤트 핸들러
    afx_msg void OnBnClickedBtnPlan();
    afx_msg void OnBnClickedBtnSchedule();
    afx_msg void OnBnClickedBtnLiveStatus();
    afx_msg void OnBnClickedBtnTrack();
};