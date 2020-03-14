#include <stdio.h>
#include <string.h>
#include <io.h>
#include "wc.h"

int charactercount(char *path,char *filename) {//统计字符数
	FILE* fp;
	errno_t err;
	int c = 0;
	char ch;
	char way[100] = { '\0' };
	strcpy_s(way, path);
	strcat_s(way, 100, filename);
	err = fopen_s(&fp, way, "r");
	printf("路径：%s\n", way);
	if (NULL == fp) {
		printf("文件为空或不存在。\n");
		return -1;
	}
	else {
		while (feof(fp) == 0) {
			ch = fgetc(fp);
			if (ch != '\0' && ch != '\n')
				c++;
		}
		c--;//使用feof函数读取字符要多读一次才能判断是否结束，因此要减1
		fclose(fp);
		return c;
	}
}

int wordcount(char*path,char* filename) {//统计词数
	FILE* fp;
	errno_t err;
	int w = 0;
	char ch;
	bool mark = true;
	char way[100] = { '\0' };
	strcpy_s(way, path);
	strcat_s(way, 100, filename);
	err = fopen_s(&fp, way, "r");
	printf("路径：%s\n", way);
	if (NULL == fp) {
		printf("文件为空或不存在。\n");
		return -1;
	}
	else {
		while (feof(fp) == 0) {
			ch = fgetc(fp);
			if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')|| ch >= '0' && ch <= '9') {
				if (mark == true) {//当该字符为字母或数字且标记为true时，单词数加一
					w++;
					mark = false;
				}
			}
			else mark = true;//当该字符为其他字符时重置标志
		}
		fclose(fp);
		return w;
	}
}

int linecount1(char*path,char* filename) {//统计行数
	FILE* fp;
	errno_t err;
	int l = 0;
	char str[100] = { 0 };
	char way[100] = { '\0' };
	strcpy_s(way, path);
	strcat_s(way, 100, filename);
	err = fopen_s(&fp, way, "r");
	printf("路径：%s\n", way);
	if (NULL == fp) {
		printf("文件为空或不存在。\n");
		return -1;
	}
	else {
		while (feof(fp) == 0) {
			fgets(str, sizeof(str) - 1, fp);//读取一整行
			l++;
		}
		fclose(fp);
		return l;
	}
}

