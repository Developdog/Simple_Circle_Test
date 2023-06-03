
// Simple_Circle_TestView.cpp: CMySimple_Circle_TestView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Simple_Circle_Test.h"
#endif

#include "Simple_Circle_TestDoc.h"
#include "Simple_Circle_TestView.h"
#include "MainFrm.h"
#include "CPrint.h"
#include <cmath>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMySimple_Circle_TestView

IMPLEMENT_DYNCREATE(CMySimple_Circle_TestView, CView)

BEGIN_MESSAGE_MAP(CMySimple_Circle_TestView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
ON_UPDATE_COMMAND_UI(ID_INDICATOR_MOUSE, &CMySimple_Circle_TestView::OnUpdateIndicatorMouse)
ON_WM_MOUSEMOVE()
ON_COMMAND(ID_CIRCLE_COUNT, &CMySimple_Circle_TestView::OnCircleCount)
ON_COMMAND(ID_SELECT_CIRCLE, &CMySimple_Circle_TestView::OnSelectCircle)
ON_COMMAND(ID_SELECT_RECTANGLE, &CMySimple_Circle_TestView::OnSelectRectangle)
ON_COMMAND(ID_CIRCLE_GO_LEFT, &CMySimple_Circle_TestView::OnCircleGoLeft)
ON_COMMAND(ID_CIRCLE_GO_RIGHT, &CMySimple_Circle_TestView::OnCircleGoRight)
ON_COMMAND(ID_MOVE_ALL_CIRCLE, &CMySimple_Circle_TestView::OnMoveAllCircle)
ON_WM_TIMER()
ON_COMMAND(ID_Change_Arraow, &CMySimple_Circle_TestView::OnChangeArraow)
ON_COMMAND(ID_DELETE_CIRCLE, &CMySimple_Circle_TestView::OnDeleteCircle)
END_MESSAGE_MAP()

// CMySimple_Circle_TestView 생성/소멸

CMySimple_Circle_TestView::CMySimple_Circle_TestView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	Name_Width = 0;
	Name_Height = 0;
	color_Select = 0;
	Shape_Select = 0;
	count = 0;
	Select_arrow = 0;
	Select_Delete = 0;
}

CMySimple_Circle_TestView::~CMySimple_Circle_TestView()
{
}

BOOL CMySimple_Circle_TestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMySimple_Circle_TestView 그리기

