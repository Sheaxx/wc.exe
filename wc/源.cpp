#include <stdio.h>
#include<string.h>
#include"wc.h"


int word(char *filename) {//ͳ�ƴ���
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

int line1(char *filename) {//ͳ������
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

int line2(char* filename) {//ͳ�ƿ��С������к�ע����
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
	printf("�ļ��еĿ�����Ϊ%d��\n", k);
	printf("�ļ��еĴ�������Ϊ%d��\n", d);
	printf("�ļ��е�ע������Ϊ%d��\n", z);
	fclose(fp);
	return 1;
}

int main(int argc, char* argv[]) {
	int c = 0, w = 0, l = 0, a = 0;
	if (strcmp(argv[1], "-c") == 0) {
		c = character(argv[2]);
		printf("�ļ��е��ַ���Ϊ%d��\n", c);
	}
	else if (strcmp(argv[1], "-w") == 0) {
		w = word(argv[2]);
		printf("�ļ��еĵ�����Ϊ%d��\n", w);
	}
	else if(strcmp(argv[1], "-l") == 0){
		l = line1(argv[2]);
		printf("�ļ��е�����Ϊ%d��\n", l);
	}
	else if (strcmp(argv[1], "-a") == 0) {
		a = line2(argv[2]);
		if (a == 0)printf("�ļ�Ϊ�ա�\n");
	}
	else printf("�������\n");
}