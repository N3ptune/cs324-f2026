#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>

int main(int argc, char *argv[]) {
	int pid;
	FILE *fp;
	int pipefd[2];

	printf("Starting program; process has pid %d\n", getpid());

	fp = fopen("fork-output.txt", "w");
	fprintf(fp, "BEFORE FORK (%d)\n", fileno(fp));
	fflush(fp);
	
	pipe(pipefd);

	if ((pid = fork()) < 0) {
		fprintf(stderr, "Could not fork()");
		exit(1);
	}

	/* BEGIN SECTION A */

	printf("Section A;  pid %d\n", getpid());
	// sleep(5);

	/* END SECTION A */
	if (pid == 0) {
		/* BEGIN SECTION B */

		printf("Section B\n");
		// sleep(30);
		// sleep(30);
		// sleep(5);
		fprintf(fp, "SECTION B (%d)\n", fileno(fp));
		// printf("Section B done sleeping\n");

		close(pipefd[0]);
		char *msg = "hello from Section B\n";
		sleep(10);
		write(pipefd[1], msg, strlen(msg));
		sleep(10);
		close(pipefd[1]);

		char *newenviron[] = { NULL };

		printf("Program \"%s\" has pid %d. Sleeping.\n", argv[0], getpid());
		// sleep(30);

		if (argc <= 1) {
			printf("No program to exec.  Exiting...\n");
			exit(0);
		}

		printf("Running exec of \"%s\"\n", argv[1]);
		dup2(fileno(fp), STDOUT_FILENO);
		execve(argv[1], &argv[1], newenviron);
		printf("End of program \"%s\".\n", argv[0]);


		exit(0);

		/* END SECTION B */
	} else {
		/* BEGIN SECTION C */

		printf("Section C\n");
		// wait(NULL);
		// sleep(30);
		fprintf(fp, "SECTION C (%d)\n", fileno(fp));
		fclose(fp);
		// sleep(5);
		// printf("Section C done sleeping\n");

		close(pipefd[1]);
		char buf[1024];
		ssize_t n = read(pipefd[0], buf, sizeof(buf) - 1);
		buf[n] = '\0';
		printf("Received %zd bytes\n", n);
		printf("%s", buf);

		ssize_t n2 = read(pipefd[0], buf, sizeof(buf) - 1);
		printf("Received %zd bytes\n", n2);

		close(pipefd[0]);

		exit(0);

		/* END SECTION C */
	}
	/* BEGIN SECTION D */

	printf("Section D\n");
	// sleep(30);

	/* END SECTION D */
}

