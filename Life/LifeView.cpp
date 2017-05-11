
// LifeView.cpp : реализация класса CLifeView
//

#include "stdafx.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "Life.h"
#endif

#include "LifeDoc.h"
#include "LifeView.h"
#include "MainFrm.h"
#include "Option.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLifeView

IMPLEMENT_DYNCREATE(CLifeView, CView)

BEGIN_MESSAGE_MAP(CLifeView, CView)
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(IDS_NEW_GAME, &CLifeView::OnIdsNewGame)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_COMMAND(IDS_START_LIFE, &CLifeView::OnIdsStartLife)
	ON_COMMAND(IDS_PAUSE_LIFE, &CLifeView::OnIdsPauseLife)
	ON_COMMAND(IDS_RESET_LIFE, &CLifeView::OnIdsResetLife)
	ON_COMMAND(IDS_OPTION, &CLifeView::OnIdsOption)
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// создание/уничтожение CLifeView

CLifeView::CLifeView()
{
	// TODO: добавьте код создания
	Timer_on = 
		Flag_button_left = Flag_button_right =
		Flag_old_mode = false;
}

CLifeView::~CLifeView()
{
}

BOOL CLifeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// рисование CLifeView

void CLifeView::OnDraw(CDC* pDC)
{
	pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CDC memDC;
	CBitmap bit;

	/*int n = 0;
	SetBit(n, 2);
	CString mfg;
	mfg.Format(L"%i", n);
	MessageBox(mfg, L"Hello", NULL);*/

	this->GetClientRect(&Rc);
	if (Rc.Width() <= Rc.Height())
		pDoc->SizeBlock = (Rc.Width() % GAME_FIELD_SIZE == 0) ? Rc.Width() / GAME_FIELD_SIZE : ((Rc.Width() - (Rc.Width() % GAME_FIELD_SIZE)) / GAME_FIELD_SIZE);
	else
		pDoc->SizeBlock = (Rc.Height() % GAME_FIELD_SIZE == 0) ? Rc.Height() / GAME_FIELD_SIZE : ((Rc.Height() - (Rc.Height() % GAME_FIELD_SIZE)) / GAME_FIELD_SIZE);
	//Here
	if (Timer_on){
		if (pDoc->First_step && pDoc->Flag_mode)
			pDoc->New_game(pDoc->Flag_mode);
		else {
			pDoc->Flag_mtrix = !pDoc->Flag_mtrix;
			if (pDoc->Flag_mtrix){
				//pDoc->Clear_field(pDoc->Fild_);
				pDoc->Do_live_move(pDoc->Fild, pDoc->Fild_);
			}
			else {
				//pDoc->Clear_field(pDoc->Fild);
				pDoc->Do_live_move(pDoc->Fild_, pDoc->Fild);
			}
		}
	}
	//(CMainFrame*)(AfxGetMainWnd())->
	CMainFrame* pFrm = (CMainFrame*)theApp.m_pMainWnd;
	pFrm->m_progress.SetPos( pDoc->Cnt_lived);

	CString str;
	str.Format(L"%i", pDoc->Cnt_lived);
	pFrm->SetWindowText(str);

	memDC.CreateCompatibleDC(pDC);
	bit.CreateCompatibleBitmap(pDC, Rc.Width(), Rc.Height());
	memDC.SelectObject(&bit);
	
	for (INT i(0); i < GAME_FIELD_SIZE; i++)
		for (INT j(0); j < GAME_FIELD_SIZE; j++)
			(!pDoc->Flag_mtrix) ? drawSBow(i, j, pDoc->Fild[i][j], memDC) : drawSBow(i, j, pDoc->Fild_[i][j], memDC);
	
	

	/*if (Timer_on){
		pDoc->Flag_mtrix = !pDoc->Flag_mtrix;
		if (pDoc->Flag_mtrix){
			pDoc->Clear_field(pDoc->Fild_);
			pDoc->Do_live_move(pDoc->Fild, pDoc->Fild_);
		}
		else {
			pDoc->Clear_field(pDoc->Fild);
			pDoc->Do_live_move(pDoc->Fild_, pDoc->Fild);
		}
	}*/

	pDC->BitBlt(0, 0, Rc.Width(), Rc.Height(), &memDC, 0, 0, SRCCOPY);//NOTSRCCOPY	
		
	// TODO: добавьте здесь код отрисовки для собственных данных
}
void CLifeView::drawSBow(INT i, INT j, Field Cell){
	CClientDC dc(this);
	CBrush*  brush = (Cell.Is_life) ? new CBrush(COLORREF(pDoc->Clr_block)) : new CBrush(COLORREF(pDoc->Clr_background));
	CBrush*	oldBrush = dc.SelectObject(brush);

	CPen* pen = (Cell.Is_life) ? new CPen(PS_SOLID, 1, COLORREF(pDoc->Clr_block)) : new CPen(PS_SOLID, 1, COLORREF(pDoc->Clr_border));
	CPen* oldPen = dc.SelectObject(pen);
	dc.Rectangle((j * pDoc->SizeBlock), (i * pDoc->SizeBlock), (j * pDoc->SizeBlock) + pDoc->SizeBlock, (i * pDoc->SizeBlock) + pDoc->SizeBlock);

	dc.SelectObject(oldBrush);
	dc.SelectObject(oldPen);

	delete brush;
	delete pen;
}

