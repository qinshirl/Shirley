// win32_multithread.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>

int g_ticket = 0;

DWORD ThreadFunction( LPVOID param )
{
    while ( 1 )
    {
        g_ticket--;
        printf( "Running in thread: %d\n", g_ticket );
    }
}

int main(int argc, char* argv[])
{
    
    CreateThread( NULL, NULL, (LPTHREAD_START_ROUTINE)ThreadFunction, NULL, NULL, NULL );
    
    while ( 1 )
    {
        g_ticket++;
        printf( "Running in thread: %d\n", g_ticket );
    }

    //TODO: �㿴����ʲô������������ô����أ�

	return 0;
}