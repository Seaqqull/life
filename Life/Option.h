#pragma once

#include "resource.h"
#include "LifeDoc.h"
// диалоговое окно Option

class Option : public CDialogEx
{
	DECLARE_DYNAMIC(Option)

public:
	CLifeDoc* Doc;
	INT fps, 
		clr_fone, clr_block, clr_border;
	CRect Fone, Block, Border;
	BOOL FLag_mode, Flag_game,
		FLag_mode_, Flag_game_;
	CString Temp_str;
	Option(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~Option();

	ConsoleColor Selected_index(INT index);
	INT Selected_color(ConsoleColor clr);
	BOOL Get_mode(){ return FLag_mode; }
	BOOL Get_game(){ return Flag_game; }
	void Set_mode(BOOL flag);
	void Set_game(BOOL flag);
// Данные диалогового окна
	enum { IDD = IDD_DIALOG1 };

protected:
	CSliderCtrl Sl_controll;
	CComboBox Bx_controll1, Bx_controll2, Bx_controll3;
	CStatic ST_controll0, ST_controll1, ST_controll2, ST_controll3;

	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnPaint();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnCbnSelchangeCombo3();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
};
