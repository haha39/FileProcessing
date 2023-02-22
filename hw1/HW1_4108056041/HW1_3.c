#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>

#include <errno.h>

int main() {
	struct timeval start;
	struct timeval end;
	unsigned long diff;
	int i, j;
	//step0 : create a 200MB file
	FILE *f;
	f = fopen("hw11.txt", "w");

	for(i = 0; i<209715200; i++) {
		fprintf(f, "a");
	}


	int f1;
	char *map_f1;

	f1 = open("hw11.txt", O_RDWR);
	if(f1 == -1) {
		printf("open hello.txt fail\n");
		return 1;
	}



	//get the size of file
	struct stat st;
	stat("hw11.txt", &st);
	long int filesize = st.st_size;
	map_f1 = mmap(NULL, filesize, PROT_READ, MAP_SHARED, f1, 0);
	if(map_f1 == MAP_FAILED) {
		printf("mmap1 error : %s\n", strerror(errno));
		return 0;
	}






	//step1 : Sequential read
	char buffer1[10000];
	gettimeofday(&start, NULL);

	for(i = 0; i < 51200; i++) {
		memcpy(buffer1, map_f1, 4096);
		//read(f1, buffer1, 4096);
	}

	gettimeofday(&end, NULL);
	diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	printf("the difference of sequential read is %ld(us)\n", diff);

	//step2 : Sequential write
	char buffer2[10000];
	gettimeofday(&start, NULL);
	
	for(i = 0; i < 51200; i++) {
		//write(f1, buffer2, 8192);
		memcpy(map_f1, buffer2, 4096);
		fsync(f1);
	}

	gettimeofday(&end, NULL);
	diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	printf("the difference of sequential write is %ld(us)\n", diff);


	//step3 : Random read 
	int x3;
	char buffer3[10000];
	srand(time(NULL));
	gettimeofday(&start, NULL);
	
	for(i = 0; i < 50000; i++) {
		x3 = rand() % (51199 - 0 + 1) + 0;
		x3 = x3 * 4 * 1024;
		lseek(f1, x3, SEEK_SET);
		memcpy(buffer1, map_f1, 3072);
	}

	gettimeofday(&end, NULL);
	diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	printf("the difference of random read is %ld(us)\n", diff);	

	//step4 : Random write_1
	int x4;
	char buffer4[10000];
	srand(time(NULL));
	gettimeofday(&start, NULL);
	
	for(i = 0; i < 50000; i++) {
		x4 = rand() % (51199 - 0 + 1) + 0;
		x4 = x4 * 4 * 1024;
		lseek(f1, x4, SEEK_SET);
		memcpy(map_f1, buffer2, 4096);
	}

	gettimeofday(&end, NULL);
	diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	printf("the difference of random write_1 is %ld(us)\n", diff);

	//step5 : Random write_2
	int x5;
	char buffer5[10000];
	srand(time(NULL));
	gettimeofday(&start, NULL);
	
	for(i = 0; i < 50000; i++) {
		x5 = rand() % (51199 - 0 + 1) + 0;
		x5 = x5 * 4 * 1024;
		lseek(f1, x5, SEEK_SET);
		memcpy(map_f1, buffer2, 4096);
		fsync(f1);
	}

	gettimeofday(&end, NULL);
	diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	printf("the difference of random write_2 is %ld(us)\n", diff);

/*

	char buffer[10000];
	int f1;
	char *map_f1;

	f1 = open("hello.txt", O_RDWR);
	if(f1 == -1) {
		printf("open hello.txt fail\n");
		return 1;
	}
*/
	//get the size of file
	//struct stat st;
	//stat("hello.txt", &st);
	//long int filesize = st.st_size;
	//printf("file size is : %ld\n", filesize);


	//printf("map_f1 is : %ld\n", map_f1);
	//read from the map you can also use it like a array buffer[0] = map_f1[0]
	//memcpy(buffer, map_f1, 4);
	//you can change the offset by increasing its value
	//map_f1 += 4;
	//write to map
/*	memcpy(map_f1, buffer, 4);
	
	map_f1 -= 4;
	if(munmap(map_f1, filesize) == -1) {
		printf("munmap_f1 failed\n");
	}
	if(close(f1) == -1) {
		printf("close f1 error\n");
	}
	printf("end\n");
*/



	//close(f1);

	return 0;










}
























