// Exception.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main(int argc, char* argv[])
{
	int a = 0;

    try
    {
        //如果没有异常保护，此处将导致程序崩溃
        int b = 9 / a;
    }
    catch (...)
    {
        //异常被捕获，程序可以继续往下走        
        printf( "exception catched\n" );
        return -1;

        //但是，虽然程序可以继续运行，但是其实是“带伤运行”
        //最好的办法还是尽力解决Bug

        //参考资料1: https://www.runoob.com/cplusplus/cpp-exceptions-handling.html
        //其他参考资料: Google serach "c exception" or "c++ exception"
    }
    
	return 0;
}