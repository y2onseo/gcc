CC=C:\QualityScroll-Cover-SE\wrapper\gcc\gcc.exe
AR=C:\QualityScroll-Cover-SE\wrapper\gcc\ac.exe

all:
	$(CC) -c main.c -DHAVE_STRUCT_TIMESPEC
	$(CC) -o a.exe main.o -lpthreadGCE2 -lws2_32

clean:
	rm -rf *.cpp *.o *.a libcstm* *~ a.exe
