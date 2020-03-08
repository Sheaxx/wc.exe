#include<stdio.h>

int character(char* filename) {//统计字符数
	FILE* fp;
	errno_t err;
	int c = 0;
	char ch;
	err = fopen_s(&fp, filename, "r");//打开对应文件
	if (NULL == fp)return 0;
	else {
		while (feof(fp) == 0) {//当文件未结束时
			ch = fgetc(fp);
			if (ch != '\0' && ch != '\n')
				c++;
		}
	}
	c--;//使用feof函数读取字符要多读一次才能判断是否结束，因此要减1
	fclose(fp);//关闭文件
	return c;
}