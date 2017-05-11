// Option.cpp: файл реализации
//

#include "stdafx.h"
#include "Life.h"
#include "Option.h"
#include "afxdialogex.h"


// диалоговое окно Option

IMPLEMENT_DYNAMIC(Option, CDialogEx)

Option::Option(CWnd* pParent /*=NULL*/)
	: CDialogEx(Option::IDD, pParent)
{
	Flag_game = FLag_mode = false;//true
	Flag_game_ = FLag_mode_ = false;
}

Option::~Option()
{
}

void Option::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_SLIDER1, Sl_controll);
	DDX_Control(pDX, IDC_COMBO1, Bx_controll1);
	DDX_Control(pDX, IDC_COMBO2, Bx_controll2);
	DDX_Control(pDX, IDC_COMBO3, Bx_controll3);
	DDX_Control(pDX, IDC_STATIC0, ST_controll0);
	DDX_Control(pDX, IDC_STATIC1, ST_controll1);
	DDX_Control(pDX, IDC_STATIC2, ST_controll2);
	DDX_Control(pDX, IDC_STATIC3, ST_controll3);
	
	DDX_Check(pDX, IDC_RADIO1, Flag_game);
	DDX_Check(pDX, IDC_RADIO2, Flag_game_);
	DDX_Check(pDX, IDC_RADIO3, FLag_mode);	
	DDX_Check(pDX, IDC_RADIO4, FLag_mode_);

	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Option, CDialogEx)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDOK, &Option::OnBnClickedOk)
	ON_WM_PAINT()
	ON_CBN_SELCHANGE(IDC_COMBO1, &Option::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &Option::OnCbnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO3, &Option::OnCbnSelchangeCombo3)
	ON_BN_CLICKED(IDC_RADIO1, &Option::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &Option::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &Option::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &Option::OnBnClickedRadio4)
END_MESSAGE_MAP()


// обработчики сообщений Option

ConsoleColor Option::Selected_index(INT index){
	switch (index){
	case 0:
		return Black;
	case 1:
		return Gray;
	case 2:
		return White;
	case 3:
		return Lavender;
	case 4:
		return LightBlue;
	case 5:
		return Lime;
	default:
		return Black;
	}
}
INT Option::Selected_color(ConsoleColor clr){
	switch (clr){
	case Black:
		return 0;
	case Gray:
		return 1;
	case White:
		return 2;
	case Lavender:
		return 3;
	case LightBlue:
		return 4;
	case Lime:
		return 5;
	default:
		return 0;
	}
}

void Option::Set_game(BOOL flag){
	if (flag)
		Flag_game = true;
	else
		Flag_game_ = true;	
}
void Option::Set_mode(BOOL flag){
	if (flag)
		FLag_mode = true;
	else
		FLag_mode_ = true;
}


BOOL Option::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Добавить дополнительную инициализацию
	fps = Doc->FPS;

	clr_fone = Selected_color(Doc->Clr_background);
	clr_border = Selected_color(Doc->Clr_border);
	clr_block = Selected_color(Doc->Clr_block);

	Temp_str.Format(L"%i", fps);
	ST_controll0.SetWindowTextW(Temp_str);

	Bx_controll1.AddString(L"Black");
	Bx_controll1.AddString(L"Gray");
	Bx_controll1.AddString(L"White");
	Bx_controll1.AddString(L"Lavender");
	Bx_controll1.AddString(L"LightBlue");
	Bx_controll1.AddString(L"Lime");
	Bx_controll1.SetCurSel(clr_fone);

	Bx_controll2.AddString(L"Black");
	Bx_controll2.AddString(L"Gray");
	Bx_controll2.AddString(L"White");
	Bx_controll2.AddString(L"Lavender");
	Bx_controll2.AddString(L"LightBlue");
	Bx_controll2.AddString(L"Lime");
	Bx_controll2.SetCurSel(clr_border);

	Bx_controll3.AddString(L"Black");
	Bx_controll3.AddString(L"Gray");
	Bx_controll3.AddString(L"White");
	Bx_controll3.AddString(L"Lavender");
	Bx_controll3.AddString(L"LightBlue");
	Bx_controll3.AddString(L"Lime");
	Bx_controll3.SetCurSel(clr_block);

	Sl_controll.SetRange(MIN_FPS, MAX_FPS, TRUE);
	Sl_controll.SetPos(fps);

	GetDlgItem(IDC_STATIC1)->GetWindowRect(&Fone);
	ScreenToClient(&Fone);

	GetDlgItem(IDC_STATIC2)->GetWindowRect(&Border);
	ScreenToClient(&Border);

	GetDlgItem(IDC_STATIC3)->GetWindowRect(&Block);
	ScreenToClient(&Block);

	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}

void Option::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	fps = Sl_controll.GetPos();
	Temp_str.Format(L"%i", fps);
	ST_controll0.SetWindowTextW(Temp_str);
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

void Option::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: добавьте свой код обработчика сообщений
	CBrush *br1;

	clr_fone = Bx_controll1.GetCurSel();
	clr_border = Bx_controll2.GetCurSel();
	clr_block = Bx_controll3.GetCurSel();

	CBrush br(COLORREF(Selected_index(clr_fone)));

	br1 = dc.SelectObject(&br);
	dc.Rectangle(&Fone);
	br.DeleteObject();

	br.CreateSolidBrush(COLORREF(Selected_index(clr_border)));
	dc.SelectObject(&br);
	dc.Rectangle(&Border);
	br.DeleteObject();

	br.CreateSolidBrush(COLORREF(Selected_index(clr_block)));
	dc.SelectObject(&br);
	dc.Rectangle(&Block);		
	br.DeleteObject();
	
	dc.SelectObject(br1);//end
	
	// Не вызывать CDialogEx::OnPaint() для сообщений рисования
}

void Option::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	CDialogEx::OnOK();
}

void Option::OnCbnSelchangeCombo1()
{
	// TODO: добавьте свой код обработчика уведомлений
	InvalidateRect(&Fone, false);
	InvalidateRect(&Block, false);
	InvalidateRect(&Border, false);
}

void Option::OnCbnSelchangeCombo2()
{
	// TODO: добавьте свой код обработчика уведомлений
	InvalidateRect(&Fone, false);
	InvalidateRect(&Block, false);
	InvalidateRect(&Border, false);
}

void Option::OnCbnSelchangeCombo3()
{
	// TODO: добавьте свой код обработчика уведомлений
	InvalidateRect(&Fone, false);
	InvalidateRect(&Block, false);
	InvalidateRect(&Border, false);
}


void Option::OnBnClickedRadio1()
{
	// TODO: добавьте свой код обработчика уведомлений
	if (!Flag_game){
		Flag_game_ = false;
		Flag_game = true;
	}		
	UpdateData(0);
}

void Option::OnBnClickedRadio2()
{
	// TODO: добавьте свой код обработчика уведомлений
	if (!Flag_game_){
		Flag_game = false;
		Flag_game_ = true;
	}
	UpdateData(0);
}

void Option::OnBnClickedRadio3()
{
	// TODO: добавьте свой код обработчика уведомлений
	if (!FLag_mode){
		FLag_mode_ = false;
		FLag_mode = true;
	}
	UpdateData(0);
}

void Option::OnBnClickedRadio4()
{
	// TODO: добавьте свой код обработчика уведомлений
	if (!FLag_mode_){
		FLag_mode = false;
		FLag_mode_ = true;
	}
	UpdateData(0);
}