void CMySimple_Circle_TestView::OnDraw(CDC* /*pDC*/)
{
	CMySimple_Circle_TestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	CClientDC dc(this);
	CRect background_size; // 화면의 크기 값 변수 선언
	GetClientRect(&background_size); // 화면의 현재 크기 값 얻어오기
	int background_division = background_size.right / 8; // 배경화면 값을 8로 나눴을때의 값
	CBrush background_brush(RGB(0, 0, 0)); // 배경화면 검은색 값 브러쉬 설정
	COLORREF Color[3]{ RGB(255, 0, 0), RGB(0, 255, 0), RGB(0, 0, 255) }; // 도형 색상 브러쉬 값

	dc.SelectObject(&background_brush); // 배경화면 브러쉬 툴 선택
	dc.Rectangle(0, 0, background_division, background_size.bottom);  // 화면 왼쪽 직사각형 그리기
	dc.Rectangle(background_size.right - background_division, 0, background_size.right, background_size.bottom); // 화면 오른쪽 직사각형 그리기
																																																																					  
	for (int i = 0; i < count; i++)
	{
		CBrush bs(Color[Shape_color[i]]);
		dc.SelectObject(&bs);
		if (Shape_result[i] == 0)
		{
			dc.Ellipse(Shape[i].x - 25, Shape[i].y - 25, Shape[i].x + 25, Shape[i].y + 25);
			dc.SetBkMode(TRANSPARENT);
			dc.SetTextColor(RGB(255, 255, 255 ));
			if (Shape_arrow[i] == 0) dc.DrawText(L"↗", CRect(Shape[i].x - 25, Shape[i].y - 25, Shape[i].x + 25, Shape[i].y + 25), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			if (Shape_arrow[i] == 1) dc.DrawText(L"↖", CRect(Shape[i].x - 25, Shape[i].y - 25, Shape[i].x + 25, Shape[i].y + 25), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			if (Shape_arrow[i] == 2) dc.DrawText(L"↙", CRect(Shape[i].x - 25, Shape[i].y - 25, Shape[i].x + 25, Shape[i].y + 25), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			if (Shape_arrow[i] == 3) dc.DrawText(L"↘", CRect(Shape[i].x - 25, Shape[i].y - 25, Shape[i].x + 25, Shape[i].y + 25), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
		else if (Shape_result[i] == 1)
		{
			dc.Rectangle(Shape[i].x - 25, Shape[i].y - 25, Shape[i].x + 25, Shape[i].y + 25);
		}
	}
	dc.SetBkMode(TRANSPARENT); // 해당 텍스트의 음영부분을 투명하게 해주는 명령어
	dc.SetTextColor(RGB(112, 112, 112));
	dc.DrawText(L"Test_Page", CRect((background_size.right / 2) + Name_Width - 100, (background_size.bottom / 2) + Name_Height - 50, (background_size.right / 2) + Name_Width + 100, (background_size.bottom / 2) + Name_Height + 50), DT_CENTER | DT_VCENTER | DT_SINGLELINE); // 이름 정중앙에 출력하기

}
// Count를 사용한 이때까지 받아온 원 및 사각형 출력하기, 원을 출력할 시에, 방향을 설정하여 출력하기

// CMySimple_Circle_TestView 인쇄

BOOL CMySimple_Circle_TestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMySimple_Circle_TestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMySimple_Circle_TestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMySimple_Circle_TestView 진단

#ifdef _DEBUG
void CMySimple_Circle_TestView::AssertValid() const
{
	CView::AssertValid();
}

void CMySimple_Circle_TestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMySimple_Circle_TestDoc* CMySimple_Circle_TestView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMySimple_Circle_TestDoc)));
	return (CMySimple_Circle_TestDoc*)m_pDocument;
}
#endif //_DEBUG


// CMySimple_Circle_TestView 메시지 처리기


void CMySimple_Circle_TestView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nChar == VK_UP)
		Name_Height -= 5;
	else if (nChar == VK_DOWN)
		Name_Height += 5;
	else if (nChar == VK_LEFT)
		Name_Width -= 5;
	else if (nChar == VK_RIGHT)
		Name_Width += 5;

	Invalidate();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
// 방향키를 눌렀을 경우 이름을 이동시켜주는 함수


