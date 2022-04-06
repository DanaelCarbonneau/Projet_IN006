all : test_SHA256

test_SHA256 : test_SHA256.c
	gcc -o test_SHA256 test_SHA256.c -lssl -lcrypto

clean : rm *.o test_SHA256