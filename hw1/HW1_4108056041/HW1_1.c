#include <sys/time.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	struct timeval start;
	struct timeval end;
	unsigned long diff;
	int i, j;
	//int x;
	//char buffer[10000];



	//step0 : create a 200MB file
	FILE *f1;
	f1 = fopen("hw11.txt", "w");



	for(i = 0; i<209715200; i++) {
		fprintf(f1, "a");
	}


	//FILE *f1;
	//f1 = fopen("hw11.txt", "w");


	//step1 : Sequential read
	char buffer1[10000];
	gettimeofday(&start, NULL);

	for(i = 0; i < 51200; i++) {
		fread(buffer1, sizeof(char), 4096, f1);
	}

	gettimeofday(&end, NULL);
	diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	printf("the difference of sequential read is %ld(us)\n", diff);

	//step2 : Sequential write
	char buffer2[10000];
	gettimeofday(&start, NULL);
	
	for(i = 0; i < 51200; i++) {
		fwrite(buffer2, sizeof(char), 8192, f1);
		fsync(fileno(f1));
	}

	gettimeofday(&end, NULL);
	diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	printf("the difference of sequential write is %ld(us)\n", diff);

	//step3 : Random read 
	int x3;
	char buffer3[10000];
	//srand(time(NULL));
	gettimeofday(&start, NULL);
	
	for(i = 0; i < 50000; i++) {
		srand(time(NULL));
		x3 = rand() % (51199 - 0 + 1) + 0;
		x3 = x3 * 4 * 1024;
		fseek(f1, x3, SEEK_SET);
		fread(buffer3, sizeof(char), 4096, f1);
	}

	gettimeofday(&end, NULL);
	diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	printf("the difference of random read is %ld(us)\n", diff);	

	//step4 : Random write_1
	int x4;
	char buffer4[10000];

	gettimeofday(&start, NULL);
	
	for(i = 0; i < 50000; i++) {
		srand(time(NULL));
		x4 = rand() % (51199 - 0 + 1) + 0;
		x4 = x4 * 4 * 1024;
		fseek(f1, x4, SEEK_SET);
		fwrite(buffer4, sizeof(char), 8192, f1);
	}

	gettimeofday(&end, NULL);
	diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	printf("the difference of random write_1 is %ld(us)\n", diff);

	//step5 : Random write_2
	int x5;
	char buffer5[10000];
	//srand(time(NULL));
	gettimeofday(&start, NULL);
	
	for(i = 0; i < 50000; i++) {
		srand(time(NULL));
		x5 = rand() % (51199 - 0 + 1) + 0;
		x5 = x5 * 4 * 1024;
		fseek(f1, x5, SEEK_SET);
		fwrite(buffer5, sizeof(char), 8192, f1);
		fsync(fileno(f1));
	}

	gettimeofday(&end, NULL);
	diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	printf("the difference of random write_2 is %ld(us)\n", diff);

	fclose(f1);

	return 0;
}