int linecount2(char*path,char* filename) {//统计空行、代码行和注释行
	FILE* fp;
	errno_t err;
	int k = 0, d = 0, z = 0, i;
	bool flag, tag = true;
	char str[100] = { '\0' };
	char way[100] = { '\0' };
	strcpy_s(way, path);
	strcat_s(way, 100, filename);
	err = fopen_s(&fp, way, "r");
	printf("路径：%s\n", way);
	if (NULL == fp) {
		printf("文件为空或不存在。\n");
		return -1;
	}
	else {
		while (feof(fp) == 0) {
			fgets(str, sizeof(str) - 1, fp);
			flag = true;
			if (str[0] == '\n' || str[0] == '\0') {
				k++;//空行，无内容的情况
			}
			else if (str[0] == '{' || str[0] == '}') {
				if (str[1] == '\0' || str[1] == '\n')
					k++;//空行，只有大括号的情况
				else if (str[1] == '/' && str[2] == '/')
					z++;//注释行，括号后跟注释的情况
				else d++;
			}
			else if (str[0] == '/' && str[1] == '/') {
				z++;//用“//”符号的注释行
			}
			else if (str[0] == '/' && str[1] == '*') {
				z++;//用“/*”符号的多行注释
				i = 2;
				while (str[i] != '\n' && str[i] != '*' && str[i + 1] != '/')
					i++;
				if (str[i] == '\n')tag = false;//标记
			}
			else {
				if (tag == true) {//不是注释行
					i = 0;
					while (str[i] != '\n' && str[i] != '\0') {
						if (str[i] == '/' && str[i + 1] == '*') {
							z++;//多行注释的开始
							tag = false;
							break;
						}
						else if (str[i] != '\t' && str[i] != ' ') {
							d++;//代码前可能有位置控制符号
							flag = false;
							break;
						}
						else i++;
					}
					if (flag == true && tag == true) k++;
				}
				else {//注释行
					z++;
					i = 0;
					while (str[i] != '\n' && str[i] != '\0') {
						if (str[i] == '*' && str[i + 1] == '/')
							tag = true;//注释行结束，重置标记
						i++;
					}
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

int searchfile(char *path, char *op, char *mode) {//递归处理文件
	struct _finddata_t file1;
	struct _finddata_t file2;
	intptr_t Handle1;
	intptr_t Handle2;
	int c, w, l, a, s = 0;
	char way1[100] = { '\0' };
	char way2[100] = { '\0' };
	char way3[100] = { '\0' };
	char way4[100] = { '\0' };
	strcpy_s(way1, path);
	strcpy_s(way2, path);
	strcpy_s(way3, path);
	strcpy_s(way4, path);
	strcat_s(way1, "*");
	strcat_s(way2, mode);

	if ((Handle1 = _findfirst(way1, &file1)) == -1L) {//Handle1查找所有文件
		printf("%s中没有找到符合文件。\n", way4);
	}
	else {
		do {
			if (file1.attrib & _A_SUBDIR) {//该文件是文件夹
				if ((strcmp(file1.name, ".") != 0) && (strcmp(file1.name, "..") != 0)) {
					strcat_s(way4, file1.name);
					strcat_s(way4, "\\");
					s += searchfile(way4, op, mode);
				}//拼接地址，递归继续查找
			}
		}while(_findnext(Handle1, &file1) == 0);
		_findclose(Handle1);
	}

	if ((Handle2 = _findfirst(way2, &file2)) == -1L) {//Handle2查找特定文件
		printf("%s中没有找到符合文件。\n", way3);
	}
	else {
		do {
			if (file2.attrib & _A_SUBDIR)continue;//文件夹不能查询
			else if ((strcmp(file2.name, ".") == 0) || (strcmp(file2.name, "..") == 0))continue;
			
			if (strcmp(op, "-c") == 0) {
				c = charactercount(way3, file2.name);
				if (c != -1)printf("%s文件中共有%d个字符。\n\n", file2.name, c);
				s += c;
			}
			else if (strcmp(op, "-w") == 0) {
				w = wordcount(way3, file2.name);
				if (w != -1)printf("%s文件中共有%d个单词。\n\n", file2.name, w);
				s += w;
			}
			else if (strcmp(op, "-l") == 0) {
				l = linecount1(way3, file2.name);
				if (l != -1)printf("%s文件中共有%d行。\n\n", file2.name, l);
				s += l;
			}
			else if (strcmp(op, "-a") == 0) {
				a = linecount2(way3, file2.name);
				s += a;
			}
			else {
				printf("输入操作错误。\n");
				s += -1;
			}
		} while (_findnext(Handle2, &file2) == 0);
		_findclose(Handle2);
	}
	return s;
}

void main(int argc, char* argv[]) {
	int c = 0, w = 0, l = 0, a = 0, s = 0;
	int len = 0, i = 0, j = 0;
	char path[50] = { '\0' };
	char mode[50] = { '\0' };
	char str[100] = { '\0' };
	if (strcmp(argv[1], "-c") == 0) {
		c = charactercount(path,argv[2]);
		printf("文件中的字符数为%d。\n", c);
	}
	else if (strcmp(argv[1], "-w") == 0) {
		w = wordcount(path,argv[2]);
		printf("文件中的单词数为%d。\n", w);
	}
	else if (strcmp(argv[1], "-l") == 0) {
		l = linecount1(path,argv[2]);
		printf("文件中的行数为%d。\n", l);
	}
	else if (strcmp(argv[1], "-a") == 0) {
		a = linecount2(path,argv[2]);
		if (a == 0)printf("文件为空。\n");
	}
	else if (strcmp(argv[1], "-s") == 0) {
		len = strlen(argv[3]) - 1;
		i = len;
		strcpy_s(str, argv[3]);
		while (i >= 0) {
			if (str[i] == '\\')break;
			else i--;
		}
		if (i >= 0) {
			strncpy_s(path, str, i + 1);
			while (i <= len) {
				mode[j] = str[i];
				j++; i++;
			}
		}
		else strcpy_s(mode, argv[3]);
		s = searchfile(path, argv[2], mode);
	}
	else printf("输入错误。\n");
}