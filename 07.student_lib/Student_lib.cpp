// Student_lib.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <LIST>
#include <STRING.H>
#include <WINDOWS.H>


void read_file();
void print_index();
void add_student();
void choose_in_index();
void remove_student();


struct student{
    int position_in_list;
    bool exist;
    int student_ID;
    char student_name[20];
    int student_mark;
    
};


std::list<student> student_list;


void read_file(){

    FILE* file_add = fopen("student_file", "rb");
    student add;
    
    if(file_add != NULL){

        while(fread(&add, sizeof(student), 1, file_add) != 0){
            if(add.exist != 0){
                student_list.push_back(add);
            }
        }
        fclose(file_add);
    }
    
}



void print_index(){
    system("cls");
    printf("please follow the commands below to adjust the student info list\npress 1 for adding student\npress 2 for deleting student\npress 3 for terminating program\n");
    
}

void add_student(){
    student temp = {0};
    
    printf("please enter the student's student ID number:\n");
    scanf("%d", &temp.student_ID);
    system("cls");

    printf("please enter the student's first name following by last name (*less than 20 characters):\n");
    scanf("%s", &temp.student_name);
    system("cls");

    fflush(stdin);

    printf("please enter the student's final exam mark:\n");
    scanf("%d", &temp.student_mark);
    fflush(stdin);

    temp.exist = 1;
    if(student_list.size() == 0){
        temp.position_in_list = 1;
    }
    else{
        int index = student_list.back().position_in_list;
        temp.position_in_list = index + 1;
    } 

    student_list.push_back(temp);
    
    FILE *file_student = fopen("student_file", "a");
    if(file_student != NULL){
      fwrite(&temp, sizeof(student),1, file_student);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
    }
    fclose(file_student);
    
}

void remove_student(){
    
    int remove_ID;
    
    //prompts user to enter the student they are willing to delete
    printf("please enter the student's student ID number:\n");
    scanf("%d", &remove_ID);
    fflush(stdin);
    
    std::list<student>::iterator find;
    
    //finds the student with his/her student ID
    for(find = student_list.begin(); find != student_list.end(); find++){
        if(find->student_ID == remove_ID && find->exist != 0){
            
            //confirm the deletion
            system("cls");
            printf("you will be deleting the student: ");
            printf("%s\n", find->student_name);
            fflush(stdin);
            
            char proceed;
            printf("do you want to proceed? (y/n)\n");
            scanf("%c", &proceed);
            fflush(stdin);

            //the deleting process
            if(proceed == 'y'){
                int flag = 0;
//                 find->exist = 0;
// 
//                 FILE* file_delete = fopen("student_file", "rb+");
// 
//                 fseek(file_delete, (find->position_in_list - 1)*sizeof(student), SEEK_SET);
//                 //fseek(file_delete, 0, SEEK_SET);
//                 fwrite(&(*find), sizeof(student), 1, file_delete);
//                 find = student_list.erase(find);
//                 fclose(file_delete);
                FILE* file_delete = fopen("student_file", "rb+");
                fseek(file_delete, (find->position_in_list - 1)*sizeof(student) + sizeof(int), SEEK_SET);
                fwrite(&flag, sizeof(int), 1, file_delete);
                find = student_list.erase(find);
                fclose(file_delete);
    
                return;
            }
            else{
               return;
            }
        }
    }

    printf("the student does not exist");
    return;

}
    

void choose_in_index(){
    bool continue_run = 1;
    while (continue_run){
        print_index();
        int command_num = 0;
        scanf("%d", &command_num);
        
        //adding student
        if(command_num == 1){
            system("cls");
            add_student();
            continue_run = 1;
        }
        
        //deleting student
        else if(command_num == 2){
            system("cls");
            remove_student();
            continue_run = 1;
        }
        
        //terminating 
        else if(command_num == 3){
            system("cls");
            printf("thank you for using \n");
            continue_run = 0;
            
            
        }
        
        //invalid command
        else{
            system("cls");
            printf("invalid command");
            continue_run = 1;
        }

    }

}


int main(int argc, char* argv[]){
    read_file();
    print_index();
    choose_in_index();
   
    return 0;
}

