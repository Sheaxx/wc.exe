#include<stdio.h>

int character(char* filename) {//ͳ���ַ���
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