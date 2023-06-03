// CPrint.cpp: 구현 파일
//

#include "pch.h"
#include "Simple_Circle_Test.h"
#include "CPrint.h"
#include "afxdialogex.h"


// CPrint 대화 상자

IMPLEMENT_DYNAMIC(CPrint, CDialogEx)

CPrint::CPrint(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ChildDialog, pParent)
	, mText1(_T(""))
{

}

CPrint::~CPrint()
{
}

void CPrint::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC1, mText1);
}


BEGIN_MESSAGE_MAP(CPrint, CDialogEx)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CPrint 메시지 처리기


HBRUSH CPrint::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	int uiResID = pWnd->GetDlgCtrlID();

	switch (uiResID)
	{
	case IDC_STATIC1:
	{
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkColor(RGB(0, 0, 0));
		break;
	}
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}

// 원정보 출력 화면의 텍스트를 하얀색으로 변경시켜준다.