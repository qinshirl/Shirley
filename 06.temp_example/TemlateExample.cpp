// TemlateExample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//模板，又被称为泛型


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
        //constructor
        CMyList()
        {
            m_pHead = m_pTail = NULL;
        }
        
        //add new node to the list
        void push_back( T param)
        {
            Node *pTemp = new Node;
            pTemp->data = param;
            pTemp->pPre = pTemp->pNext = NULL;
            
            if ( m_pHead == NULL)
            {
                m_pHead = pTemp;
                m_pTail = pTemp;
                m_pHead->pNext = m_pHead->pPre = NULL;
            }
            else
            {
                m_pTail->pNext = pTemp;
                m_pTail = pTemp;
            }
        }
        
        void remove(T param){
            Node* temp = m_pHead;
            //if delete head Node
            if(param == m_pHead->data){
                m_pHead = m_pHead->pNext;
                delete temp;
                return;
            }

            //traverse through the linked list to find the node
            while(param != temp->data){
                temp = temp->pNext;
                if(temp == m_pTail && param != m_pTail->data){
                    printf("parameter not found. \n");
                    return;
                }
            }
            //if deleting tail node
            if(temp == m_pTail && param == m_pTail->data){
                m_pTail = temp->pPre;
                delete temp;
                return;
            }

            //other cases: deleting the node in the middle
            temp->pPre->pNext = temp->pNext;
            temp->pNext->pPre = temp->pPre;
            delete temp;        
        }


        MyIterator begin()
        {
            return MyIterator(m_pHead);
        }

        MyIterator end()
        {
            return MyIterator(NULL);
        }
};
//template class example end

int main(int argc, char* argv[])
{

    //test template class
    CMyList<int> myList;
    myList.push_back(100);
    myList.push_back(200);
    myList.push_back(88);
    myList.push_back(55);
    myList.push_back(999);
    myList.remove(100);
    myList.remove(222);

    CMyList<int>::MyIterator iter = myList.begin();
    while ( iter != myList.end() )
    {
        printf("%d\n", *iter );
        iter++;
    }

	return 0;
}