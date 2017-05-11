
// Life.h : главный файл заголовка для приложения Life
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CLifeApp:
// О реализации данного класса см. Life.cpp
//

class CLifeApp : public CWinApp
{
public:
	CLifeApp();


// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CLifeApp theApp;
