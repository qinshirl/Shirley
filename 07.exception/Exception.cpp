// Exception.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main(int argc, char* argv[])
{
	int a = 0;

    try
    {
        //���û���쳣�������˴������³������
        int b = 9 / a;
    }
    catch (...)
    {
        //�쳣�����񣬳�����Լ���������        
        printf( "exception catched\n" );
        return -1;

        //���ǣ���Ȼ������Լ������У�������ʵ�ǡ��������С�
        //��õİ취���Ǿ������Bug

        //�ο�����1: https://www.runoob.com/cplusplus/cpp-exceptions-handling.html
        //�����ο�����: Google serach "c exception" or "c++ exception"
    }
    
	return 0;
}