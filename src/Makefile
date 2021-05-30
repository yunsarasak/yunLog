testBinary : ../lib/libyLog.a yLog.o yLog.c
	gcc -o $@ testb.c -I../headers -L../lib -lyLog

libyLog.a : yLog.o
	ar rc ../lib/libyLog.a yLog.o

yLog.o : yLog.c
	gcc -c -o $@ $^ -I../headers

clean :
	rm yLog.o
	rm testBinary

