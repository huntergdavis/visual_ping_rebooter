// visual ping rebooter.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CvisualpingrebooterApp:
// See visual ping rebooter.cpp for the implementation of this class
//

class CvisualpingrebooterApp : public CWinApp
{
public:
	CvisualpingrebooterApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CvisualpingrebooterApp theApp;