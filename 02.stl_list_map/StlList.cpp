// StlList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <list>
#include <string>
#include <map>

int main(int argc, char* argv[])
{
    
    //创建一个基于STL模板的int链表
    std::list<int> listInt;

    //向链表里插入若干个元素
    listInt.push_back(100);
    listInt.push_back(77);
    listInt.push_back(88);

    //创建一个STL的链表迭代器，用于遍历链表
    std::list<int>::iterator iter = listInt.begin();

    //遍历链表
    while ( listInt.end() != iter )
    {
        printf( "找到一个元素: %d\n", *iter ); //此处相当于把对象iter当作指针来用, “*号”使用了C++的重载特性

        iter++; //移动到下一个元素，“++号”被重载
    }
    
    listInt.clear();
    

    std::map< std::string, int >  mapTest;

    mapTest[ "lisa" ] = 100;
    mapTest[ "qi" ] = 99;

    if ( mapTest.end() != mapTest.find("qi")  )
    {
        printf("%d\n", mapTest["qi"]);
    }
    
	printf("运行结束!\n");
	return 0;
}