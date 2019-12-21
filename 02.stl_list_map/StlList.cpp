// StlList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <list>
#include <string>
#include <map>

int main(int argc, char* argv[])
{
    
    //����һ������STLģ���int����
    std::list<int> listInt;

    //��������������ɸ�Ԫ��
    listInt.push_back(100);
    listInt.push_back(77);
    listInt.push_back(88);

    //����һ��STL����������������ڱ�������
    std::list<int>::iterator iter = listInt.begin();

    //��������
    while ( listInt.end() != iter )
    {
        printf( "�ҵ�һ��Ԫ��: %d\n", *iter ); //�˴��൱�ڰѶ���iter����ָ������, ��*�š�ʹ����C++����������

        iter++; //�ƶ�����һ��Ԫ�أ���++�š�������
    }
    
    listInt.clear();
    

    std::map< std::string, int >  mapTest;

    mapTest[ "lisa" ] = 100;
    mapTest[ "qi" ] = 99;

    if ( mapTest.end() != mapTest.find("qi")  )
    {
        printf("%d\n", mapTest["qi"]);
    }
    
	printf("���н���!\n");
	return 0;
}