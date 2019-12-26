// win32sdk.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"

#define SHAPE_NONE 0
#define SHAPE_LINE 1
#define SHAPE_RECT 2
#define SHAPE_CIRCLE 3

UINT g_CurrentShape = SHAPE_NONE;
POINT g_StartPoint = {0};
POINT g_EndPoint = {0};
BOOL g_MousePressed = FALSE;

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
    RECT rc;

    TCHAR *szText = _T("要绘制的文字");

	switch (message) 
    {
    case WM_COMMAND: //菜单消息
        wmId    = LOWORD(wParam); 
        wmEvent = HIWORD(wParam); 
        // Parse the menu selections:
        switch (wmId)
        {
        case MENU_LINE:
            g_CurrentShape = SHAPE_LINE;
            break;
        case MENU_RECT:
            g_CurrentShape = SHAPE_RECT;
            break;
        case MENU_CIRCLE:
            g_CurrentShape = SHAPE_CIRCLE;
            break;
        case IDM_EXIT: //菜单里的退出
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        break;

        case WM_LBUTTONDOWN: //鼠标左键的按下消息
            if ( SHAPE_NONE == g_CurrentShape )
            {
                MessageBox( hWnd, _T("请先从菜单选择图形"), _T("发啥神经"), MB_OK );
            }
            else
            {
                g_MousePressed = TRUE;

                //获取鼠标在整个屏幕的坐标（屏幕左上顶点为0,0）
                GetCursorPos(&g_StartPoint);
                
                //转换为鼠标在当前窗口Client区域的坐标
                ScreenToClient(hWnd, &g_StartPoint);
            }
            break;
            
        case WM_MOUSEMOVE: //鼠标左键的松开消息
            if ( g_MousePressed )
            {
                //获取鼠标在整个屏幕的坐标（屏幕左上顶点为0,0）
                GetCursorPos(&g_EndPoint);
                
                //转换为鼠标在当前窗口Client区域的坐标
                ScreenToClient(hWnd, &g_EndPoint);
                
                //使整个客户区域RECT失效，强迫系统发送WM_PAINT消息
                GetClientRect(hWnd, &rc);
                InvalidateRect( hWnd, &rc, TRUE );
            }
            break;
        case WM_LBUTTONUP:
            g_MousePressed = FALSE;
            break;
        case WM_PAINT: //窗口绘制消息，客户
            hdc = BeginPaint(hWnd, &ps);
            
            //根据选择来绘图
            
            if ( SHAPE_LINE == g_CurrentShape )
            {
                //首先移动到起点
                MoveToEx(hdc, g_StartPoint.x, g_StartPoint.y, NULL);
                //连线到终点
                LineTo(hdc, g_EndPoint.x, g_EndPoint.y);
            }
            else if ( SHAPE_RECT == g_CurrentShape )
            {
                //创建并使用蓝色的画笔
                HPEN hPen =CreatePen( PS_DOT, 1, RGB(0,0,255) );
                SelectObject(hdc, hPen);

                //绘制矩形
                Rectangle( hdc, g_StartPoint.x, g_StartPoint.y, g_EndPoint.x, g_EndPoint.y );

                DeleteObject(hPen);
            }
            else if ( SHAPE_CIRCLE == g_CurrentShape )
            {
                //绘制椭圆
                Ellipse( hdc, g_StartPoint.x, g_StartPoint.y, g_EndPoint.x, g_EndPoint.y );
            }

            //TODO: 记录所有画过的图形，下次WM_PAINT时不消失（思考：当图形很多时，会出现什么现象，怎么解决）
            
            EndPaint(hWnd, &ps);
            break;
        case WM_DESTROY: //窗口销毁消息
            PostQuitMessage(0);
            break;
        default: //默认的消息处理函数
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
   return 0;
}