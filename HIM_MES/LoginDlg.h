#pragma once

class CLoginDlg : public CDialogEx
{
public:
    CLoginDlg(CWnd* pParent = nullptr);

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_HIM_MES_DIALOG }; // ← 정확한 다이얼로그 ID
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    afx_msg void DrawButton(CDC* pDC, CRect rect, const CString& text, BOOL isFocused);
    afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);

    CFont m_fontHeader, m_fontLabel, m_fontButton;

    CStatic m_imageRight;  // ⬅️ 이 줄
    CBitmap m_bmpRight;    // ⬅️ 이 줄

    DECLARE_MESSAGE_MAP()

public:
    afx_msg void OnBnClickedButtonLogin();
    afx_msg void OnStnClickedForgotPw();  // ← Static 클릭 대응
};