void CMySimple_Circle_TestView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CClientDC dc(this);
	CRect background_size; // 화면의 크기 값 변수 선언
	GetClientRect(&background_size); // 화면의 현재 크기 값 얻어오기
	int background_division = background_size.right / 8; // 배경화면 값을 8로 나눴을때의 값


	if (Select_Delete == 1)
	{
		for (int alpha = count; alpha >= 0; alpha--)
		{

			if(Shape_result[alpha] == 0){
				double ceta = sqrt(pow((double)Shape[alpha].x - point.x, 2) + pow((double)Shape[alpha].y - point.y, 2));
				if (ceta < 25) {
						Shape_result[alpha] = 2;
						Shape[alpha].x = 0;
						Shape[alpha].y = 0;
						Invalidate();
						return;
				}
			}
			if (Shape_result[alpha] == 1) {
				if (Shape[alpha].x - 25 < point.x && Shape[alpha].x + 25 > point.x) {
					if (Shape[alpha].y - 25 < point.y && Shape[alpha].y + 25 > point.y) {
						Shape_result[alpha] = 2;
						Shape[alpha].x = 0;
						Shape[alpha].y = 0;
						Invalidate();
						return;
					}
				}
			}
		}
		return;
	}
	// 삭제 토큰이 활성화되어 있으면, 해당 도형 출력 비활성화

	if (Select_arrow == 1)
	{
		for (int alpha = count; alpha >= 0; alpha--)
		{
			double ceta = sqrt(pow((double)Shape[alpha].x - point.x, 2) + pow((double)Shape[alpha].y - point.y, 2));
			if (ceta < 25) {
					Shape_arrow[alpha] = (Shape_arrow[alpha] + 1) % 4;
					Invalidate();
					return;
			}
		}
		return;
	}
	// 방향 변경 토큰이 활성화 되어 있으면, 해당 원 방향 변경


	// 그릴 위치에 이미 도형이 있으면 색만 변경
	for (int alpha = count; alpha >= 0; alpha--)
	{
		if (Shape_result[alpha] == 0) {
			double ceta = sqrt(pow((double)Shape[alpha].x - point.x, 2) + pow((double)Shape[alpha].y - point.y, 2));
			if (ceta < 25) {
				Shape_color[alpha] = (Shape_color[alpha] + 1) % 3;
				Invalidate();
				return;
			}
		}


		if (Shape_result[alpha] == 1) {
			if (Shape[alpha].x - 25 < point.x && Shape[alpha].x + 25 > point.x) {
				if (Shape[alpha].y - 25 < point.y && Shape[alpha].y + 25 > point.y) {
					Shape_color[alpha] = (Shape_color[alpha] + 1) % 3;
					Invalidate();
					return;
				}
			}
		}
	}

	if (point.x > 0 && point.x < background_division && point.y > 0 && point.y < background_size.bottom) return;
	else if (point.x > background_size.right - background_division && point.x < background_size.right && point.y > 0 && point.y < background_size.bottom) return;
	// 만약 배경화면의 검은색 부분을 눌렀을 경우 원이 출력되지 않음.

	if (Shape_Select == 0) 
	{
		for (int alpha = 0; alpha <= count; alpha++)
		{
			double ceta = sqrt(pow((double)point.x - Shape[alpha].x, 2) + pow((double)point.y - Shape[alpha].y, 2));
			if (ceta < 50 && Shape_result[alpha] == 0)
			{
				MessageBox(L"원 끼리는 겹치게 놓을 수 없습니다.", L"오류 발생!");
				return;
			}
		}
	}
	// 만약 다른 원과 위치가 겹쳤을 경우 해당 위치에 놓을 수 없게 함.

	Shape_result[count] = Shape_Select;
	Shape_color[count] = color_Select;
	color_Select = (color_Select + 1) % 3;
	Shape[count] = point;
	Shape_arrow[count] = rand() % 4;
	count++;
	// 도형 그리기	

	Invalidate();

	CView::OnLButtonDown(nFlags, point);
}

// 함수 설정 전 UP COMMAND UI에 해당 함수 처리기 필요

void CMySimple_Circle_TestView::OnUpdateIndicatorMouse(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(); // 상태바 갱신

	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}
//

void CMySimple_Circle_TestView::OnMouseMove(UINT nFlags, CPoint point)
{
	CString Mouse;
	Mouse.Format(L"마우스 좌표 (%4d, %4d)", point.x, point.y); // 마우스 좌표 출력
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	pMainFrame->SetMouse(1, Mouse); // ID_INDICATOR_MOUSE 배열 요소값, 문자열

	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CView::OnMouseMove(nFlags, point);
}
//마우스 좌표 출력 처리 함수

