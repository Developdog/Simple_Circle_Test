
// MovingCirlceView.cpp: CMovingCirlceView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MovingCirlce.h"
#endif

#include "MovingCirlceDoc.h"
#include "MovingCirlceView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMovingCirlceView

IMPLEMENT_DYNCREATE(CMovingCirlceView, CView)

BEGIN_MESSAGE_MAP(CMovingCirlceView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_START_STOP, &CMovingCirlceView::START_STOP)
	ON_COMMAND(ID_INFO, &CMovingCirlceView::OnInfo)
END_MESSAGE_MAP()

// CMovingCirlceView 생성/소멸

CMovingCirlceView::CMovingCirlceView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	Circle_Count = 0;
	Circle_Move = 0;
	Circle_Size = 20;
	Circle_Count_end = 49;
	Circle_Move_distance = 5;
}

CMovingCirlceView::~CMovingCirlceView()
{
}

BOOL CMovingCirlceView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMovingCirlceView 그리기

void CMovingCirlceView::OnDraw(CDC* /*pDC*/)
{
	CMovingCirlceDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CClientDC dc(this);
	
	CDC memDC; //더블 버퍼링 사용하기
	CBitmap Bitmap, * oldBitmap;
	CRect rc;
	CString Text1;
	GetClientRect(&rc);

	memDC.CreateCompatibleDC(&dc);
	Bitmap.CreateCompatibleBitmap(&dc, rc.right, rc.bottom);
	oldBitmap = memDC.SelectObject(&Bitmap);

	memDC.SelectStockObject(WHITE_BRUSH);
	memDC.Rectangle(0, 0, rc.right, rc.bottom);

	for (int alpha = 0; alpha < Circle_Count; alpha++) { // 해당 원이 빨간색인 경우 원을 그려주면서 화살표 값을 넣어준다.
		CBrush Circlecolor = RGB(Circle_RGB[alpha][0], Circle_RGB[alpha][1], Circle_RGB[alpha][2]);
		memDC.SelectObject(&Circlecolor);
		memDC.Ellipse(Circle_Location[alpha].x - Circle_Size, Circle_Location[alpha].y - Circle_Size,
			Circle_Location[alpha].x + Circle_Size, Circle_Location[alpha].y + Circle_Size);

		memDC.SetBkMode(TRANSPARENT);
		memDC.SetTextColor(RGB(255, 255, 255));
		if (Circle_RGB[alpha][0] > 1) {
			if (Circle_Arrow[alpha] == 1) memDC.DrawText(L"↗", CRect(Circle_Location[alpha].x - Circle_Size, Circle_Location[alpha].y - Circle_Size, Circle_Location[alpha].x + Circle_Size, Circle_Location[alpha].y + Circle_Size), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			if (Circle_Arrow[alpha] == 2) memDC.DrawText(L"↖", CRect(Circle_Location[alpha].x - Circle_Size, Circle_Location[alpha].y - Circle_Size, Circle_Location[alpha].x + Circle_Size, Circle_Location[alpha].y + Circle_Size), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			if (Circle_Arrow[alpha] == 3) memDC.DrawText(L"↙", CRect(Circle_Location[alpha].x - Circle_Size, Circle_Location[alpha].y - Circle_Size, Circle_Location[alpha].x + Circle_Size, Circle_Location[alpha].y + Circle_Size), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			if (Circle_Arrow[alpha] == 4) memDC.DrawText(L"↘", CRect(Circle_Location[alpha].x - Circle_Size, Circle_Location[alpha].y - Circle_Size, Circle_Location[alpha].x + Circle_Size, Circle_Location[alpha].y + Circle_Size), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
	}
	// 현재 사용중인 원 개수 출력
	memDC.SetTextColor(RGB(0, 0, 0));
	Text1.Format(_T("현재 사용중인 원 개수 : %d / 50"), Circle_Count);
	memDC.DrawText(Text1, CRect((rc.right / 2) - 200, (rc.bottom / 2) - 200, (rc.right / 2) + 200, (rc.bottom / 2) + 200), DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	dc.BitBlt(0, 0, rc.right, rc.bottom, &memDC, 0, 0, SRCCOPY);
	memDC.SelectObject(oldBitmap);

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CMovingCirlceView 인쇄

BOOL CMovingCirlceView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMovingCirlceView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMovingCirlceView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMovingCirlceView 진단

#ifdef _DEBUG
void CMovingCirlceView::AssertValid() const
{
	CView::AssertValid();
}

void CMovingCirlceView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMovingCirlceDoc* CMovingCirlceView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMovingCirlceDoc)));
	return (CMovingCirlceDoc*)m_pDocument;
}
#endif //_DEBUG


// CMovingCirlceView 메시지 처리기


void CMovingCirlceView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CClientDC dc(this);
	CRect rect;
	GetClientRect(&rect);

	// 이동방향대로 움직이고, 충돌하면 튕겨나오고, 밖으로 안나가게 하며, 색깔 변경하기
	for (int alpha = 0; alpha <= Circle_Count; alpha++) {
		if (Circle_RGB[alpha][0] > 1) { // 벽에 부딪쳤을 경우

			if (rect.right - Circle_Location[alpha].x < Circle_Size) {
				if (Circle_Arrow[alpha] == 1) Circle_Arrow[alpha] = 2;
				if (Circle_Arrow[alpha] == 4) Circle_Arrow[alpha] = 3;
				Circle_RGB[alpha][0] -= 5;
				Circle_RGB[alpha][2] += 5;
			}
			else if (Circle_Location[alpha].x - rect.left < Circle_Size) {
				if (Circle_Arrow[alpha] == 2) Circle_Arrow[alpha] = 1;
				if (Circle_Arrow[alpha] == 3) Circle_Arrow[alpha] = 4;
				Circle_RGB[alpha][0] -= 5;
				Circle_RGB[alpha][2] += 5;
			}
			else if (rect.bottom - Circle_Location[alpha].y < Circle_Size) {
				if (Circle_Arrow[alpha] == 3) Circle_Arrow[alpha] = 2;
				if (Circle_Arrow[alpha] == 4) Circle_Arrow[alpha] = 1;
				Circle_RGB[alpha][0] -= 5;
				Circle_RGB[alpha][2] += 5;
			}
			else if (Circle_Location[alpha].y - rect.top < Circle_Size) {
				if (Circle_Arrow[alpha] == 1) Circle_Arrow[alpha] = 4;
				if (Circle_Arrow[alpha] == 2) Circle_Arrow[alpha] = 3;
				Circle_RGB[alpha][0] -= 5;
				Circle_RGB[alpha][2] += 5;
			}


			for (int beta = 0; beta <= Circle_Count; beta++) { // 원끼리 부딪쳤을 경우
				if (alpha != beta) {
					double Circle_line = sqrt(pow(double(Circle_Location[alpha].x - Circle_Location[beta].x), 2) + pow(double(Circle_Location[alpha].y - Circle_Location[beta].y), 2));
					if (Circle_line <= Circle_Size * 2) {
						Circle_Check[alpha] += 1; // 2개 이상의 원이 하나에 간섭되도 해당 원은 방향을 바꾸지 않는다.
						if (Circle_Check[alpha] >= 2) break;
						switch (Circle_Arrow[alpha]) {
						case 1:
							Circle_Arrow[alpha] = 3;
							break;
						case 2:
							Circle_Arrow[alpha] = 4;
							break;
						case 3:
							Circle_Arrow[alpha] = 1;
							break;
						case 4:
							Circle_Arrow[alpha] = 2;
							break;
						}
						Circle_RGB[alpha][0] -= 5;
						Circle_RGB[alpha][2] += 5;
						if (Circle_RGB[beta][0] < 1) { // 만약 마지막에 파란색 원이 겹쳐서 종료됬을 경우 추가로 이동을 시켜준다.
							Circle_blue[alpha][0] = 1;
							Circle_blue[alpha][1] = (Circle_Size * 2 - Circle_line)+1;
						}
					}

				}
			}
		}
	}
		// 다 부딫혔을 경우에도 끝낼 수 있게 하기

		for (int alpha = 0; alpha <= Circle_Count; alpha++) {
			if (Circle_RGB[alpha][0] > 1) {
				if (Circle_Arrow[alpha] == 1) {
					Circle_Location[alpha].x += Circle_Move_distance;
					Circle_Location[alpha].y -= Circle_Move_distance;
				}
				if (Circle_Arrow[alpha] == 2) {
					Circle_Location[alpha].x -= Circle_Move_distance;
					Circle_Location[alpha].y -= Circle_Move_distance;
				}
				if (Circle_Arrow[alpha] == 3) {
					Circle_Location[alpha].x -= Circle_Move_distance;
					Circle_Location[alpha].y += Circle_Move_distance;
				}
				if (Circle_Arrow[alpha] == 4) {
					Circle_Location[alpha].x += Circle_Move_distance;
					Circle_Location[alpha].y += Circle_Move_distance;
				}
				Circle_Check[alpha] = 0;
			}
			if (Circle_RGB[alpha][0] > 1 && Circle_blue[alpha][0] == 1) {// 만약 마지막에 파란색 원이 겹쳐서 종료됬을 경우 추가로 이동을 시켜준다.
				if (Circle_Arrow[alpha] == 1) {
					Circle_Location[alpha].x += Circle_blue[alpha][1];
					Circle_Location[alpha].y -= Circle_blue[alpha][1];
				}
				if (Circle_Arrow[alpha] == 2) {
					Circle_Location[alpha].x -= Circle_blue[alpha][1];
					Circle_Location[alpha].y -= Circle_blue[alpha][1];
				}
				if (Circle_Arrow[alpha] == 3) {
					Circle_Location[alpha].x -= Circle_blue[alpha][1];
					Circle_Location[alpha].y += Circle_blue[alpha][1];
				}
				if (Circle_Arrow[alpha] == 4) {
					Circle_Location[alpha].x += Circle_blue[alpha][1];
					Circle_Location[alpha].y += Circle_blue[alpha][1];
				}
				Circle_blue[alpha][0] = 0;
			}
		}

		Invalidate();
		CView::OnTimer(nIDEvent);
}


void CMovingCirlceView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (nChar == VK_SPACE) START_STOP();
	if (nChar == 0x49) OnInfo();
	// 키 다운 관련 값
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CMovingCirlceView::OnLButtonDown(UINT nFlags, CPoint point)  // 왼쪽 마우스 클릭 = 원 생성
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	CClientDC dc(this);
	CRect rect;
	GetClientRect(&rect);

	if (Circle_Count > Circle_Count_end) {
		MessageBox(L"최대 한계치에 도달했습니다.", L"오류!", MB_ICONSTOP);
		return;
	}

	if(rect.right - point.x < Circle_Size || rect.bottom - point.y < Circle_Size || point.x < Circle_Size || point.y < Circle_Size) {
		MessageBox(L"화면 밖으로 놓을 수 없습니다..", L"오류!", MB_ICONSTOP);
		return;
	}
	for (int alpha = 0; alpha < Circle_Count; alpha++) {
		if (abs(point.x - Circle_Location[alpha].x) < Circle_Size*2 && abs(point.y - Circle_Location[alpha].y) < Circle_Size*2) {
			MessageBox(L"원은 서로 겹치게 놓을 수 없습니다.", L"오류!" ,MB_ICONSTOP);
			return;
		}
	}

	
	// 만약 근처에 원이 겹칠 경우, 혹은 밖으로 나갈 경우, return 처리하기, 없을 경우에는 출력하기
	
	Circle_Location[Circle_Count].x = point.x;
	Circle_Location[Circle_Count].y = point.y;
	Circle_RGB[Circle_Count][0] = 255;
	Circle_Arrow[Circle_Count] = rand()%4+1;
	Circle_Count += 1;

	Invalidate();

	CView::OnLButtonDown(nFlags, point);
}


BOOL CMovingCirlceView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return false;
		//CView::OnEraseBkgnd(pDC);
}


void CMovingCirlceView::START_STOP()
{
	if (Circle_Move == 0) {
			SetTimer(0, 20, NULL);
			Circle_Move = !Circle_Move;
	}
	else if (Circle_Move == 1) {
			KillTimer(0);
			Circle_Move = !Circle_Move;
	}// 시작 및 정지
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CMovingCirlceView::OnInfo()
{
	int beta = 0;
	int theta = 0;
	CString sign;

	for (int alpha = 0; alpha < Circle_Count; alpha++) {
		if (Circle_RGB[alpha][0] > 1) beta += 1;
		if (Circle_RGB[alpha][0] < 1) theta += 1;
	}

	sign.Format(_T("활동중인 원 : %d  정지한 원 : %d"), beta, theta);
	MessageBox(sign, L"원 정보");
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}
