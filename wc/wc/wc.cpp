#include <stdio.h>
#include <string.h>
#include <io.h>
#include "wc.h"

int charactercount(char* filename) {//ͳ���ַ���
	FILE* fp;
	errno_t err;
	int c = 0;
	char ch;
	err = fopen_s(&fp, filename, "r");//�򿪶�Ӧ�ļ�
	if (NULL == fp) {
		printf("�ļ�Ϊ�ջ򲻴��ڡ�\n");
		return -1;
	}
	else {
		while (feof(fp) == 0) {//���ļ�δ����ʱ
			ch = fgetc(fp);
			if (ch != '\0' && ch != '\n')
				c++;
		}
		c--;//ʹ��feof������ȡ�ַ�Ҫ���һ�β����ж��Ƿ���������Ҫ��1
		fclose(fp);//�ر��ļ�
		return c;
	}
}

int wordcount(char* filename) {//ͳ�ƴ���
	FILE* fp;
	errno_t err;
	int w = 0;
	char ch;
	bool flag = true;
	err = fopen_s(&fp, filename, "r");
	if (NULL == fp) {
		printf("�ļ�Ϊ�ջ򲻴��ڡ�\n");
		return -1;
	}
	else {
		while (feof(fp) == 0) {
			ch = fgetc(fp);
			if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {//�����ַ�Ϊ��ĸʱ
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

int linecount1(char* filename) {//ͳ������
	FILE* fp;
	errno_t err;
	int l = 0;
	char str[100] = { 0 };
	err = fopen_s(&fp, filename, "r");
	if (NULL == fp) {
		printf("�ļ�Ϊ�ջ򲻴��ڡ�\n");
		return -1;
	}
	else {
		while (feof(fp) == 0) {
			fgets(str, sizeof(str) - 1, fp);//fgets�������Զ�ȡһ����
			l++;
		}
		fclose(fp);
		return l;
	}
}

int linecount2(char* filename) {//ͳ�ƿ��С������к�ע����
	FILE* fp;
	errno_t err;
	int k = 0, d = 0, z = 0, i = 0, j = 0;
	char str[100] = { 0 };
	bool flag, tag = true;
	err = fopen_s(&fp, filename, "r");
	if (NULL == fp) {
		printf("�ļ�Ϊ�ջ򲻴��ڡ�\n");
		return -1;
	}
	else {
		while (feof(fp) == 0) {
			fgets(str, sizeof(str) - 1, fp);
			for (; i <= sizeof(str); i++) {
				flag = true;
				if (((str[i] == '{' || str[i] == '}') && (str[i + 1] == '\0' || str[i + 1] == '\n')) || str[i] == '\n' || str[i] == '\0') {
					k++;//����
					break;
				}
				else if ((str[i] == '/' && str[i + 1] == '/') || (str[i] == '}' && str[i + 1] == '/')) {
					z++;//�á�//�����ŵ�ע����
					break;
				}
				else if (str[i] == '/' && str[i + 1] == '*') {
					z++;//�á�/*�����ŵĶ���ע��
					j = i + 2;
					while (str[j] != '\n' && str[j] != '*' && str[j + 1] != '/')
						j++;
					if (str[j] == '\n')tag = false;//���
					break;
				}
				else if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n') {
					if (tag == true)d++;//������
					else {//ע����
						z++;
						j = i++;
						while (str[j] != '\n' && str[j] != '*' && str[j + 1] != '/')
							j++;
						if (str[j] == '*' && str[j + 1] == '/')
							tag = true;//���
					}
					break;
				}
				else if (str[i] == ' ' || str[i] == '\t') {
					i++;
					while (str[i] != '\n') {
						if (str[i] != ' ' && str[i] != '\t') {
							d++;//����ǰ��λ�ÿ��Ʒ���
							flag = false;
							break;
						}
						else i++;
					}
					if (flag == true)k++;//����
					break;
				}
			}
		}
		fclose(fp);
	}
	printf("%s�ļ��У�\n", filename);
	printf("�ļ��еĿ�����Ϊ%d��\n", k);
	printf("�ļ��еĴ�������Ϊ%d��\n", d);
	printf("�ļ��е�ע������Ϊ%d��\n\n", z);
	return k * k + d * d + z * z;//���ڼ�����Ƿ���ȷ
}

int searchfile(char* path, char* str1, char* str2,int select) {//�ݹ鴦���ļ�
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
		printf("û���ҵ��ļ���\n");
		s += -1;
	}
	else {
		do {
			if (file.attrib & _A_SUBDIR) {//���ļ����ļ���
				if ((strcmp(file.name, ".") != 0) && (strcmp(file.name, "..") != 0)) {
					strcpy_s(way1, file.name);
					strcat_s(way1, "\\");
					s += searchfile(way1, str1, str2, select);
				}//ƴ�ӵ�ַ���ݹ��������
			}
			else {//��������Ĳ���ָ����ļ����в���
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
				printf("·����%s\n", way3);
				if (strcmp(str1, "-c") == 0) {
					c = charactercount(way3);
					if (c != -1)printf("%s�ļ��й���%d���ַ���\n\n", file.name, c);
					s += c;
				}
				else if (strcmp(str1, "-w") == 0) {
					w = wordcount(way3);
					if (w != -1)printf("%s�ļ��й���%d�����ʡ�\n\n", file.name, w);
					s += w;
				}
				else if (strcmp(str1, "-l") == 0) {
					l = linecount1(way3);
					if (l != -1)printf("%s�ļ��й���%d�С�\n\n", file.name, l);
					s += l;
				}
				else if (strcmp(str1, "-a") == 0) {
					a = linecount2(way3);
					s += a;
				}
				else {
					printf("�����������\n");
					s += -1;
				}
			}
		} while (_findnext(Handle, &file) == 0);
		_findclose(Handle);//��������
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
		printf("�ļ��е��ַ���Ϊ%d��\n", c);
	}
	else if (strcmp(argv[1], "-w") == 0) {
		w = wordcount(argv[2]);
		printf("�ļ��еĵ�����Ϊ%d��\n", w);
	}
	else if (strcmp(argv[1], "-l") == 0) {
		l = linecount1(argv[2]);
		printf("�ļ��е�����Ϊ%d��\n", l);
	}
	else if (strcmp(argv[1], "-a") == 0) {
		a = linecount2(argv[2]);
		if (a == 0)printf("�ļ�Ϊ�ա�\n");
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
		}//��������������в������ж�ִ�в�ͬ����
		s = searchfile(path, argv[2], argv[3],select);
	}
	else printf("�������\n");
}