// List.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdlib.h"

struct Node
{
    int data_in_struct;
    Node *pNext;
};

Node *pHead = 0; //ָ������ĵ�һ���ڵ�
Node *pTail = 0; //ָ����������һ���ڵ�


//insert a node
void push( int data )
{
    //����һ���½ڵ�
    Node *pNode = ( Node* )malloc( sizeof(Node) );
    
    //���ڵ��ڵ�Ԫ�ظ�ֵ
    pNode->data_in_struct = data;
    pNode->pNext = 0;
    
    
    if ( 0 == pHead ) 
    {
        //�ոմ����Ľڵ�pNode�ǵ�һ���ڵ�
        pHead = pTail = pNode;
    }

    else
    {
        //�ոմ����Ľڵ㲻�ǵ�һ���ڵ�
        
        //�����һ���ڵ�ġ���һ�ڵ㡱ָ��ָ��ոմ����Ľڵ�
        pTail->pNext = pNode;
        
        //�����һ���ڵ��Ϊ�ոմ����Ľڵ�
        pTail = pNode;
    }
}

//traverse list
void walk()
{
    Node *pNode = pHead;
    
    while ( pNode )
    {
        printf( "�ҵ�һ���ڵ�: %d\n", pNode->data_in_struct );
        
        //�ƶ�����һ���ڵ�
        pNode = pNode->pNext;
    }
    
    printf( "walk ���\n" );
}

int main(int argc, char* argv[])
{
    push(100);
    push(50);
    push(88);
    push(40);
    
    //���������ڵ�����
    walk();
    
    return 0;
}