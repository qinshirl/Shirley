// win32_multithread.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>


//线程函数声明
DWORD WINAPI Thread1Proc(  LPVOID lpParameter);
DWORD WINAPI Thread2Proc(  LPVOID lpParameter);

//全局变量
int tickets = 100;
CRITICAL_SECTION g_cs;

//线程1入口函数
DWORD WINAPI Thread1Proc(  LPVOID lpParameter)
{
    while(TRUE)
    {
        //进入关键代码段前调用该函数等待其他线程离开临界区
        EnterCriticalSection(&g_cs);
        Sleep(1);
        if(tickets > 0)
        {
            Sleep(1);
            printf("thread1 sell ticket : %d\n",tickets--);
            //访问结束后释放临界区对象的使用权
            LeaveCriticalSection(&g_cs);
            Sleep(1);
        }
        else
        {
            LeaveCriticalSection(&g_cs);
            break;
        }
    }
    
    return 0;
}

//线程2入口函数
DWORD WINAPI Thread2Proc(  LPVOID lpParameter)
{
    while(TRUE)
    {
        //进入关键代码段前调用该函数等待其他线程离开临界区
        EnterCriticalSection(&g_cs);
        Sleep(1);
        if(tickets > 0)
        {
            Sleep(1);
            printf("thread2 sell ticket : %d\n",tickets--);
            //访问结束后释放临界区对象的使用权
            LeaveCriticalSection(&g_cs);
            Sleep(1);
        }
        else
        {
            LeaveCriticalSection(&g_cs);
            break;
        }
    }
    
    return 0;
}

int main()
{
    HANDLE hThread1;
    HANDLE hThread2;

    //初始化临界区
    InitializeCriticalSection(&g_cs);

    //创建线程1
    hThread1 = CreateThread(NULL, 0, Thread1Proc, NULL, 0, NULL);
    
    //创建线程2
    hThread2 = CreateThread(NULL, 0, Thread2Proc, NULL, 0, NULL);
    
    
    //主线程休眠5秒，等待其他线程执行结束
    Sleep(5 * 1000);

    //关闭线程句柄
    CloseHandle(hThread1);
    CloseHandle(hThread2);

    //销毁临界区
    DeleteCriticalSection(&g_cs);
    return 0;

    // Tips: 
    // 1. 线程同步也要注意性能问题，不能一味的加锁;
    // 2. 除了临界区之外，还有别的线程同步方案
    // 3. 更多Windows编程知识，请看《VC++深入详解》或《Programming Windows》
    // 4. 不同系统之间的编程知识几乎都是相通的，只是编译器不一样而已
}
