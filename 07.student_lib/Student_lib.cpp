// Student_lib.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <LIST>
#include <STRING.H>
#include <WINDOWS.H>




struct student{
    int student_ID;
    char student_name[20];
    int student_mark;
};


std::list<student> student_list;


void print_index(){
    system("cls");
    printf("please follow the commands below to adjust the student info list\npress 1 for adding student\npress 2 for deleting student\npress 3 for returning main menu\npress 4 for terminating program\n");
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

    student_list.push_back(temp);

    FILE *file_student = fopen("student_file", "ab");
    if(file_student != NULL){
      fwrite(&temp, sizeof(student),1, file_student);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
    }
}
void remove_student(){

} 



int choose_in_index(){
    int command_num = 0;

    scanf("%d", &command_num);
    
    //adding student
    if(command_num == 1){
        system("cls");
        add_student();
    }

    //deleting student
    else if(command_num == 2){
    }

    //returning to main index
    else if(command_num == 3){
        print_index();
        choose_in_index();
        
    }

    //terminating 
    else if(command_num == 4){
        system("cls");
        printf("thank you for using \n");
        return 0;

    }

    //invalid command
    else{
        system("cls");
        printf("invalid command");
        }
}





int main(int argc, char* argv[])
{
    int command_num = 0;
    print_index();
    choose_in_index();

    if(choose_in_index == 0)	return 0;
}

