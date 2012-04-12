/*
    Simple wrapper class for checking validity of a URL
*/
#include <windows.h>
#include <io.h>
#include "stdafx.h"
#include "inetter.h"

WinInet::WinInet()
{
    m_hInternet = InternetOpen(NULL, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
}

WinInet::~WinInet()
{

    if ( m_hInternet != NULL )
    {
        InternetCloseHandle(m_hInternet);
        m_hInternet = NULL;
    } 
}

BOOL WinInet::TouchLink(LPCSTR pcszURL)
{
    BOOL    bFound = FALSE;
    DWORD   dwErr;
    char    szURLHostName[INTERNET_MAX_HOST_NAME_LENGTH];
    char    szURLPath[INTERNET_MAX_URL_LENGTH];


    if ( IsConnected() )
    {
        URL_COMPONENTS urlInfo = { sizeof(URL_COMPONENTS) };

        urlInfo.lpszHostName = szURLHostName;
        urlInfo.dwHostNameLength = INTERNET_MAX_HOST_NAME_LENGTH;
        urlInfo.lpszUrlPath = szURLPath;
        urlInfo.dwUrlPathLength = INTERNET_MAX_URL_LENGTH;


        //could be changed to return NOT_A_URL, success or failure
        if ( !InternetCrackUrl(pcszURL, 0, 0, &urlInfo) )
            return FALSE;


        if ( urlInfo.nScheme == INTERNET_SCHEME_HTTP )
        {

			
            HINTERNET hURL = InternetConnect(m_hInternet, szURLHostName, INTERNET_INVALID_PORT_NUMBER,
                               "", "", INTERNET_SERVICE_HTTP, 0, 0);
         if ( hURL )
            {
                LPSTR szarrAcceptTypes[2] = { "*/*", NULL };

                DWORD  dwFlags = INTERNET_FLAG_RELOAD           | 
                                 INTERNET_FLAG_NO_CACHE_WRITE   | 
                                 INTERNET_FLAG_KEEP_CONNECTION;

                HINTERNET hRequest = HttpOpenRequest(hURL, "GET", szURLPath,
                                                     HTTP_VERSION, "", (LPCSTR*)szarrAcceptTypes, dwFlags, 0);

				DWORD dwTimeout = 1000;
				InternetSetOption (hRequest, INTERNET_OPTION_RECEIVE_TIMEOUT, &dwTimeout,sizeof(DWORD));

				InternetSetOption (hRequest, INTERNET_OPTION_SEND_TIMEOUT, &dwTimeout, sizeof(DWORD));

				InternetSetOption (hRequest, INTERNET_OPTION_CONNECT_TIMEOUT, &dwTimeout, sizeof(DWORD));

              if ( hRequest )
                {
					BOOL b = HttpSendRequest(hRequest, NULL, 0, NULL,0);		
				}
			}
            InternetCloseHandle(hURL);
            
        }
 
    }

    return bFound;
}
BOOL WinInet::CheckLink(LPCSTR pcszURL)
{
    BOOL    bFound = FALSE;
    DWORD   dwErr;
    char    szURLHostName[INTERNET_MAX_HOST_NAME_LENGTH];
    char    szURLPath[INTERNET_MAX_URL_LENGTH];


    if ( IsConnected() )
    {
        URL_COMPONENTS urlInfo = { sizeof(URL_COMPONENTS) };

        urlInfo.lpszHostName = szURLHostName;
        urlInfo.dwHostNameLength = INTERNET_MAX_HOST_NAME_LENGTH;
        urlInfo.lpszUrlPath = szURLPath;
        urlInfo.dwUrlPathLength = INTERNET_MAX_URL_LENGTH;


        //could be changed to return NOT_A_URL, success or failure
        if ( !InternetCrackUrl(pcszURL, 0, 0, &urlInfo) )
            return FALSE;


        if ( urlInfo.nScheme == INTERNET_SCHEME_HTTP )
        {

            HINTERNET hURL = InternetConnect(m_hInternet, szURLHostName, INTERNET_INVALID_PORT_NUMBER,
                               "", "", INTERNET_SERVICE_HTTP, 0, 0);

            if ( hURL )
            {
                LPSTR szarrAcceptTypes[2] = { "*/*", NULL };

                DWORD  dwFlags = INTERNET_FLAG_RELOAD           | 
                                 INTERNET_FLAG_NO_CACHE_WRITE   | 
                                 INTERNET_FLAG_KEEP_CONNECTION;

                HINTERNET hRequest = HttpOpenRequest(hURL, "GET", szURLPath,
                                                     HTTP_VERSION, "", (LPCSTR*)szarrAcceptTypes, dwFlags, 0);
				DWORD dwTimeout = 1000;
				InternetSetOption (hRequest, INTERNET_OPTION_RECEIVE_TIMEOUT, &dwTimeout,sizeof(DWORD));

				InternetSetOption (hRequest, INTERNET_OPTION_SEND_TIMEOUT, &dwTimeout, sizeof(DWORD));

				InternetSetOption (hRequest, INTERNET_OPTION_CONNECT_TIMEOUT, &dwTimeout, sizeof(DWORD));

                if ( hRequest )
                {
                    BOOL b = HttpSendRequest(hRequest, NULL, 0, NULL,0);
                    if ( b )
                    {
                        DWORD dwStatus = 0;
                        DWORD dwLength = sizeof(DWORD);

                        if ( HttpQueryInfo(hRequest, HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER, (PVOID)&dwStatus, &dwLength, NULL) )
                            bFound = (dwStatus < HTTP_STATUS_AMBIGUOUS);
                        else
                            dwErr = GetLastError();

                    }

                    InternetCloseHandle(hRequest);
                }

                InternetCloseHandle(hURL);
            }
        }
        else if ( urlInfo.nScheme == INTERNET_SCHEME_FTP )
        {

            HINTERNET hFTP = InternetConnect(m_hInternet, szURLHostName, INTERNET_DEFAULT_FTP_PORT,
                               "", "", INTERNET_SERVICE_FTP, 0, 0);

            if ( hFTP )
            {
                HINTERNET hFile = FtpOpenFile(hFTP, szURLPath, GENERIC_READ, INTERNET_FLAG_RELOAD | FTP_TRANSFER_TYPE_BINARY, 0);

                if ( hFile )
                {
                    bFound = TRUE;
                    InternetCloseHandle(hFile);
                }

                InternetCloseHandle(hFTP);
            }
        }
        else if ( urlInfo.nScheme == INTERNET_SCHEME_FILE )
        {
            // check if the file exists
   //         bFound = (access(szURLPath, 0x00) == 0x00);
        }
        else
        {
            //unrecognized URL scheme
        }

    }

    return bFound;
}


