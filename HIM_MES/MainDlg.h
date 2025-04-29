#pragma once

// MainDlg.h - 메인 메뉴 다이얼로그 클래스 정의
class MainDlg : public CDialogEx
{
    DECLARE_DYNAMIC(MainDlg)

public:
    MainDlg(CWnd* pParent = nullptr);
    virtual ~MainDlg();

    enum { IDD = IDD_MAIN_DIALOG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

    // 메뉴 버튼들
    CButton m_btnDashboard;
    CButton m_btnProduction;
    CButton m_btnEquipment;
    CButton m_btnSystem;

    // 상태 표시줄
    CStatusBar m_statusBar;

    // 폰트
    CFont m_fontMenu;
    CFont m_fontStatus;

    // 배경 브러시
    CBrush m_brushBg;
    CBrush m_brushButtonBg;
    CBrush m_brushStatusBg;

    // 아이콘
    HICON m_hIcon;

    DECLARE_MESSAGE_MAP()

public:
    afx_msg void OnBnClickedBtnDashboard();
    afx_msg void OnBnClickedBtnProduction();
    afx_msg void OnBnClickedBtnEquipment();
    afx_msg void OnBnClickedBtnSystem();
    afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
};