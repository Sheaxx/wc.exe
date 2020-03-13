#include <stdio.h>
#include <string.h>
#include <io.h>
#include "wc.h"

int charactercount(char* filename) {//统计字符数
	FILE* fp;
	errno_t err;
	int c = 0;
	char ch;
	err = fopen_s(&fp, filename, "r");//打开对应文件
	if (NULL == fp) {
		printf("文件为空或不存在。\n");
		return -1;
	}
	else {
		while (feof(fp) == 0) {//当文件未结束时
			ch = fgetc(fp);
			if (ch != '\0' && ch != '\n')
				c++;
		}
		c--;//使用feof函数读取字符要多读一次才能判断是否结束，因此要减1
		fclose(fp);//关闭文件
		return c;
	}
}

int wordcount(char* filename) {//统计词数
	FILE* fp;
	errno_t err;
	int w = 0;
	char ch;
	bool flag = true;
	err = fopen_s(&fp, filename, "r");
	if (NULL == fp) {
		printf("文件为空或不存在。\n");
		return -1;
	}
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
		fclose(fp);
		return w;
	}
}

int linecount1(char* filename) {//统计行数
	FILE* fp;
	errno_t err;
	int l = 0;
	char str[100] = { 0 };
	err = fopen_s(&fp, filename, "r");
	if (NULL == fp) {
		printf("文件为空或不存在。\n");
		return -1;
	}
	else {
		while (feof(fp) == 0) {
			fgets(str, sizeof(str) - 1, fp);//fgets函数可以读取一整行
			l++;
		}
		fclose(fp);
		return l;
	}
}

int linecount2(char* filename) {//统计空行、代码行和注释行
	FILE* fp;
	errno_t err;
	int k = 0, d = 0, z = 0, i = 0, j = 0;
	char str[100] = { 0 };
	bool flag, tag = true;
	err = fopen_s(&fp, filename, "r");
	if (NULL == fp) {
		printf("文件为空或不存在。\n");
		return -1;
	}
	else {
		while (feof(fp) == 0) {
			fgets(str, sizeof(str) - 1, fp);
			for (; i <= sizeof(str); i++) {
				flag = true;
				if (((str[i] == '{' || str[i] == '}') && (str[i + 1] == '\0' || str[i + 1] == '\n')) || str[i] == '\n' || str[i] == '\0') {
					k++;//空行
					break;
				}
				else if ((str[i] == '/' && str[i + 1] == '/') || (str[i] == '}' && str[i + 1] == '/')) {
					z++;//用“//”符号的注释行
					break;
				}
				else if (str[i] == '/' && str[i + 1] == '*') {
					z++;//用“/*”符号的多行注释
					j = i + 2;
					while (str[j] != '\n' && str[j] != '*' && str[j + 1] != '/')
						j++;
					if (str[j] == '\n')tag = false;//标记
					break;
				}
				else if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n') {
					if (tag == true)d++;//代码行
					else {//注释行
						z++;
						j = i++;
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
					if (flag == true)k++;//空行
					break;
				}
			}
		}
		fclose(fp);
	}
	printf("%s文件中：\n", filename);
	printf("文件中的空行数为%d。\n", k);
	printf("文件中的代码行数为%d。\n", d);
	printf("文件中的注释行数为%d。\n\n", z);
	return k * k + d * d + z * z;//用于检测结果是否正确
}

int searchfile(char* path, char* str1, char* str2,int select) {//递归处理文件
	struct _finddata_t file;
	intptr_t Handle;
	intptr_t Handle2;
	int c, w, l, a, s = 0;
	int len = 0;
	char way1[100] = { '\0' };
	char way2[100] = { '\0' };
	char way3[100] = { '\0' };
	strcpy_s(way1, path);
	strcpy_s(way2, way1);
	strcat_s(way1, "*");
	if ((Handle = _findfirst(way1, &file)) == -1L) {
		printf("没有找到文件。\n");
		s += -1;
	}
	else {
		do {
			if (file.attrib & _A_SUBDIR) {//该文件是文件夹
				if ((strcmp(file.name, ".") != 0) && (strcmp(file.name, "..") != 0)) {
					strcpy_s(way1, file.name);
					strcat_s(way1, "\\");
					s += searchfile(way1, str1, str2, select);
				}//拼接地址，递归继续查找
			}
			else {//根据输入的操作指令对文件进行操作
				strcpy_s(way3, way2);
				switch (select) {
				case 1:
					strcat_s(way2, str2);
					if (Handle2 = _findfirst(way2, &file) == -1L) {
						continue;
					}
					else {
						strcat_s(way3, file.name);
					}
					break;
				case 2:
					len = strlen(file.name);
					if (file.name[len - 1] != 'c' && file.name[len - 2] != '.')continue;
					strcat_s(way3, file.name);
					break;
				case 3:
					strcat_s(way3, file.name);
					break;
				case 4:
					if (strcmp(str2, file.name) != 0)continue;
					strcat_s(way3, file.name);
					break;
				}
				printf("路径：%s\n", way3);
				if (strcmp(str1, "-c") == 0) {
					c = charactercount(way3);
					if (c != -1)printf("%s文件中共有%d个字符。\n\n", file.name, c);
					s += c;
				}
				else if (strcmp(str1, "-w") == 0) {
					w = wordcount(way3);
					if (w != -1)printf("%s文件中共有%d个单词。\n\n", file.name, w);
					s += w;
				}
				else if (strcmp(str1, "-l") == 0) {
					l = linecount1(way3);
					if (l != -1)printf("%s文件中共有%d行。\n\n", file.name, l);
					s += l;
				}
				else if (strcmp(str1, "-a") == 0) {
					a = linecount2(way3);
					s += a;
				}
				else {
					printf("输入操作错误。\n");
					s += -1;
				}
			}
		} while (_findnext(Handle, &file) == 0);
		_findclose(Handle);//结束查找
		return s;
	}
}

void main(int argc, char* argv[]) {
	int c = 0, w = 0, l = 0, a = 0, s = 0, i = 0;
	int select = 0;
	bool mark = true;
	char path[50] = { "\0" };
	char mode[50] = { "\0" };
	if (strcmp(argv[1], "-c") == 0) {
		c = charactercount(argv[2]);
		printf("文件中的字符数为%d。\n", c);
	}
	else if (strcmp(argv[1], "-w") == 0) {
		w = wordcount(argv[2]);
		printf("文件中的单词数为%d。\n", w);
	}
	else if (strcmp(argv[1], "-l") == 0) {
		l = linecount1(argv[2]);
		printf("文件中的行数为%d。\n", l);
	}
	else if (strcmp(argv[1], "-a") == 0) {
		a = linecount2(argv[2]);
		if (a == 0)printf("文件为空。\n");
	}
	else if (strcmp(argv[1], "-s") == 0) {
		strcpy_s(mode, argv[3]);
		while (mode[i] != '\0') {
			if (mode[i] == '?') {
				mark = false;
				break;
			}
			else i++;
		}
		if (mark == false)select = 1;
		else {
			if (strcmp(mode, "*.c") == 0)select = 2;
			else if (strcmp(mode, "*") == 0 || strcmp(mode, "*.*") == 0)select = 3;
			else select = 4;
		}//根据输入的命令行参数来判断执行不同操作
		s = searchfile(path, argv[2], argv[3],select);
	}
	else printf("输入错误。\n");
}