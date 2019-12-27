// win32sdk.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include <stdio.h>


#define TIMER_ID_SHIRLEY 1

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
    //定义窗口的类名称
    TCHAR *szWindowClass = _T("MyWindowClass");
    
    //用WNDCLASSEX结构体定义窗口的各种特性
    WNDCLASSEX wcex;
    
    wcex.cbSize = sizeof(WNDCLASSEX); 
    
    wcex.style			= CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc	= (WNDPROC)WndProc;
    wcex.cbClsExtra		= 0;
    wcex.cbWndExtra		= 0;
    wcex.hInstance		= hInstance;
    wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_WIN32SDK);
    wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName	= (LPCSTR)IDC_WIN32SDK;
    wcex.lpszClassName	= szWindowClass;
    wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);
    
    //注册窗口类
    RegisterClassEx(&wcex);
    
    //创建窗口
    TCHAR *szTitle = _T("我的窗口名字"); 
    HWND hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
    
    if (!hWnd)
    {
        return 0;
    }
    
    //显示窗口
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    //给这个窗口设置一个时长为1秒（1000毫秒）的定时器
    SetTimer(hWnd, TIMER_ID_SHIRLEY, 1 * 1000, NULL);
    
    //进入窗口消息循环:
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) 
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return msg.wParam;
}

//  窗口消息处理函数
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

    SYSTEMTIME st = {0};
    TCHAR szBuffer[120] = {0};

    TCHAR *szText = _T("要绘制的文字");

	switch (message) 
	{
		case WM_COMMAND: //菜单消息
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
            switch (wmId)
            {
            case IDM_EXIT: //菜单里的退出
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
            break;
            case WM_TIMER:
                //处理定时器消息
                if ( TIMER_ID_SHIRLEY == wParam )
                {
                    //获取当前时间
                    GetLocalTime(&st);

                    //格式化为字符串
                    _stprintf(szBuffer, "%02d/%02d/%02d %02d:%02d:%02d", st.wYear, st.wMonth, st.wDay,
                        st.wHour, st.wMinute, st.wSecond);
                    
                    //将当前窗口的标题设置为上述字符串
                    SetWindowText( hWnd, szBuffer );
                }
                break;
            case WM_PAINT: //窗口绘制消息
                hdc = BeginPaint(hWnd, &ps);
                // TODO: Add any drawing code here...
                RECT rt;
                GetClientRect(hWnd, &rt);
                DrawText(hdc, szText, strlen(szText), &rt, DT_CENTER);
                EndPaint(hWnd, &ps);
                break;
            case WM_DESTROY: //窗口销毁消息
                KillTimer(hWnd, TIMER_ID_SHIRLEY);
                PostQuitMessage(0);
                break;
            default: //默认的消息处理函数
                return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}