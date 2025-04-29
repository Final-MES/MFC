// SystemDlg.h
#pragma once

#include "afxdialogex.h"

class CSystemDlg : public CDialogEx
{
    DECLARE_DYNAMIC(CSystemDlg)

public:
    CSystemDlg(CWnd* pParent = nullptr);
    virtual ~CSystemDlg();

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_SYSTEM_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnDestroy();

    // 위젯 그리기 함수들
    void DrawUserIcon(CDC* pDC, CRect rect);
    void DrawConfigIcon(CDC* pDC, CRect rect);
    void DrawLogIcon(CDC* pDC, CRect rect);
    void DrawBackupRestoreIcon(CDC* pDC, CRect rect);

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

    // 시스템 구성 위젯 버튼들
    CButton m_btnUser;           // 사용자 권한 관리
    CButton m_btnConfig;         // 시스템 환경 설정
    CButton m_btnLog;            // 로그 및 감사 추적
    CButton m_btnBackupRestore;  // 데이터 백업 및 복원

    // 애니메이션 변수
    int m_nAnimStep;            // 애니메이션 단계
    bool m_bBlinkState;         // 깜빡임 상태

    DECLARE_MESSAGE_MAP()

public:
    afx_msg void OnBnClickedBtnDashboard();
    afx_msg void OnBnClickedBtnProduction();
    afx_msg void OnBnClickedBtnEquip();
    afx_msg void OnBnClickedBtnSystem();

    // 시스템 구성 위젯 버튼 이벤트 핸들러
    afx_msg void OnBnClickedBtnUser();
    afx_msg void OnBnClickedBtnConfig();
    afx_msg void OnBnClickedBtnLog();
    afx_msg void OnBnClickedBtnBackupRestore();
};