#pragma once
#ifndef _WC_H  
#define _WC_H 

int charactercount(char* filename);
int wordcount(char* filename);
int linecount1(char* filename);
int linecount2(char* filename);
int searchfile(char* path, char* mode, char* str,int select);

#endif