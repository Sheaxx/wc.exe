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
	printf("%s\n",filename);
	if (NULL == fp) {
		printf("文件为空。\n");
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
		printf("文件为空。\n");
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
		printf("文件为空。\n");
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
		printf("文件为空。\n");
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
	printf("文件中的注释行数为%d。\n", z);
	return k * k + d * d + z * z;//用于检测结果是否正确
}

int searchfile(char* path, char* mode, char* str) {//递归处理文件
	struct _finddata_t file;
	intptr_t Handle;
	int c, w, l, a, x = 0;
	char way1[100] = { '\0' };
	char way2[100] = { '\0' };
	strcpy_s(way1, path);
	strcpy_s(way2, path);
	strcat_s(way1, "\\");
	strcat_s(way1, mode);
	if ((Handle = _findfirst(way1, &file)) == -1L)
		printf("没有找到文件。\n");
	else {
		do {
			if (file.attrib & _A_SUBDIR) {//该文件是文件夹
				if ((strcmp(file.name, ".") != 0) && (strcmp(file.name, "..") != 0)) {
					if (strcmp(mode, "*") == 0 || strcmp(mode, "*.*") == 0) {
						strcat_s(way2, "\\");
						strcat_s(way2, file.name);
						searchfile(way2, mode, str);
					}//如果输入的是*，则先求出文件名再拼接
					else searchfile(way1, mode, str);//若输入文件名，则可以直接拼接进入递归
				}
			}
			else {//根据输入的操作指令对文件进行操作
				if (strcmp(str, "-c") == 0) {
					c = charactercount(way1);
					if (c != -1)printf("%s文件中共有%d个字符。\n", file.name, c);
					x = c;
				}
				else if (strcmp(str, "-w") == 0) {
					w = wordcount(way1);
					if (w != -1)printf("%s文件中共有%d个单词。\n", file.name, w);
					x = w;
				}	
				else if (strcmp(str, "-l") == 0) {
					l = linecount1(way1);
					if (l != -1)printf("%s文件中共有%d行。\n", file.name, l);
					x = l;
				}
				else if (strcmp(str, "-a") == 0) {
					a = linecount2(file.name);
					x = a;
				}
			}
		} while (_findnext(Handle, &file) == 0);
		_findclose(Handle);//结束查找
		return x;
	}
}

int main(int argc, char* argv[]) {
	int c = 0, w = 0, l = 0, a = 0;
	char path[50] = { '\0' };
	char mode[20] = { '\0' };
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
		printf("请输入文件路径：");
		scanf_s("%s", path, 50);
		printf("请输入文件名称：");
		scanf_s("%s", mode, 20);
		searchfile(path, mode, argv[2]);
	}
	else printf("输入错误。\n");
}