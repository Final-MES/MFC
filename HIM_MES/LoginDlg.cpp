#include "pch.h"
#include "HIM_MES.h"
#include "LoginDlg.h"
#include "afxdialogex.h"
#include "MainDlg.h" 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CLoginDlg::OnBnClickedButtonLogin)
    ON_STN_CLICKED(IDC_FORGOT_PW, &CLoginDlg::OnStnClickedForgotPw)
    ON_WM_CTLCOLOR()
    ON_WM_DRAWITEM()
END_MESSAGE_MAP()

BOOL CLoginDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    SetWindowText(_T("HIM MES"));
    // 🔷 폰트 설정
    m_fontHeader.CreatePointFont(180, _T("맑은 고딕"));  // 18pt 헤더
    GetDlgItem(IDC_STATIC)->SetFont(&m_fontHeader);

    m_fontLabel.CreatePointFont(100, _T("맑은 고딕"));  // 10pt 라벨
    GetDlgItem(IDC_STATIC_ID)->SetFont(&m_fontLabel);
    GetDlgItem(IDC_STATIC_PW)->SetFont(&m_fontLabel);
    GetDlgItem(IDC_FORGOT_PW)->SetFont(&m_fontLabel);

    m_fontButton.CreatePointFont(100, _T("맑은 고딕 Bold")); // 버튼용
    GetDlgItem(IDC_BUTTON_LOGIN)->SetFont(&m_fontButton);
    m_imageRight.SubclassDlgItem(IDC_STATIC_RIGHT_IMAGE, this);
    m_bmpRight.LoadBitmap(IDB_LOGIN_RIGHT);
    m_imageRight.SetBitmap((HBITMAP)m_bmpRight);

    // Static 클릭 감지 활성화
    GetDlgItem(IDC_FORGOT_PW)->ModifyStyle(0, SS_NOTIFY);

    // 플레이스홀더처럼 안내 문구
    GetDlgItem(IDC_EDIT_ID)->SetWindowText(_T(""));
    GetDlgItem(IDC_EDIT_PW)->SetWindowText(_T(""));

    return TRUE;
}

CLoginDlg::CLoginDlg(CWnd* pParent)
    : CDialogEx(IDD_HIM_MES_DIALOG, pParent)
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

void CLoginDlg::OnBnClickedButtonLogin()
{
    CString id, pw;
    GetDlgItemText(IDC_EDIT_ID, id);
    GetDlgItemText(IDC_EDIT_PW, pw);

    if (id == _T("admin") && pw == _T("1234"))
    {
        EndDialog(IDOK);  // ✅ 여기까지만 하면 InitInstance()로 돌아감
    }
}


void CLoginDlg::OnStnClickedForgotPw()
{
    AfxMessageBox(_T("비밀번호 찾기 기능은 준비 중입니다."));
}

HBRUSH CLoginDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    static HBRUSH hbrBkgnd = ::CreateSolidBrush(RGB(245, 248, 255)); // 연한 하늘색

    // 전체 배경
    if (nCtlColor == CTLCOLOR_DLG)
    {
        return hbrBkgnd;
    }

    // 에디트 컨트롤 배경색 맞추기
    if (nCtlColor == CTLCOLOR_EDIT)
    {
        pDC->SetBkColor(RGB(245, 248, 255)); // 배경을 하늘색으로
        pDC->SetTextColor(RGB(0, 0, 0));     // 텍스트는 검정색
        return hbrBkgnd;
    }

    // Static 컨트롤 (Welcome HIM MES, 라벨 등)
    if (nCtlColor == CTLCOLOR_STATIC)
    {
        pDC->SetBkMode(TRANSPARENT);
        pDC->SetTextColor(RGB(0, 0, 0));
        return hbrBkgnd;
    }

    // 비밀번호 링크 텍스트 색상
    if (pWnd->GetDlgCtrlID() == IDC_FORGOT_PW)
    {
        pDC->SetTextColor(RGB(0, 93, 255));
        pDC->SetBkMode(TRANSPARENT);
        return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
    }

    return CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
}

void CLoginDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    if (nIDCtl == IDC_BUTTON_LOGIN)
    {
        CDC dc;
        dc.Attach(lpDrawItemStruct->hDC);

        CRect rect = lpDrawItemStruct->rcItem;

        // 배경색: 진한 파랑
        dc.FillSolidRect(rect, RGB(0, 93, 255));

        // 테두리: 흰색
        dc.Draw3dRect(rect, RGB(255, 255, 255), RGB(255, 255, 255));

        // 텍스트: 흰색, 가운데 정렬
        dc.SetBkMode(TRANSPARENT);
        dc.SetTextColor(RGB(255, 255, 255));
        dc.SelectObject(GetStockObject(DEFAULT_GUI_FONT));
        dc.DrawText(_T("로그인"), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

        dc.Detach();
        return;
    }

    CDialogEx::OnDrawItem(nIDCtl, lpDrawItemStruct);
}
