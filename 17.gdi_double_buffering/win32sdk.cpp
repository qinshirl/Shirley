// win32sdk.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include <STDLIB.H>
#include <LIST>
#include <STRING>
#include <STDIO.H>

#define SHAPE_NONE 0
#define SHAPE_LINE 1
#define SHAPE_RECT 2
#define SHAPE_CIRCLE 3

struct DRAWN_SHAPES
{
    POINT g_point_saved_start;
    POINT g_point_saved_end;
    int shape;

};

std::list<DRAWN_SHAPES> g_saved_shapes;


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
    //���崰�ڵ�������
    TCHAR *szWindowClass = _T("MyWindowClass");
    
    //��WNDCLASSEX�ṹ�嶨�崰�ڵĸ�������
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
    
    //ע�ᴰ����
    RegisterClassEx(&wcex);
    
    //��������
    TCHAR *szTitle = _T("my drawing window"); 
    HWND hWnd = CreateWindow(
        szWindowClass, 
        szTitle, 
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 
        0, 
        CW_USEDEFAULT, 
        0, 
        NULL, 
        NULL, 
        hInstance, 
        NULL);
    
    if (!hWnd)
    {
        return 0;
    }
    
    //��ʾ����
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    
    //���봰����Ϣѭ��:
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) 
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return msg.wParam;
}

void DrawShapes( HWND hWnd )
{
    //since the function will be called for every update in the window, the iterator needs to be reset to the start of the linkedlist everytime
    std::list<DRAWN_SHAPES>::iterator g_iter_shapes= g_saved_shapes.begin();
    
    HDC hdc = GetDC(hWnd);

    // ׼��˫����
    // ����һ����ָ���豸(��������Ļ)���ݵ��ڴ��豸�����Ļ�����DC��         
    HDC hMemoryDC = CreateCompatibleDC(hdc); 
    
    // ����һ������Ļ��ʾ���ݵ�λͼ��λͼ�Ĵ�С��ѡ�ô��ڿͻ����Ĵ�С
    RECT rc;
    GetClientRect( hWnd, &rc );
    HBITMAP hMemoryMap = CreateCompatibleBitmap(hdc, rc.right - rc.left, rc.bottom - rc.top );

    // ��λͼ����ѡ�뵽�ڴ���ʾ�豸�������У�ֻ��ѡ���˲��ܽ��л�ͼ      
    HBITMAP hOldBitMap = (HBITMAP)SelectObject(hMemoryDC, hMemoryMap);

    //������ı���Ĭ���Ǻ�ɫ��Ҫ��Ϳ��
    HBRUSH bBrush = CreateSolidBrush(RGB(255,255,255));

    //the returned hOldBrush contains the previous brush selected
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hMemoryDC, bBrush);
    Rectangle(hMemoryDC, 0, 0, rc.right - rc.left, rc.bottom - rc.top);
    SelectObject(hMemoryDC, hOldBrush);
    DeleteObject(hOldBrush);

    //����׼����ϣ��򻺳�HDC��ͼ
    while( g_iter_shapes != g_saved_shapes.end() ){
        
        //draw line
        if(g_iter_shapes->shape == SHAPE_LINE){
            
            MoveToEx(hMemoryDC, (g_iter_shapes->g_point_saved_start).x, (g_iter_shapes->g_point_saved_start).y, NULL);
            LineTo(hMemoryDC, (g_iter_shapes->g_point_saved_end).x, (g_iter_shapes->g_point_saved_end).y);
            
        }
        //draw rectangle
        else if ( g_iter_shapes->shape == SHAPE_RECT ){
            
            HPEN hPen =CreatePen( PS_DASHDOTDOT, 2, RGB(255,0,255) );
            //since the selectObject function returns the hPen value of the default(used) pen
            HPEN hOldPen = (HPEN)SelectObject(hMemoryDC, hPen);
            
            Rectangle( hMemoryDC, (g_iter_shapes->g_point_saved_start).x, (g_iter_shapes->g_point_saved_start).y,
                (g_iter_shapes->g_point_saved_end).x, (g_iter_shapes->g_point_saved_end).y);
            
            DeleteObject(hPen);
            
            //select the stored oldpen value back
            //SelectObject(hMemoryDC, hOldPen);
        }
        
        //draw eclipse
        else if ( SHAPE_CIRCLE == g_CurrentShape ){
            HPEN hPen =CreatePen( PS_DASHDOTDOT, 2, RGB(0,255,255) );
            //since the selectObject function returns the hPen value of the default(used) pen
           (HPEN)SelectObject(hMemoryDC, hPen);
            
            Ellipse( hMemoryDC, (g_iter_shapes->g_point_saved_start).x, (g_iter_shapes->g_point_saved_start).y,
                (g_iter_shapes->g_point_saved_end).x, (g_iter_shapes->g_point_saved_end).y);
            
            DeleteObject(hPen);
            
        }
        
        g_iter_shapes++;
    }
    
    if ( SHAPE_LINE == g_CurrentShape )
    {
        //�����ƶ������
        MoveToEx(hMemoryDC, g_StartPoint.x, g_StartPoint.y, NULL);
        //���ߵ��յ�
        LineTo(hMemoryDC, g_EndPoint.x, g_EndPoint.y);
    }
    else if ( SHAPE_RECT == g_CurrentShape )
    {
        //������ʹ����ɫ�Ļ���
        HPEN hPen =CreatePen( PS_DASHDOTDOT, 2, RGB(255,0,255) );
        SelectObject(hMemoryDC, hPen);
        
        //���ƾ���
        Rectangle( hMemoryDC, g_StartPoint.x, g_StartPoint.y, g_EndPoint.x, g_EndPoint.y );
        
        DeleteObject(hPen);
    }
    else if ( SHAPE_CIRCLE == g_CurrentShape )
    {
        //������Բ
        Ellipse( hMemoryDC, g_StartPoint.x, g_StartPoint.y, g_EndPoint.x, g_EndPoint.y );
    }

    //�ӻ����DC������ʵ��DC
    BOOL bRet = BitBlt(hdc, 0, 0, rc.right - rc.left, rc.bottom - rc.top, hMemoryDC, 0, 0, SRCCOPY);

    
    //ɾ������DC�������Դ
    SelectObject(hMemoryDC, hOldBitMap);
    ReleaseDC( hWnd, hMemoryDC );
    DeleteObject( hMemoryMap );
    ReleaseDC( hWnd, hdc );
}

