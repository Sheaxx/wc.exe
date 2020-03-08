#include <stdio.h>
#include<string.h>
#include"wc.h"


int word(char *filename) {//统计词数
	FILE* fp;
	errno_t err;
	int w = 0;
	char ch;
	bool flag = true;
	err = fopen_s(&fp, filename, "r");
	if (NULL == fp)return 0;
	else {
		while (feof(fp) == 0) {
			ch = fgetc(fp);
			if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {//当该字符为字母时
				if (flag == true) {
					w++;
					flag = false;
				}
			}
			else flag = true;
		}
	}
	fclose(fp);
	return w;
}

int line1(char *filename) {//统计行数
	FILE* fp;
	errno_t err;
	int l = 0;
	char str[100] = { 0 };
	err = fopen_s(&fp, filename, "r");
	if (NULL == fp)return 0;
	else {
		while (feof(fp) == 0) {
			fgets(str, sizeof(str) - 1, fp);
			l++;
		}
	}
	fclose(fp);
	return l;
}

int line2(char* filename) {//统计空行、代码行和注释行
	FILE* fp;
	errno_t err;
	int k = 0, d = 0, z = 0, i = 0, j = 0;
	char str[100] = { 0 };
	bool flag, tag = true;
	err = fopen_s(&fp, filename, "r");
	if (NULL == fp)return 0;
	else {
		while (feof(fp) == 0) {
			fgets(str, sizeof(str) - 1, fp);
			for (; i <= sizeof(str);  i++) {
				flag = true;
				if (((str[i] == '{' || str[i] == '}') && (str[i + 1] == '\0' || str[i + 1] == '\n'))||str[i]=='\n'||str[i]=='\0') {
					k++;//空行
					break;
				}
				else if ((str[i] == '/' && str[i + 1] == '/')||(str[i]=='}'&&str[i+1]=='/')) {
					z++;//用“//”符号的注释行
					break;
				}
				else if (str[i] == '/' && str[i + 1] == '*') {
					z++;//用“/*”符号的多行注释
					j = i + 2;
					while (str[j] != '\n' && str[j] != '*' && str[j + 1] != '/')
						j++;
					if(str[j]=='\n')tag = false;//标记
					break;
				}
				else if (str[i] != ' ' && str[i] != '\t' && str[i]!='\n') {
					if (tag == true)d++;//代码行
					else {//注释行
						z++;
						j=i++;
						while (str[j] != '\n' && str[j] != '*' && str[j + 1] != '/')
							j++;
						if (str[j] == '*' && str[j + 1] == '/')
							tag = true;//标记
					}
					break;
				}
				else if (str[i] == ' ' || str[i] == '\t') {
					i++;
					while (str[i] != '\n') {
						if (str[i] != ' ' && str[i] != '\t') {
							d++;//代码前有位置控制符号
							flag = false;
							break;
						}
						else i++;
					}
					if(flag==true)k++;//空行
					break;
				}
			}
		}
	}
	printf("文件中的空行数为%d。\n", k);
	printf("文件中的代码行数为%d。\n", d);
	printf("文件中的注释行数为%d。\n", z);
	fclose(fp);
	return 1;
}

int main(int argc, char* argv[]) {
	int c = 0, w = 0, l = 0, a = 0;
	if (strcmp(argv[1], "-c") == 0) {
		c = character(argv[2]);
		printf("文件中的字符数为%d。\n", c);
	}
	else if (strcmp(argv[1], "-w") == 0) {
		w = word(argv[2]);
		printf("文件中的单词数为%d。\n", w);
	}
	else if(strcmp(argv[1], "-l") == 0){
		l = line1(argv[2]);
		printf("文件中的行数为%d。\n", l);
	}
	else if (strcmp(argv[1], "-a") == 0) {
		a = line2(argv[2]);
		if (a == 0)printf("文件为空。\n");
	}
	else printf("输入错误。\n");
}