void CLifeView::drawSBow(INT i, INT j, Field Cell, CDC& memDC){
	CBrush*  brush = (Cell.Is_life) ? new CBrush(COLORREF(pDoc->Clr_block)) : new CBrush(COLORREF(pDoc->Clr_background));
	CBrush*	oldBrush = memDC.SelectObject(brush);

	CPen* pen = (Cell.Is_life) ? new CPen(PS_SOLID, 1, COLORREF(pDoc->Clr_block)) : new CPen(PS_SOLID, 1, COLORREF(pDoc->Clr_border));
	CPen* oldPen = memDC.SelectObject(pen);

	memDC.Rectangle((j * pDoc->SizeBlock), (i * pDoc->SizeBlock), (j * pDoc->SizeBlock) + pDoc->SizeBlock, (i * pDoc->SizeBlock) + pDoc->SizeBlock);

	memDC.SelectObject(oldBrush);
	memDC.SelectObject(oldPen);

	delete brush;
	delete pen;
}
// диагностика CLifeView

#ifdef _DEBUG
void CLifeView::AssertValid() const
{
	CView::AssertValid();
}

void CLifeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLifeDoc* CLifeView::GetDocument() const // встроена неотлаженная версия
{		
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLifeDoc)));
	return (CLifeDoc*)m_pDocument;
}
#endif //_DEBUG


// обработчики сообщений CLifeView


void CLifeView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	
	Invalidate(false);
	CView::OnTimer(nIDEvent);
}

void CLifeView::OnIdsNewGame()
{
	// TODO: добавьте свой код обработчика команд
	if (Timer_on){
		Timer_on = false;
		KillTimer(ID_TIMER);
	}
	pDoc->New_game(false);
	Invalidate(false);
}

void CLifeView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	if (pDoc->Flag_mode){
		if (!Timer_on)
			Check_timer(true);
		else
			Check_timer(false);
	}
	else
		Flag_button_left = true;
	CView::OnLButtonDown(nFlags, point);
}

void CLifeView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	if (!pDoc->Flag_mode)
		Flag_button_left = false;
	CView::OnLButtonUp(nFlags, point);
}

void CLifeView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	if (!pDoc->Flag_mode)
		Flag_button_right = true;
	CView::OnRButtonDown(nFlags, point);
}

void CLifeView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	if (!pDoc->Flag_mode)
		Flag_button_right = false;
	CView::OnRButtonUp(nFlags, point);
}


