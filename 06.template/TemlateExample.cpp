// TemlateExample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CMyList.hpp"

//模板，又被称为泛型

//template function example start:
template <typename AnyType>

AnyType add( AnyType x, AnyType y)
{
    return x + y;
}

//template function example end


//template class example start:
template <typename T>

class CMyList
{
private:
    struct Node
    {
        Node *pPre;
        Node *pNext;
        T data;
    };
    
    Node *m_pHead;
    Node *m_pTail;
    
public:
        //a new inner class
        class MyIterator{
        private:
            Node *m_pCurrent;
            
        public:
            MyIterator( Node *pNode )
            {
                m_pCurrent = pNode;
            }
           
            void operator ++(int)
            {
                m_pCurrent = m_pCurrent->pNext;
            }

            T & operator *()
            {
                return m_pCurrent->data;
            }

            bool operator != ( MyIterator & iter )
            {
                return iter.m_pCurrent != m_pCurrent;
            }

        };
        //class iterator end

        //belong to CMyList
        CMyList()
        {
            m_pHead = m_pTail = 0;
        }
        
        void push_back( T param)
        {
            Node *pTemp = new Node;
            pTemp->data = param;
            pTemp->pPre = pTemp->pNext = 0;
            
            if ( m_pHead == 0 )
            {
                m_pHead = m_pTail = pTemp;
                m_pHead->pNext = m_pHead->pPre = 0;
            }
            else
            {
                m_pTail->pNext = pTemp;
                m_pTail = pTemp;
            }
        }

        MyIterator begin()
        {
            return MyIterator(m_pHead);
        }

        MyIterator end()
        {
            return MyIterator(0);
        }
};
//template class example end

int main(int argc, char* argv[])
{
    //test template function
	printf("%d\n", add(100, 200) );
    printf("%.2f\n", add(5.13, 4.28) );


    //test template class
    CMyList<int> myList;
    myList.push_back(100);
    myList.push_back(200);
    myList.push_back(88);
    myList.push_back(55);
    myList.push_back(999);

    CMyList<int>::MyIterator iter = myList.begin();
    while ( iter != myList.end() )
    {
        printf("%d\n", *iter );
        iter++;
    }

	return 0;
}