void CMySimple_Circle_TestView::OnCircleCount()
{
	CClientDC dc(this);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	int Red = 0, Blue = 0, Green = 0;
	for (int alpha = 0; alpha < count; alpha++)
	{
		if (Shape_result[alpha] == 0) {
			if (Shape_color[alpha] == 0) Red++;
			else if (Shape_color[alpha] == 1) Green++;
			else if (Shape_color[alpha] == 2) Blue++;
		}
	}

	CPrint Circleprint;
	Circleprint.mText1.Format(L"Red : %d  Blue : %d  GREEN : %d	      Total : %d", Red, Blue, Green, Red + Blue + Green);
	Circleprint.DoModal();
	Circleprint.DestroyWindow();

}
// 원의 모든 색깔 값을 받아서 해당되는 변수에 더한 뒤 값을 모아 출력한다.

void CMySimple_Circle_TestView::OnSelectCircle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	Shape_Select = 0;
}
// 원을 선택했을 경우 Shape_Select 값을 변경시켜준다.

void CMySimple_Circle_TestView::OnSelectRectangle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	Shape_Select = 1;
}
// 사각형을 선택했을 경우 Shpae_Select 값을 변경시켜준다.

void CMySimple_Circle_TestView::OnCircleGoLeft()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	for (int alpha = 0; alpha < count; alpha++)
	{
		if (Shape_result[alpha] == 0) {
			Shape[alpha].x = Shape[alpha].x - 5;
		}
	}
	Invalidate();
}
// 모든 원을 왼쪽으로 5픽셀 이동시킨다.

void CMySimple_Circle_TestView::OnCircleGoRight()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	for (int alpha = 0; alpha < count; alpha++)
	{
		if (Shape_result[alpha] == 0) {
			Shape[alpha].x = Shape[alpha].x + 5;
		}
	}
	Invalidate();
}
// 모든 원을 오른쪽으로 5픽셀 이동시킨다.




void CMySimple_Circle_TestView::OnMoveAllCircle()
{
	if (Circle_Move == 0){
		Circle_Move = 1;
		SetTimer(0, 40, NULL);
	}
	else if (Circle_Move == 1)
	{
		Circle_Move = 0;
		KillTimer(0);
	}
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}
// S 버튼 타이머 끄고 키기

