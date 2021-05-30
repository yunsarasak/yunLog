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
void setLv(LLV _lv);
void setFP();

void logInit();
void logFin();

char* make_message(const char* _fmt, ...);
void logWrite(LLV _lv, char* _fileName, int _numLine, char* _fmt, ...);
void splitString(char* _ori, char* _str1, char* _str2, int _sep);

