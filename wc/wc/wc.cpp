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
	if (NULL == fp)return 0;
	else {
		while (feof(fp) == 0) {//���ļ�δ����ʱ
			ch = fgetc(fp);
			if (ch != '\0' && ch != '\n')
				c++;
		}
	}
	c--;//ʹ��feof������ȡ�ַ�Ҫ���һ�β����ж��Ƿ���������Ҫ��1
	fclose(fp);//�ر��ļ�
	return c;
}

int wordcount(char *filename) {//ͳ�ƴ���
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
			if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {//�����ַ�Ϊ��ĸʱ
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

int linecount1(char *filename) {//ͳ������
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

int linecount2(char* filename) {//ͳ�ƿ��С������к�ע����
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
					k++;//����
					break;
				}
				else if ((str[i] == '/' && str[i + 1] == '/')||(str[i]=='}'&&str[i+1]=='/')) {
					z++;//�á�//�����ŵ�ע����
					break;
				}
				else if (str[i] == '/' && str[i + 1] == '*') {
					z++;//�á�/*�����ŵĶ���ע��
					j = i + 2;
					while (str[j] != '\n' && str[j] != '*' && str[j + 1] != '/')
						j++;
					if(str[j]=='\n')tag = false;//���
					break;
				}
				else if (str[i] != ' ' && str[i] != '\t' && str[i]!='\n') {
					if (tag == true)d++;//������
					else {//ע����
						z++;
						j=i++;
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
					if(flag==true)k++;//����
					break;
				}
			}
		}
	}
	printf("%s�ļ��У�\n",filename);
	printf("�ļ��еĿ�����Ϊ%d��\n", k);
	printf("�ļ��еĴ�������Ϊ%d��\n", d);
	printf("�ļ��е�ע������Ϊ%d��\n", z);
	fclose(fp);
	return k+d+z;//���ڼ��
}

void searchfile(char *path,char *mode,char *str) {//�ݹ鴦���ļ�
	struct _finddata_t file;
	intptr_t Handle;
	char way[100] = { '\0' };
	strcpy_s(way, path);
	strcat_s(way, "\\");
	strcat_s(way, mode);
	if ((Handle = _findfirst(way, &file)) == -1L) {
		printf("û���ҵ��ļ���\n");
		return;
	}
	do {
		if (file.attrib == _A_SUBDIR) {//���ļ����ļ���
			if ((strcmp(file.name, ".") != 0) && (strcmp(file.name, "..") != 0)) {
				strcat_s(way, "\\");
				strcat_s(way, file.name);
				searchfile(way, mode, str);//�����ļ��м�������
			}
			
		}
		else {//��������Ĳ���ָ����ļ����в���
			if (strcmp(str, "-c") == 0)
				printf("%s�ļ��й���%d���ַ���\n", file.name, charactercount(file.name));
			else if (strcmp(str, "-w") == 0)
				printf("%s�ļ��й���%d�����ʡ�\n", file.name, wordcount(file.name));
			else if (strcmp(str, "-l") == 0)
				printf("%s�ļ��й���%d�С�\n", file.name, linecount1(file.name));
			else if (strcmp(str, "-a") == 0)
				linecount2(file.name);
		}
	}while(_findnext(Handle, &file) == 0);
	_findclose(Handle);//��������
}

int main(int argc, char* argv[]) {
	int c = 0, w = 0, l = 0, a = 0;
	char path[50] = { '\0' };
	char mode[20] = { '\0' };
	if (strcmp(argv[1], "-c") == 0) {
		c = charactercount(argv[2]);
		printf("�ļ��е��ַ���Ϊ%d��\n", c);
	}
	else if (strcmp(argv[1], "-w") == 0) {
		w = wordcount(argv[2]);
		printf("�ļ��еĵ�����Ϊ%d��\n", w);
	}
	else if(strcmp(argv[1], "-l") == 0){
		l = linecount1(argv[2]);
		printf("�ļ��е�����Ϊ%d��\n", l);
	}
	else if (strcmp(argv[1], "-a") == 0) {
		a = linecount2(argv[2]);
		if (a == 0)printf("�ļ�Ϊ�ա�\n");
	}
	else if (strcmp(argv[1], "-s") == 0) {
		printf("�������ļ�·����");
		scanf_s("%s", path, 50);
		printf("�������ļ����ƣ�");
		scanf_s("%s", mode, 20);
		searchfile(path, mode, argv[2]);
	}
	else printf("�������\n");
}