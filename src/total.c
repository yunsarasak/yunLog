#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_BYTE 1000

#define YLog_e(X, ...) logWrite(ERR, __FILE__, __LINE__, X, __VA_ARGS__)
#define YLog_s(X, ...) logWrite(SVC, __FILE__, __LINE__, X, __VA_ARGS__)
#define YLog_d(X, ...) logWrite(DBG, __FILE__, __LINE__, X, __VA_ARGS__)

typedef enum LLV {
	NONE = 0,
	ERR,
	SVC,
	DBG
}LLV;

LLV currLv;
FILE* fp;
char path[1000];
char savingDir[1000];
int fIndex;

void setDir(char*);

void logWrite(LLV _lv, char* _fileName, int _numLine, char* _fmt, ...);
void splitString(char* _ori, char* _st1, char* _st2, int _sep) {
	memcpy(_st1, _ori, _sep);
	strcat(_st1, "");
	memcpy(_st2, _ori + _sep, strlen(_ori) - _sep);
	strcat(_st2, "");
}

char* make_message(const char* fmt, ...)
{
	int n = 0;
	size_t size = 0;
	char* p = NULL;
	va_list ap;

	/* Determine required size. */

	va_start(ap, fmt);
	n = vsnprintf(p, size, fmt, ap);
	va_end(ap);

	if (n < 0)
		return NULL;

	size = (size_t)n + 1; /* One extra byte for '\0' */
	p = malloc(size);
	if (p == NULL)
		return NULL;

	va_start(ap, fmt);
	n = vsnprintf(p, size, fmt, ap);
	va_end(ap);

	if (n < 0)
	{
		free(p);
		return NULL;
	}

	return p;
}

void setFP() {
	if (fp != NULL) {
		fclose(fp);
	}

	fIndex = 0;

	while (1) {
		memset(path, 0, sizeof(path));
		strcat(path, make_message("%s/", savingDir));
		strcat(path, make_message("%s", __DATE__));
		strcat(path, make_message("#%d", fIndex));
		strcat(path, make_message("%s", ".log"));

		fp = fopen(path, "a");
		fseek(fp, 0, SEEK_END);
		int fSize = ftell(fp);
		fclose(fp);


		if (fSize < MAX_BYTE) {
			fp = fopen(path, "a");
			return;
		}
		else {
			fIndex++;
		}
	}
}

void logWrite(LLV _lv, char* _fileName, int _numLine, char* _fmt, ...) {
	va_list ap;
	va_start(ap, _fmt);
	char msg[1000] = {'\0'};
	strcat(msg, make_message("%s:%d ", _fileName, _numLine));
	strcat(msg, make_message(_fmt, ap));
	va_end(ap);

	int fSize;
	setFP();
	fseek(fp, 0, SEEK_CUR);
	fSize = ftell(fp);
	setFP();

	int length = strlen(msg);

	if (fSize + length <= MAX_BYTE) {
		fprintf(fp, "%s", msg);
	}
	else {
		char sub1[1000]={'\0'};
		char sub2[1000]={'\0'};
		splitString(msg, sub1, sub2, (MAX_BYTE - fSize));
		fprintf(fp, "%s", sub1);
		setFP();
		fprintf(fp, "%s", sub2);
	}


}

void setLv(LLV _lv) {
	currLv = _lv;
}

void setDir(char* _path){
	struct stat st = {0};

	if (stat(_path, &st) == -1) {
		mkdir(_path, S_IRWXU | S_IRWXG | S_IRWXO );
	}	

	strcpy(savingDir, _path);
}

void logInit() {
	setDir("./");
	setFP();
	setLv(NONE);

}



void logFin() {
	fclose(fp);

}

int main() {
	//testcode
	char key1;

	logInit();

	setDir("testdir");

	printf("press key : ");
	scanf("%c", &key1);
	//	printf("key1 : %c", key1);
	while (getchar() != '\n');
	//	YLog_d("key %c is pressed\n", key1);

	while (key1 != 'q')
	{
		printf("press key : ");
		scanf("%c", &key1);
		while (getchar() != '\n');
		YLog_d("key %c is pressed\n", key1);
	}

	logFin();


}
