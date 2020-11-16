#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main() {
	
	int randfile = open("/dev/random", O_RDONLY);
	if (randfile == -1) {
		printf ("errno: %d\terror: %s\n", errno, strerror (errno));
		return 0;
	}
	
	printf ("Generating random numbers\n");
	int random_ints[10];
	int i;
	for (i = 0; i < 10; i++) {
		int rand = read (randfile, &random_ints[i], sizeof(random_ints[i]));	
		if (rand == -1) {
			printf ("errno: %d\terror: %s\n", errno, strerror (errno));
			return 0;
		}
		printf ("Random #%d: %d\n", i, random_ints[i]);
	}
	
	printf("\nWriting numbers to file\n");
	int randout = open ("random.out", O_CREAT | O_WRONLY, 0777);
	if (randout == -1) {
		printf ("errno: %d\terror: %s\n", errno, strerror (errno));
		return 0;
	}
	
	int rand_write = write (randout, random_ints, sizeof(random_ints));
	if (rand_write == -1) {
		printf ("errno: %d\terror: %s\n", errno, strerror (errno));
		return 0;
	}
	
	printf ("\nReading numbers from file\n");
	int randfile2 = open ("random.out", O_RDONLY);
	if (randfile2 == -1) {
		printf ("errno: %d\terror: %s\n", errno, strerror (errno));
		return 0;
	}
	
	printf ("\nVerification that written values were the same\n");
	int random_ints2 [10];
	for (i = 0; i < 10; i++) {
		int rand = read (randfile, &random_ints2[i], sizeof(random_ints2[i]));	
		if (rand == -1) {
			printf ("errno: %d\terror: %s\n", errno, strerror (errno));
			return 0;
		}
		printf ("Random #%d: %d\n", i, random_ints[i]);
	}
	
	return 0;
}
