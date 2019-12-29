// win32_multithread.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>

DWORD ThreadFunctionA( LPVOID param )
{
    for(int i = 0; i < 10; i++)
    {
        printf( "Running in thread A ...\n" );
        Sleep(500);
    }
    return 0;
}

DWORD ThreadFunctionB( LPVOID param )
{
    for(int i = 0; i < 10; i++)
    {
        printf( "Running in thread B ...\n" );
        Sleep(500);
    }
    return 0;
}

int main(int argc, char* argv[])
{
    
    CreateThread( NULL, NULL, (LPTHREAD_START_ROUTINE)ThreadFunctionA, NULL, NULL, NULL );
    
    CreateThread( NULL, NULL, (LPTHREAD_START_ROUTINE)ThreadFunctionB, NULL, NULL, NULL );
    
    while ( 1 )
    {
        printf( "Running in main thread...\n" );
        Sleep(500);
    }

	return 0;
}

