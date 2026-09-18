#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <fcntl.h>

#define BUFSIZE 30

void memprint(char *, char *, int);

void part1();
void part3(char *);
void part4();

int main(int argc, char *argv[]) {
	part1();

	/* Part 2 (below this comment) */
	printf("\n===== Part 2 =====\n");
	printf("-- Questions 8 and 9\n");
	printf("%d\n", argc);
	for (int i = 0; i < argc; i++) {
		printf("%s\n", argv[i]);
	}

	printf("-- Questions 10 and 11\n");
	if (argc != 2) {
		fprintf(stderr, "Exactly one command-line option is required: filename\n");
		exit(6);
	}

	part3(argv[1]);
	part4();
}

void memprint(char *s, char *fmt, int len) {
	// iterate through each byte/character of s, and print each out with
	// the format specified with fmt
	int i;
	char fmt_with_space[8];

	sprintf(fmt_with_space, "%s ", fmt);
	for (i = 0; i < len; i++) {
		printf(fmt_with_space, s[i]);
	}
	printf("\n");
}

void part1() {
	printf("\n===== Part 1 =====\n");

	// Note: STDOUT_FILENO is defined in /usr/include/unistd.h:
	//
	// #define	STDOUT_FILENO	1

	char s1a[] = { 104, 101, 108, 108, 111, 10 };
	write(STDOUT_FILENO, s1a, 6);

	char s1b[] = { 0x68, 0x65, 0x6c, 0x6c, 0x6f, 0x0a };
	write(STDOUT_FILENO, s1b, 6);

	char s1c[] = { 'h', 'e', 'l', 'l', 'o', '\n' };
	write(STDOUT_FILENO, s1c, 6);

	char s2[] = { 0xe5, 0x8f, 0xb0, 0xe7, 0x81, 0xa3, 0x0a };
	write(STDOUT_FILENO, s2, 7);

	char s3[] = { 0xf0, 0x9f, 0x98, 0x82, 0x0a };
	write(STDOUT_FILENO, s3, 5);

	int s1a_len = sizeof(s1a);

	printf("-- Questions 1 through 4\n");
	// I did these afterwards, initially I used man to look through the ascii tables, oops
	memprint(s1a, "%02x", s1a_len);
	memprint(s1a, "%d", s1a_len);
	memprint(s1a, "%c", s1a_len);

	printf("-- Questions 5 through 7\n");
	// Same with these haha
	char q5[] = { 'B' };
	memprint(q5, "%02x", 1);

	char q6[] = { '$' };
	memprint(q6, "%d", 1);

	char q7[] = { 7 };
	memprint(q7, "%c", 1);
}

void part3(char *filename) {
	printf("\n===== Part 3 =====\n");

	printf("-- Question 12\n");
	printf("%d\n", fileno(stdin));
	printf("%d\n", fileno(stdout));
	printf("%d\n", fileno(stderr));

	printf("-- Question 13\n");
	char buf[BUFSIZE];
	memset(buf, 'z', BUFSIZE);
	buf[24] = '\0';
	memprint(buf, "%02x", BUFSIZE);

	printf("-- Question 14\n");
	printf("%s", buf);
	printf("\n");
	write(fileno(stdout), buf, BUFSIZE);
	write(fileno(stdout), "\n", 1);

	fprintf(stderr, "-- Questions 15 through 18\n");
	fprintf(stderr, "%s", buf);
	fprintf(stderr, "\n");
	write(fileno(stderr), buf, BUFSIZE);
	write(fileno(stderr), "\n", 1);

	printf("-- Question 19\n");
	int fd1, fd2;
	fd1 = open(filename, O_RDONLY);
	fd2 = fd1;
	printf("%d\n", fd1);
	printf("%d\n", fd2);


	printf("-- Questions 20 and 21\n");
	size_t numread = 0;
	size_t totread = 0;
	numread = read(fd1, buf, 4);
	totread += numread;
	printf("%d\n", (int)numread);
	printf("%d\n", (int)totread);
	memprint(buf, "%02x", BUFSIZE);

	printf("-- Questions 22 through 25\n");
	numread = read(fd2, buf + totread, 4);
	totread += numread;
	printf("%d\n", (int)numread);
	printf("%d\n", (int)totread);
	memprint(buf, "%02x", BUFSIZE);

	printf("-- Questions 26 through 31\n");
	numread = read(fd2, buf + totread, BUFSIZE - totread);
	totread += numread;
	printf("%d\n", (int)numread);
	printf("%d\n", (int)totread);
	memprint(buf, "%02x", BUFSIZE);

	printf("-- Questions 32 and 33\n");
	numread = read(fd2, buf + totread, BUFSIZE - totread);
	printf("%d\n", (int)numread);

	printf("-- Question 34\n");
	printf("%s\n", buf);

	printf("-- Question 35\n");
	int ret = 0;
	buf[totread] = '\0';
	printf("%s\n", buf);

	printf("-- Question 36\n");
	ret = close(fd1);
	printf("%d\n", ret);

	printf("-- Question 37\n");
	ret = close(fd2);
	printf("%d\n", ret);

	printf("-- Question 38\n");
	fprintf(stdout, "abc");
	fprintf(stderr, "def");
	fprintf(stdout, "ghi\n");

	printf("-- Questions 39 and 40\n");
	write(fileno(stdout), "abc", 3);
	write(fileno(stderr), "def", 3);
	write(fileno(stdout), "ghi\n", 4);

	printf("-- Question 41\n");
	fprintf(stdout, "abc");
	fflush(stdout);
	fprintf(stderr, "def");
	fprintf(stdout, "ghi\n");
}

void part4() {
	printf("\n===== Part 4 =====\n");

	printf("-- Questions 42 and 43\n");
	char *s1 = getenv("CS324_VAR");
	if (s1 != NULL) {
		printf("CS324_VAR is %s\n", s1);
	} else {
		printf("CS324_VAR not found\n");
	}
}
