#ifndef __INETTER_H__
#define __INETTER_H__

#include <windows.h>
#include <wininet.h>
#include "stdafx.h"

class WinInet
{
    public:
        WinInet();
        ~WinInet();

        BOOL IsConnected() const { return (InternetAttemptConnect(0)==ERROR_SUCCESS); }
        BOOL CheckLink(LPCSTR pcszURL);
		BOOL TouchLink(LPCSTR pcszURL);

    private:
        HINTERNET m_hInternet;
};


#endif