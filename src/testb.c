#include"yLog.h"

int main() {
	//testcode
	char key1;

	logInit();

//	setDir("testdir");

	printf("press key : ");
	scanf("%c", &key1);
	//	printf("key1 : %c", key1);
	while (getchar() != '\n');
	//	YLog_d("key %c is pressed\n", key1);
	YLog_d("key %c is pressed\n", key1);
	while (key1 != 'q')
	{
		printf("press key : ");
		scanf("%c", &key1);
		while (getchar() != '\n');
		YLog_d("key %c is pressed\n", key1);
	}

	logFin();


}