//  ������Ϣ������
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
    RECT rc;

    TCHAR *szText = _T("draw smth :)");
    
    DRAWN_SHAPES temp = {0};

	switch (message) 
    {
    case WM_COMMAND: //�˵���Ϣ
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

        case IDM_EXIT: //�˵�����˳�
            DestroyWindow(hWnd);
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        break;


////////////////////////////////////////////
        case WM_LBUTTONDOWN: //�������İ�����Ϣ
            if ( SHAPE_NONE == g_CurrentShape )
            {
                //MessageBox( hWnd, _T("choose shape from index"), _T("��ɶ��"), MB_OK );
                AfxMessageBox("shirley");

                CWnd* test = CWnd::FromHandle(hWnd);
                test->CenterWindow();
                test->Detach();
            }
            else
            {
                g_MousePressed = TRUE;

                //��ȡ�����������Ļ�����꣨��Ļ���϶���Ϊ0,0��
                GetCursorPos(&g_StartPoint);
                
                //ת��Ϊ����ڵ�ǰ����Client���������
                ScreenToClient(hWnd, &g_StartPoint);
            }
            break;
            


///////////////////////////////////////////
        case WM_MOUSEMOVE: //���������ɿ���Ϣ
            if ( g_MousePressed )
            {
                //��ȡ�����������Ļ�����꣨��Ļ���϶���Ϊ0,0��
                GetCursorPos(&g_EndPoint);
                
                //ת��Ϊ����ڵ�ǰ����Client���������
                ScreenToClient(hWnd, &g_EndPoint);
                
                //ʹ�����ͻ�����RECTʧЧ��ǿ��ϵͳ����WM_PAINT��Ϣ
                GetClientRect(hWnd, &rc);
                InvalidateRect( hWnd, &rc, FALSE);
            }
            break;
            

///////////////////////////////////////////
        case WM_LBUTTONUP:
            g_MousePressed = FALSE;
            temp.shape = g_CurrentShape;
            temp.g_point_saved_start = g_StartPoint;
            temp.g_point_saved_end = g_EndPoint;
            g_saved_shapes.push_back(temp);
       
            break;
  
            
///////////////////////////////////////////

        case WM_PAINT: //���ڻ�����Ϣ���ͻ�
            DrawShapes(hWnd);
            break;

        case WM_DESTROY: //����������Ϣ
            PostQuitMessage(0);
            break;

        default: //Ĭ�ϵ���Ϣ������
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
   return DefWindowProc(hWnd, message, wParam, lParam);
}