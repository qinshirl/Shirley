// List.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdlib.h"

struct Node
{
    int data_in_struct;
    Node *pNext;
};

Node *pHead = 0; //指向链表的第一个节点
Node *pTail = 0; //指向链表的最后一个节点


//insert a node
void push( int data )
{
    //创建一个新节点
    Node *pNode = ( Node* )malloc( sizeof(Node) );
    
    //给节点内的元素赋值
    pNode->data_in_struct = data;
    pNode->pNext = 0;
    
    
    if ( 0 == pHead ) 
    {
        //刚刚创建的节点pNode是第一个节点
        pHead = pTail = pNode;
    }

    else
    {
        //刚刚创建的节点不是第一个节点
        
        //将最后一个节点的“下一节点”指针指向刚刚创建的节点
        pTail->pNext = pNode;
        
        //将最后一个节点改为刚刚创建的节点
        pTail = pNode;
    }
}

//traverse list
void walk()
{
    Node *pNode = pHead;
    
    while ( pNode )
    {
        printf( "找到一个节点: %d\n", pNode->data_in_struct );
        
        //移动到下一个节点
        pNode = pNode->pNext;
    }
    
    printf( "walk 完成\n" );
}

int main(int argc, char* argv[])
{
    push(100);
    push(50);
    push(88);
    push(40);
    
    //遍历链表内的数据
    walk();
    
    return 0;
}