void CMySimple_Circle_TestView::OnTimer(UINT_PTR nIDEvent)
{
	CRect background_size; // 화면의 크기 값 변수 선언
	GetClientRect(&background_size); // 화면의 현재 크기 값 얻어오기

	// 이동하는 원의 방향을 바꿀 필요가 있는지 확인하는 for문
	for (int alpha = 0; alpha <= count; alpha++)
	{
		if (Shape_result[alpha] == 0)
		{
			switch (Shape_arrow[alpha]) {

			case 0:
				if (Shape[alpha].y < 25) {
					Shape_arrow[alpha] = 3;
					break;
				}
				if (Shape[alpha].x > background_size.right - 25) {
					Shape_arrow[alpha] = 1;
					break;
				}

				for (int beta = 0; beta <= count; beta++) {
					if (beta != alpha) {
						if (Shape_result[beta] == 0)
						{
							if (Shape_color[alpha] == Shape_color[beta])
							{
								double ceta = sqrt(pow((double)Shape[alpha].x - Shape[beta].x, 2) + pow((double)Shape[alpha].y - Shape[beta].y, 2));
								if (ceta < 50)
								{
									Shape_arrow[alpha] = 2;
									break;
								}
							}
						}
						//점과 점사이의 거리가 50 미만일 경우 어디서 오는가에 따라서 if문을 써주어 정리해야함.
					}
				}break;



			case 1:

				if (Shape[alpha].x < 25) {
					Shape_arrow[alpha] = 0;
					break;
				}
				if (Shape[alpha].y < 25) {
					Shape_arrow[alpha] = 2;
					break;
				}

				for (int beta = 0; beta <= count; beta++) {
					if (beta != alpha) {
						if (Shape_result[beta] == 0)
						{
							if (Shape_color[alpha] == Shape_color[beta])
							{
								double ceta = sqrt(pow((double)Shape[alpha].x - Shape[beta].x, 2) + pow((double)Shape[alpha].y - Shape[beta].y, 2));
								if (ceta < 50)
								{
									Shape_arrow[alpha] = 3;
									break;
								}
							}
						}
					}
				}break;

			case 2:

				if (Shape[alpha].x < 25) {
					Shape_arrow[alpha] = 3;
					break;
				}
				if (Shape[alpha].y > background_size.bottom - 25) {
					Shape_arrow[alpha] = 1;
					break;
				}


				for (int beta = 0; beta <= count; beta++) {
					if (beta != alpha) {
						if (Shape_result[beta] == 0)
						{
							if (Shape_color[alpha] == Shape_color[beta])
							{
								double ceta = sqrt(pow((double)Shape[alpha].x - Shape[beta].x, 2) + pow((double)Shape[alpha].y - Shape[beta].y, 2));
								if (ceta < 50)
								{
									if(Shape)
									Shape_arrow[alpha] = 0;
									break;
								}
							}
						}
					}
				}break;


			case 3:

				if (Shape[alpha].x > background_size.right - 25) {
					Shape_arrow[alpha] = 2;
					break;
				}
				if (Shape[alpha].y > background_size.bottom - 25) {
					Shape_arrow[alpha] = 0;
					break;
				}


				for (int beta = 0; beta <= count; beta++) {
					if (beta != alpha) {
						if (Shape_result[beta] == 0)
						{
							if (Shape_color[alpha] == Shape_color[beta])
							{
								double ceta = sqrt(pow((double)Shape[alpha].x - Shape[beta].x, 2) + pow((double)Shape[alpha].y - Shape[beta].y, 2));
								if (ceta < 50)
								{
									Shape_arrow[alpha] = 1;
									break;
								}
							}
						}
					}
				}break;

			}
		}
	}
	// 조건
	// 일단 같은 alpha값이 아니며, 도형의 형태가 원이며, 같은 색깔이고, 원의 중심 사이의 거리가 50미만일 경우 해당 값을 반대로 놓아주며 return 해줌.
	//for문을 한번 더 만들어주는 이유는, 비껴나갈때, 방향이 바뀌는 버벅거림을 줄이기 위해서이다.
	for (int alpha = 0; alpha <= count; alpha++)
	{
		if(Shape_result[alpha] == 0)
			switch (Shape_arrow[alpha]) {
			case 0:
				Shape[alpha].x += 5;
				Shape[alpha].y -= 5;
				break;
			case 1:
				Shape[alpha].x -= 5;
				Shape[alpha].y -= 5;
				break;
			case 2:
				Shape[alpha].x -= 5;
				Shape[alpha].y += 5;
				break;
			case 3:
				Shape[alpha].x += 5;
				Shape[alpha].y += 5;
				break;
			}
	}
	//원 경로 변경 관련 스위치구문
	Invalidate();
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CView::OnTimer(nIDEvent);
}
// 원을 각자 맞게 이동시켜주며, 만약 같은 색의 원이나 벽에 부딪혔을 경우 경로를 변경한다.


void CMySimple_Circle_TestView::OnChangeArraow()
{
	if (Select_arrow == 0) {
		MessageBox(L"방향 바꾸기 버튼 활성화", L"알림");
		Select_arrow = 1;
		return;
	}
	else if (Select_arrow == 1) {
		Select_arrow = 0;
		MessageBox(L"방향 바꾸기 버튼 비활성화", L"알림");
		return;
	}
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}
//방향 바꾸기 버튼 활성화/비활성화 함수

void CMySimple_Circle_TestView::OnDeleteCircle()
{
	if (Select_Delete == 0) {
		MessageBox(L"도형 삭제 버튼 활성화", L"알림");
		Select_Delete = 1;
		return;
	}
	else if (Select_Delete == 1) {
		MessageBox(L"도형 삭제 버튼 비활성화", L"알림");
		Select_Delete = 0;
		return;
	}
	// TODO: 여기에 명령 처리기 코드를 추가합니다
	
}
//도형 삭제 버튼 활성화/비활성화 함수
