
// Simple_Circle_TestView.h: CMySimple_Circle_TestView 클래스의 인터페이스
//

#pragma once


class CMySimple_Circle_TestView : public CView
{
protected: // serialization에서만 만들어집니다.
	CMySimple_Circle_TestView() noexcept;
	DECLARE_DYNCREATE(CMySimple_Circle_TestView)

// 특성입니다.
public:
	CMySimple_Circle_TestDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMySimple_Circle_TestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	int Name_Height;
	int Name_Width;
	int color_Select; //  색깔 정하는 변수
	int Shape_Select; // 도형 정하는 변수
	int count; // 현재까지 사용한 도형의 개수
	CPoint Shape[100]; // 도형의 좌표
	int Shape_result[100]; // 선택한 도형의 모양 원은 0, 직사각형은 1, 2는 도형 삭제
	short int Shape_color[100]; // 도형의 색깔
	int Shape_arrow[100] = {}; // 도형의 이동 방향
	int Circle_Move = 0; // S 버튼을 키고 끌수 있게 한다.
	int Select_arrow; // 도형 방향을 선택할 수 있게 한다, 
	int Select_Delete; // 도형 삭제를 선택할 수 있게 한다, 

	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnUpdateMousepoint(CCmdUI* pCmdUI);
	afx_msg void OnUpdateIndicatorMousepoint(CCmdUI* pCmdUI);
	afx_msg void OnUpdateIndicatorMouse(CCmdUI* pCmdUI);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnCircleCount();
	afx_msg void OnSelectCircle();
	afx_msg void OnSelectRectangle();
	afx_msg void OnCircleGoLeft();
	afx_msg void OnCircleGoRight();
	afx_msg void OnMoveAllCircle();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	afx_msg void OnLeftdown();
//	afx_msg void OnLeftup();
//	afx_msg void OnRightdown();
//	afx_msg void OnRightup();
	afx_msg void OnChangeArraow();
	afx_msg void OnDeleteCircle();
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

#ifndef _DEBUG  // Simple_Circle_TestView.cpp의 디버그 버전
inline CMySimple_Circle_TestDoc* CMySimple_Circle_TestView::GetDocument() const
   { return reinterpret_cast<CMySimple_Circle_TestDoc*>(m_pDocument); }
#endif

