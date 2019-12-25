#ifndef _MD5_H_ 
#define _MD5_H_ 


char* MD5String( char* string );
char* MD5HEX( char *string, char* digest); 

bool MD5Check( char *md5string, char* string ); 

#endif //_MD5_H_ 