
// LifeView.h : интерфейс класса CLifeView
//

#pragma once


class CLifeView : public CView
{
protected: // создать только из сериализации
	CLifeView();
	DECLARE_DYNCREATE(CLifeView)

// Атрибуты
public:
	CLifeDoc* GetDocument() const;	
	CLifeDoc* pDoc;

	CRect Rc;
	BOOL Timer_on, 
		Flag_button_left, Flag_button_right,
		Flag_old_mode;
// Операции
public:
	void Check_timer(BOOL Flag_on_timer);
	void drawSBow(INT i, INT j, Field Cell, CDC& memDC);
	void drawSBow(INT i, INT j, Field Cell);
	//void 
// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Реализация
public:
	virtual ~CLifeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnIdsNewGame();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnIdsStartLife();
	afx_msg void OnIdsPauseLife();
	afx_msg void OnIdsResetLife();
	afx_msg void OnIdsOption();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // отладочная версия в LifeView.cpp
inline CLifeDoc* CLifeView::GetDocument() const
   { return reinterpret_cast<CLifeDoc*>(m_pDocument); }
#endif

