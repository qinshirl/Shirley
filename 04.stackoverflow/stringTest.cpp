// stringTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <IOSTREAM>
#include <string>

int main(int argc, char* argv[])
{
    int a = 9;
    char szTest[8] = {0};

    scanf( "%s", szTest );
    printf( "%d\n", a );

    /*
    std::string strTest;

    //strTest << std::cin;
    std::cin >> strTest;

	printf( "%d\n", a );
    */
	return 0;
}

