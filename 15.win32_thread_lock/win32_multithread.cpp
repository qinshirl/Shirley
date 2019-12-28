// win32_multithread.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>


//�̺߳�������
DWORD WINAPI Thread1Proc(  LPVOID lpParameter);
DWORD WINAPI Thread2Proc(  LPVOID lpParameter);

//ȫ�ֱ���
int tickets = 100;
CRITICAL_SECTION g_cs;

//�߳�1��ں���
DWORD WINAPI Thread1Proc(  LPVOID lpParameter)
{
    while(TRUE)
    {
        //����ؼ������ǰ���øú����ȴ������߳��뿪�ٽ���
        EnterCriticalSection(&g_cs);
        Sleep(1);
        if(tickets > 0)
        {
            Sleep(1);
            printf("thread1 sell ticket : %d\n",tickets--);
            //���ʽ������ͷ��ٽ��������ʹ��Ȩ
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

//�߳�2��ں���
DWORD WINAPI Thread2Proc(  LPVOID lpParameter)
{
    while(TRUE)
    {
        //����ؼ������ǰ���øú����ȴ������߳��뿪�ٽ���
        EnterCriticalSection(&g_cs);
        Sleep(1);
        if(tickets > 0)
        {
            Sleep(1);
            printf("thread2 sell ticket : %d\n",tickets--);
            //���ʽ������ͷ��ٽ��������ʹ��Ȩ
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

    //��ʼ���ٽ���
    InitializeCriticalSection(&g_cs);

    //�����߳�1
    hThread1 = CreateThread(NULL, 0, Thread1Proc, NULL, 0, NULL);
    
    //�����߳�2
    hThread2 = CreateThread(NULL, 0, Thread2Proc, NULL, 0, NULL);
    
    
    //���߳�����5�룬�ȴ������߳�ִ�н���
    Sleep(5 * 1000);

    //�ر��߳̾��
    CloseHandle(hThread1);
    CloseHandle(hThread2);

    //�����ٽ���
    DeleteCriticalSection(&g_cs);
    return 0;

    // Tips: 
    // 1. �߳�ͬ��ҲҪע���������⣬����һζ�ļ���;
    // 2. �����ٽ���֮�⣬���б���߳�ͬ������
    // 3. ����Windows���֪ʶ���뿴��VC++������⡷��Programming Windows��
    // 4. ��ͬϵͳ֮��ı��֪ʶ����������ͨ�ģ�ֻ�Ǳ�������һ������
}
