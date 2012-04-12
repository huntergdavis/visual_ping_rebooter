// visual ping rebooterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "visual ping rebooter.h"
#include "visual ping rebooterDlg.h"
#include ".\visual ping rebooterdlg.h"
#include "inetter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CvisualpingrebooterDlg dialog



CvisualpingrebooterDlg::CvisualpingrebooterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CvisualpingrebooterDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CvisualpingrebooterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CvisualpingrebooterDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnBnClickedButton5)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CvisualpingrebooterDlg message handlers

BOOL CvisualpingrebooterDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	SetDlgItemText(IDC_EDIT1,"http://www.google.com");
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CvisualpingrebooterDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CvisualpingrebooterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CvisualpingrebooterDlg::OnBnClickedButton3()
{
	WinInet win;
	SYSTEMTIME sys;
	GetSystemTime(&sys);
	CString OutPut, InPut;
	OutPut.Format("Cable Modem Rebooted: %d-%d-%d ,%d:%d\r\n",sys.wMonth,sys.wDay,sys.wYear,sys.wHour,sys.wMinute);
	GetDlgItemText(IDC_EDIT,InPut);
	CString FinalOut;
	FinalOut.Format("%s%s",InPut,OutPut);
	SetDlgItemText(IDC_EDIT,FinalOut);
	win.TouchLink("http://192.168.100.1/gscan.cgi?freq=331000000");
}

void CvisualpingrebooterDlg::OnBnClickedButton4()
{
	GetDlgItem(IDC_BUTTON4)->EnableWindow(0);
	CString TempNumber;
	GetDlgItemText(IDC_EDIT_NUMBER,TempNumber);
	if(TempNumber == "")
	{
		MessageBox("Please enter a time interval");
	}
	else
	{
		int mytime = atoi(TempNumber)*1000;
		SetTimer(69, mytime, NULL);
	}
}

void CvisualpingrebooterDlg::OnBnClickedButton5()
{
	GetDlgItem(IDC_BUTTON4)->EnableWindow(1);
	KillTimer(69);
}

void CvisualpingrebooterDlg::OnTimer(UINT nIDEvent)
{
	if(nIDEvent == 69)
	{
		CString OurLinkToCheck;
		GetDlgItemText(IDC_EDIT1,OurLinkToCheck);
		WinInet win;
		if(OurLinkToCheck == "")
		{
			MessageBox("Please Enter a web site");
		}
		else
		{
			if(!win.CheckLink(OurLinkToCheck))
			{
				SYSTEMTIME sys;
				GetSystemTime(&sys);
				CString OutPut, InPut;
				OutPut.Format("Cable Modem Rebooted: %d-%d-%d ,%d:%d\r\n",sys.wMonth,sys.wDay,sys.wYear,sys.wHour,sys.wMinute);
				GetDlgItemText(IDC_EDIT,InPut);
				InPut += OutPut;
				SetDlgItemText(IDC_EDIT,InPut);
				win.TouchLink("http://192.168.100.1/gscan.cgi?freq=331000000");
			}
			else
			{
				/*
				SYSTEMTIME sys;
				GetSystemTime(&sys);
				CString OutPut, InPut;
				OutPut.Format("Link Check Fine: %d-%d-%d ,%d:%d\r\n",sys.wMonth,sys.wDay,sys.wYear,sys.wHour,sys.wMinute);
				GetDlgItemText(IDC_EDIT,InPut);
				InPut += OutPut;
				SetDlgItemText(IDC_EDIT,InPut);
				*/
			}

		}
	}
	CDialog::OnTimer(nIDEvent);
}
