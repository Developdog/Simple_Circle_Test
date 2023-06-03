
// MovingCirlceView.h: CMovingCirlceView 클래스의 인터페이스
//

#pragma once


class CMovingCirlceView : public CView
{
protected: // serialization에서만 만들어집니다.
	CMovingCirlceView() noexcept;
	DECLARE_DYNCREATE(CMovingCirlceView)

	// 특성입니다.
public:
	CMovingCirlceDoc* GetDocument() const;

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
	virtual ~CMovingCirlceView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	int Circle_Count = 0; // 원 개수 세기
	int Circle_Count_end; // 원의 최대 개수
	CPoint Circle_Location[51]; // 원의 구역
	int Circle_RGB[51][3] = { 0 }; // 원의 색상
	int Circle_Arrow[51]; // 원의 방향성
	int Circle_Move; // 원 이동 끄고 켜기
	int Circle_Size; // 원 반지름
	int Circle_Move_distance; // 원 이동거리
	int Circle_Check[51]; // 간섭 원이 2개 이상이면 해당 원 정지
	int Circle_blue[51][2] = { 0 }; // 간섭 원이 파란색일 경우 탈출하기
	afx_msg void START_STOP();
	afx_msg void OnInfo();
};

#ifndef _DEBUG  // MovingCirlceView.cpp의 디버그 버전
inline CMovingCirlceDoc* CMovingCirlceView::GetDocument() const
   { return reinterpret_cast<CMovingCirlceDoc*>(m_pDocument); }
#endif

