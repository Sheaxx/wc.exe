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
	err = fopen_s(&fp, way, "r");
	printf("·����%s\n", way);
	if (NULL == fp) {
		printf("�ļ�Ϊ�ջ򲻴��ڡ�\n");
		return -1;
	}
	else {
		while (feof(fp) == 0) {
			ch = fgetc(fp);
			if (ch != '\0' && ch != '\n')
				c++;
		}
		c--;//ʹ��feof������ȡ�ַ�Ҫ���һ�β����ж��Ƿ���������Ҫ��1
		fclose(fp);
		return c;
	}
}

int wordcount(char*path,char* filename) {//ͳ�ƴ���
	FILE* fp;
	errno_t err;
	int w = 0;
	char ch;
	bool mark = true;
	char way[100] = { '\0' };
	strcpy_s(way, path);
	strcat_s(way, 100, filename);
	err = fopen_s(&fp, way, "r");
	printf("·����%s\n", way);
	if (NULL == fp) {
		printf("�ļ�Ϊ�ջ򲻴��ڡ�\n");
		return -1;
	}
	else {
		while (feof(fp) == 0) {
			ch = fgetc(fp);
			if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')|| ch >= '0' && ch <= '9') {
				if (mark == true) {//�����ַ�Ϊ��ĸ�������ұ��Ϊtrueʱ����������һ
					w++;
					mark = false;
				}
			}
			else mark = true;//�����ַ�Ϊ�����ַ�ʱ���ñ�־
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
	err = fopen_s(&fp, way, "r");
	printf("·����%s\n", way);
	if (NULL == fp) {
		printf("�ļ�Ϊ�ջ򲻴��ڡ�\n");
		return -1;
	}
	else {
		while (feof(fp) == 0) {
			fgets(str, sizeof(str) - 1, fp);//��ȡһ����
			l++;
		}
		fclose(fp);
		return l;
	}
}

int linecount2(char*path,char* filename) {//ͳ�ƿ��С������к�ע����
	FILE* fp;
	errno_t err;
	int k = 0, d = 0, z = 0, i;
	bool flag, tag = true;
	char str[100] = { '\0' };
	char way[100] = { '\0' };
	strcpy_s(way, path);
	strcat_s(way, 100, filename);
	err = fopen_s(&fp, way, "r");
	printf("·����%s\n", way);
	if (NULL == fp) {
		printf("�ļ�Ϊ�ջ򲻴��ڡ�\n");
		return -1;
	}
	else {
		while (feof(fp) == 0) {
			fgets(str, sizeof(str) - 1, fp);
			flag = true;
			if (str[0] == '\n' || str[0] == '\0') {
				k++;//���У������ݵ����
			}
			else if (str[0] == '{' || str[0] == '}') {
				if (str[1] == '\0' || str[1] == '\n')
					k++;//���У�ֻ�д����ŵ����
				else if (str[1] == '/' && str[2] == '/')
					z++;//ע���У����ź��ע�͵����
				else d++;
			}
			else if (str[0] == '/' && str[1] == '/') {
				z++;//�á�//�����ŵ�ע����
			}
			else if (str[0] == '/' && str[1] == '*') {
				z++;//�á�/*�����ŵĶ���ע��
				i = 2;
				while (str[i] != '\n' && str[i] != '*' && str[i + 1] != '/')
					i++;
				if (str[i] == '\n')tag = false;//���
			}
			else {
				if (tag == true) {//����ע����
					i = 0;
					while (str[i] != '\n' && str[i] != '\0') {
						if (str[i] == '/' && str[i + 1] == '*') {
							z++;//����ע�͵Ŀ�ʼ
							tag = false;
							break;
						}
						else if (str[i] != '\t' && str[i] != ' ') {
							d++;//����ǰ������λ�ÿ��Ʒ���
							flag = false;
							break;
						}
						else i++;
					}
					if (flag == true && tag == true) k++;
				}
				else {//ע����
					z++;
					i = 0;
					while (str[i] != '\n' && str[i] != '\0') {
						if (str[i] == '*' && str[i + 1] == '/')
							tag = true;//ע���н��������ñ��
						i++;
					}
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

int searchfile(char *path, char *op, char *mode) {//�ݹ鴦���ļ�
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

	if ((Handle1 = _findfirst(way1, &file1)) == -1L) {//Handle1���������ļ�
		printf("%s��û���ҵ������ļ���\n", way4);
	}
	else {
		do {
			if (file1.attrib & _A_SUBDIR) {//���ļ����ļ���
				if ((strcmp(file1.name, ".") != 0) && (strcmp(file1.name, "..") != 0)) {
					strcat_s(way4, file1.name);
					strcat_s(way4, "\\");
					s += searchfile(way4, op, mode);
				}//ƴ�ӵ�ַ���ݹ��������
			}
		}while(_findnext(Handle1, &file1) == 0);
		_findclose(Handle1);
	}

	if ((Handle2 = _findfirst(way2, &file2)) == -1L) {//Handle2�����ض��ļ�
		printf("%s��û���ҵ������ļ���\n", way3);
	}
	else {
		do {
			if (file2.attrib & _A_SUBDIR)continue;//�ļ��в��ܲ�ѯ
			else if ((strcmp(file2.name, ".") == 0) || (strcmp(file2.name, "..") == 0))continue;
			
			if (strcmp(op, "-c") == 0) {
				c = charactercount(way3, file2.name);
				if (c != -1)printf("%s�ļ��й���%d���ַ���\n\n", file2.name, c);
				s += c;
			}
			else if (strcmp(op, "-w") == 0) {
				w = wordcount(way3, file2.name);
				if (w != -1)printf("%s�ļ��й���%d�����ʡ�\n\n", file2.name, w);
				s += w;
			}
			else if (strcmp(op, "-l") == 0) {
				l = linecount1(way3, file2.name);
				if (l != -1)printf("%s�ļ��й���%d�С�\n\n", file2.name, l);
				s += l;
			}
			else if (strcmp(op, "-a") == 0) {
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
	int len = 0, i = 0, j = 0;
	char path[50] = { '\0' };
	char mode[50] = { '\0' };
	char str[100] = { '\0' };
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
	else printf("�������\n");
}