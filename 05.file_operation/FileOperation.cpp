// FileOperation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string.h>
#include <windows.H>

struct Student
{
    int id;
    char szName[20];
};

int main(int argc, char* argv[])
{
    Student stu[2] = {0};
    
    stu[0].id = 1000;
    strcpy( stu[0].szName, "Shirley" );

    stu[1].id = 1001;
    strcpy( stu[1].szName, "Lisa" );

	//open a file(write, binary)
    FILE *file = fopen("test.bin", "wb");

    if ( NULL != file )
    {
        //file is opened, write data
        fwrite(stu, sizeof(Student), sizeof(stu) / sizeof(Student), file  );

        //close file.
        fclose(file);
    }

    Student stu_read[2] = {0};

    //open a file(read only)
    FILE *file_r = fopen("test.bin", "r");
    
    if ( NULL != file_r )
    {
        //file is opened, write data
        fread(stu_read, sizeof(Student), sizeof(stu) / sizeof(Student), file_r  );

        //close file.
        fclose(file_r);

        //print data that read from file 
        printf( "%d -- %s\n", stu_read[0].id, stu_read[0].szName );
        printf( "%d -- %s\n", stu_read[1].id, stu_read[1].szName );
    }

	return 0;
}

