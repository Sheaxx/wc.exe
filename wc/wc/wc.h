#pragma once
#ifndef _WC_H  
#define _WC_H 

int charactercount(char* path, char* filename);
int wordcount(char* path, char* filename);
int linecount1(char* path, char* filename);
int linecount2(char* path, char* filename);
int searchfile(char* path, char* op, char* mode);

#endif