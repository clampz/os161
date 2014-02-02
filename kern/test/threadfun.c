/*
 *
 *
*/

#include <types.h>
#include <lib.h>
#include <test.h>
#include <thread.h>
#include <synch.h>

static volatile int sharedThreadCount;
static struct semaphore *s;
static struct semaphore *d;

/* increment for exercise 5
 * enforces mutual exclusion with semaphores
 * */
void semIncrementThread(void *junk, unsigned long num) {

	(void) junk;

	P(s);

	sharedThreadCount += num;

	putch('a');

	V(d);

}

/* this is the safe thread test incrementor wrapper function
 *
 * this function was for project 1 exercise 5
 * */
int safethreadcounter(int nargs, char **args) {

	int result, i, maxthreads, nincrements;
	(void) nargs;

	sharedThreadCount = 0;
	maxthreads = atoi(args[1]);
	nincrements = atoi(args[2]);
	s = sem_create("thread_count_test_sem", 0);
	d = sem_create("thread_count_test_done_sem", 0);

	kprintf("%s", "\nBegin threadfun test number 3..\n\n");

	for (i = 0; i < maxthreads; i++) {

		result = thread_fork("threadfun3_child", NULL, nincrements, semIncrementThread, NULL);
		if (result) panic("threadfun: thread_fork failed: %s\n\n", strerror(result));

	}

	for (i = 0; i < maxthreads; i++) {

		V(s);
		P(d);

	}

	sem_destroy(s);
	sem_destroy(d);

	kprintf("\nThe final value of sharedThreadCount is: %d.\n", sharedThreadCount);

	kprintf("%s", "\n\nEnd threadfun test n3..\n\n");

	return 0;

}

/* this is the incrementor function for exercise 4
 * does not use proper mutual exclusion
 * */
void incrementThread(void *junk, unsigned long num) {

	(void) junk;

	sharedThreadCount += num;

	putch('a');

}

/* this is the unsafe thread test incrementor wrapper function.
 *
 * project 1, exercise 4
 * */
int threadfuntwo(int nargs, char **args) {

	int result, i, maxthreads, nincrements;
	(void) nargs;

	sharedThreadCount = 0;
	maxthreads = atoi(args[1]);
	nincrements = atoi(args[2]);

	kprintf("%s", "\nBegin threadfun test number 2..\n\n");

	for (i = 0; i < maxthreads; i++) {

		result = thread_fork("threadfun2_child", NULL, nincrements, incrementThread, NULL);
		if (result) panic("threadfun: thread_fork failed: %s\n\n", strerror(result));

	}

	kprintf("\nThe final value of sharedThreadCount is: %d.\n", sharedThreadCount);

	kprintf("%s", "\n\nEnd threadfun test n2..\n\n");

	return 0;

}


void printThread(void *junk, unsigned long num) {

	char numStr[] = {'0', ((char) '1' + num), NULL};
	(void) junk;

	kprintf("%s\n", numStr);

}

int threadfun(int nargs, char **args) {

	int result, i;
	(void) nargs;
	(void) args;

	kprintf("%s", "\nBegin threadfun test..\n\n");

	for (i = 0; i < ((int) *args[1] - 48); i++) {

		result = thread_fork("threadfun_child", NULL, i, printThread, NULL);
		if (result) panic("threadfun: thread_fork failed: %s\n\n", strerror(result));

	}

	kprintf("%s", "\n\nEnd threadfun test..\n\n");

	return 0;

}



