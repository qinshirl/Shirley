// student_lib_sql.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <WINSOCK2.H>
#include <mysql.h>
#include <STDLIB.H>

#ifdef _WIN32
#pragma comment(lib, "libmysql.lib")
#endif

int main(int argc, char* argv[])
{
    //initialize
    MYSQL first;
    mysql_init(&first);

    //connect 
    //conn -> the file we are using rn
    MYSQL * conn = mysql_real_connect(&first, "127.0.0.1", "root", "root", "shirley", 3306, NULL, 0);

    //query from the file 
    if ( mysql_query(conn, "delete from `websites` where `alexa` = '1' ;") != 0 ) //check if the command is correct
    {
        printf("error: %s\n", mysql_error(conn) ); //'mysql_error' command gives the details of the error
        return 0;
    }

    if ( mysql_query(conn, "insert into `websites` (name, url, alexa, country) values('amazon', 'amazon.ca', '5', 'USA')") != 0 ) //check if the command is correct
    {
        printf("error: %s\n", mysql_error(conn) ); //'mysql_error' command gives the details of the error
        return 0;
    }

    
    if ( mysql_query(conn, "select * from `websites`;") != 0 )
    {
        printf("error: %s\n", mysql_error(conn) );
        return 0;
    }
    
    //result collected from the select command
    MYSQL_RES * result = mysql_store_result(conn);
    
    //create MYSQL_ROW variable - 'lines'
    MYSQL_ROW lines;
    //check if the 'mysql_fetch_row' command is successful 
    while ( (lines = mysql_fetch_row( result )) != 0 )//fetch each row using the 'mysql_fetch_row' into 'lines' 
    {
        //printf("record\n");

        //ascii to integer "atoi"
//         int id = atoi(row[0]);
// 
//         printf( "%d\n", id );
//         
        printf( "%s -- %s -- %s -- %s -- %s\n", lines[0], lines[1], lines[2], lines[3], lines[4] );
    }
    
    //free the result collected from the select command
    mysql_free_result( result );

    //similar to close file
    mysql_close(conn);




	printf("Hello World!\n");
	return 0;
}

