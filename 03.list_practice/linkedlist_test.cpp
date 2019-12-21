// linkedlist_test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


//Node structure
struct Node{
    int num;
    Node* p_pre_node;
    Node* p_next_node;
};


Node* p_head = NULL; //head of the linkedlist
Node* p_tail = NULL; //tail of the linkedlist

//to traverse over the entire linkedlist
void traverse(){
    Node* temp = p_head;
    while(temp != NULL){
        printf("found node: %d\n", temp->num);
        temp = temp->p_next_node;
    }
    //return;
}

//to add new node to the linkedlist
void add_Node(int in_num){
    Node* new_node = new Node; //dynamically allocate space for the new node pointer
    
    new_node ->num = in_num;
    new_node ->p_next_node = NULL;
    
    //if the linkedlist is empty
    if(NULL == p_head){
        p_head = new_node;
        p_tail = new_node;
    }
    //if the linkedlist is not empty, add the new node to the end of the list
    else{
        p_tail ->p_next_node = new_node;
        p_tail = new_node;
    }
    printf("added node %d to the linkedlist.\n", in_num);
}

void delete_Node(int in_num){
    Node* temp = p_head;                
    Node* pre = NULL;
    
    //if the in_num is in the first node
    if(p_head->num == in_num){
        p_head = p_head ->p_next_node;
        delete temp;
        printf("deleted node %d from the linkedlist.\n", in_num);
        return;
    }
    
    
    //traverse to the node that has the number of in_num
    while (temp->num != in_num){
        pre = temp;
        temp = temp->p_next_node;
        
        if(temp == p_tail && temp->num != in_num){
            printf("number %d could not be found in the linkedlist.\n", in_num);
            return;
        }
    }
    
    //if the in_num is the last node
    if(p_tail->num == in_num){
        p_tail = pre;
        delete pre ->p_next_node;
        printf("deleted node %d from the linkedlist.\n", in_num);
        return;
        
    }
    
    //connect the previous node of the deleted node to its next node
    else{
        pre = temp ->p_next_node;
        delete temp;
        printf("deleted node %d from the linkedlist.\n", in_num);
        return;
    }
}


int main(int argc, char* argv[])
{
    add_Node(10);
    add_Node(20);
    add_Node(30);
    traverse();
    delete_Node(10);
    delete_Node(40);
    traverse();
    
    return 0;
    
}