void CLifeView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	if (!pDoc->Flag_mode && !Timer_on){
		pDoc->currentY = point.x / pDoc->SizeBlock;
		pDoc->currentX = point.y / pDoc->SizeBlock;
		if (Flag_button_left){			
			if (pDoc->Flag_mtrix){
				if (!pDoc->Fild_[pDoc->currentX][pDoc->currentY].Is_life){
					pDoc->Fild_[pDoc->currentX][pDoc->currentY].Is_life = true;
					pDoc->Cnt_lived++;
				}
			}
			else
				if (!pDoc->Fild[pDoc->currentX][pDoc->currentY].Is_life){
					pDoc->Fild[pDoc->currentX][pDoc->currentY].Is_life = true;
					pDoc->Cnt_lived++;
				}
			//Invalidate(false);
		}
		else if (Flag_button_right){			
			if (pDoc->Flag_mtrix){
				if (pDoc->Fild_[pDoc->currentX][pDoc->currentY].Is_life){
					pDoc->Fild_[pDoc->currentX][pDoc->currentY].Is_life = false;
					pDoc->Cnt_lived--;
				}
			}
			else
				if (pDoc->Fild[pDoc->currentX][pDoc->currentY].Is_life){
					pDoc->Fild[pDoc->currentX][pDoc->currentY].Is_life = false;
					pDoc->Cnt_lived--;
				}
			//Invalidate(false);
		}	
		
		/*if (_cnt_ == 100){
			MessageBox(L"100", L"ALert", NULL);
			Invalidate(false);
		}
		else*/
		(!pDoc->Flag_mtrix) ? drawSBow(pDoc->currentX, pDoc->currentY, pDoc->Fild[pDoc->currentX][pDoc->currentY]) :
			drawSBow(pDoc->currentX, pDoc->currentY, pDoc->Fild_[pDoc->currentX][pDoc->currentY]);
	}	
	CView::OnMouseMove(nFlags, point);
}

void CLifeView::Check_timer(BOOL Flag_on_timer){
	if (Flag_on_timer){
		if (!Timer_on)
		{
			Timer_on = true;
			SetTimer(ID_TIMER, 1000 / pDoc->FPS, NULL);
		}
	}
	else{
		if (Timer_on){
			Timer_on = false;
			KillTimer(ID_TIMER);
		}
	}
}

void CLifeView::OnIdsStartLife()
{
	// TODO: добавьте свой код обработчика команд
	Check_timer(true);
}

void CLifeView::OnIdsPauseLife()
{
	// TODO: добавьте свой код обработчика команд
	Check_timer(false);
}

void CLifeView::OnIdsResetLife()
{
	// TODO: добавьте свой код обработчика команд
	Check_timer(false);

	pDoc->New_game(pDoc->Flag_mode);
	Invalidate(false);
}

void CLifeView::OnIdsOption()
{
	// TODO: добавьте свой код обработчика команд
	Option option;
	option.Doc = pDoc;
	option.Set_game(pDoc->Flag_game);
	option.Set_mode(pDoc->Flag_mode);
	Flag_old_mode = pDoc->Flag_mode;

	if (Timer_on)
		KillTimer(ID_TIMER);
	if (option.DoModal() == IDOK){
		if (pDoc->Flag_mode && pDoc->Flag_mode != option.Get_mode())
			pDoc->Clear_field((!pDoc->Flag_mtrix) ? pDoc->Fild : pDoc->Fild_);
		pDoc->FPS = option.fps;
		pDoc->Flag_game = option.Get_game();
		pDoc->Flag_mode = option.Get_mode(); 

		pDoc->Clr_background = option.Selected_index(option.clr_fone);
		pDoc->Clr_border = option.Selected_index(option.clr_border);
		pDoc->Clr_block = option.Selected_index(option.clr_block);			
	}
	if (Timer_on){//если таймер был активен
		if (pDoc->Flag_mode){//продолжаем таймер для обчыного режима
			Timer_on = false;
			if (Flag_old_mode != pDoc->Flag_mode){
				pDoc->New_game(pDoc->Flag_mode);
				Invalidate(false);
			}
			else		
				Check_timer(true);		
		}
		else{//останавливаем таймер для ручного режима
			Timer_on = false;
			if (Flag_old_mode != pDoc->Flag_mode){
				Invalidate(false);
				pDoc->Cnt_lived = 0;
			}
			else 
				Check_timer(true);			
		}
	}
	else{//если таймер был выключен
		if (pDoc->Flag_mode){//отрисовуем изминения для обычного режима
			if (Flag_old_mode != pDoc->Flag_mode){
				pDoc->New_game(pDoc->Flag_mode);
				Invalidate(false);
			}
			else {
				Invalidate(false);
			}			
		}
		else{//отрисовуем изминения для ручного режима
			Invalidate(false);
			pDoc->Cnt_lived = 0;
		}
	}
}
