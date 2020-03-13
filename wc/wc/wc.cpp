#include <stdio.h>
#include <string.h>
#include <io.h>
#include "wc.h"

int charactercount(char *path,char *filename) {//ͳ���ַ���
	FILE* fp;
	errno_t err;
	int c = 0;
	char ch;
	char way[100] = { '\0' };
	strcpy_s(way, path);
	strcat_s(way, 100, filename);
	err = fopen_s(&fp, way, "r");//�򿪶�Ӧ�ļ�
	printf("·����%s\n", way);
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

int wordcount(char*path,char* filename) {//ͳ�ƴ���
	FILE* fp;
	errno_t err;
	int w = 0;
	char ch;
	bool flag = true;
	char way[100] = { '\0' };
	strcpy_s(way, path);
	strcat_s(way, 100, filename);
	err = fopen_s(&fp, way, "r");//�򿪶�Ӧ�ļ�
	printf("·����%s\n", way);
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

int linecount1(char*path,char* filename) {//ͳ������
	FILE* fp;
	errno_t err;
	int l = 0;
	char str[100] = { 0 };
	char way[100] = { '\0' };
	strcpy_s(way, path);
	strcat_s(way, 100, filename);
	err = fopen_s(&fp, way, "r");//�򿪶�Ӧ�ļ�
	printf("·����%s\n", way);
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

int linecount2(char*path,char* filename) {//ͳ�ƿ��С������к�ע����
	FILE* fp;
	errno_t err;
	int k = 0, d = 0, z = 0, i = 0, j = 0;
	char str[100] = { 0 };
	bool flag, tag = true;
	char way[100] = { '\0' };
	strcpy_s(way, path);
	strcat_s(way, 100, filename);
	err = fopen_s(&fp, way, "r");//�򿪶�Ӧ�ļ�
	printf("·����%s\n", way);
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

int searchfile(char *path, char *str1, char *str2) {//�ݹ鴦���ļ�
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
	strcat_s(way2, str2);

	if ((Handle1 = _findfirst(way1, &file1)) == -1L) {//Handle1���������ļ�
		printf("û���ҵ��ļ���\n");
	}
	else {
		do {
			if (file1.attrib & _A_SUBDIR) {//���ļ����ļ���
				if ((strcmp(file1.name, ".") != 0) && (strcmp(file1.name, "..") != 0)) {
					strcat_s(way4, file1.name);
					strcat_s(way4, "\\");
					s += searchfile(way4, str1, str2);
				}//ƴ�ӵ�ַ���ݹ��������
			}
		}while(_findnext(Handle1, &file1) == 0);
		_findclose(Handle1);
	}

	if ((Handle2 = _findfirst(way2, &file2)) == -1L) {//Handle2�����ض��ļ�
		printf("û���ҵ��ļ���\n");
	}
	else {
		do {
			if (file2.attrib & _A_SUBDIR)continue;
			else if ((strcmp(file2.name, ".") == 0) || (strcmp(file2.name, "..") == 0))continue;
			
			if (strcmp(str1, "-c") == 0) {
				c = charactercount(way3, file2.name);
				if (c != -1)printf("%s�ļ��й���%d���ַ���\n\n", file2.name, c);
				s += c;
			}
			else if (strcmp(str1, "-w") == 0) {
				w = wordcount(way3, file2.name);
				if (w != -1)printf("%s�ļ��й���%d�����ʡ�\n\n", file2.name, w);
				s += w;
			}
			else if (strcmp(str1, "-l") == 0) {
				l = linecount1(way3, file2.name);
				if (l != -1)printf("%s�ļ��й���%d�С�\n\n", file2.name, l);
				s += l;
			}
			else if (strcmp(str1, "-a") == 0) {
				a = linecount2(way3, file2.name);
				s += a;
			}
			else {
				printf("�����������\n");
				s += -1;
			}
		} while (_findnext(Handle2, &file2) == 0);
		_findclose(Handle2);
	}
	return s;
}

void main(int argc, char* argv[]) {
	int c = 0, w = 0, l = 0, a = 0, s = 0;
	char path[50] = { '\0' };
	if (strcmp(argv[1], "-c") == 0) {
		c = charactercount(path,argv[2]);
		printf("�ļ��е��ַ���Ϊ%d��\n", c);
	}
	else if (strcmp(argv[1], "-w") == 0) {
		w = wordcount(path,argv[2]);
		printf("�ļ��еĵ�����Ϊ%d��\n", w);
	}
	else if (strcmp(argv[1], "-l") == 0) {
		l = linecount1(path,argv[2]);
		printf("�ļ��е�����Ϊ%d��\n", l);
	}
	else if (strcmp(argv[1], "-a") == 0) {
		a = linecount2(path,argv[2]);
		if (a == 0)printf("�ļ�Ϊ�ա�\n");
	}
	else if (strcmp(argv[1], "-s") == 0) 
		s = searchfile(path, argv[2], argv[3]);
	else printf("�������\n");
}