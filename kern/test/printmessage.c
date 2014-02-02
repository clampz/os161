/*	file: printmessage.c 
 *	date: 01/23/14
 *	author: David Weinman
 *
 * 	simple test program to add a program
 * 	to the test menu, prints a message.
 *
 * */

#include <types.h>
#include <lib.h>
#include <test.h>
#include <thread.h>
#include <curthread.h>

/*
static
void
semtestthread(void *junk, unsigned long num)
{
	int i;
	(void)junk;

	
	 // Only one of these should print at a time.
	 
	P(testsem);
	kprintf("Thread %2lu: ", num);
	for (i=0; i<NSEMLOOPS; i++) {
		kprintf("%c", (int)num+64);
	}
	kprintf("\n");
	V(donesem);
}*/

/*

int
semtest(int nargs, char **args)
{
	int i, result;

	(void)nargs;
	(void)args;

	inititems();
	kprintf("Starting semaphore test...\n");
	kprintf("If this hangs, it's broken: ");
	P(testsem);
	P(testsem);
	kprintf("ok\n");

	for (i=0; i<NTHREADS; i++) {
		result = thread_fork("semtest", NULL, i, semtestthread, NULL);
		if (result) {
			panic("semtest: thread_fork failed: %s\n", 
			      strerror(result));
		}
	}

	for (i=0; i<NTHREADS; i++) {
		V(testsem);
		P(donesem);
	}

	// so we can run it again
	V(testsem);
	V(testsem);

	kprintf("Semaphore test done.\n");
	return 0;
}*/

void printmessage_thread_printTID(void *junk, unsigned long num) {

	(void) junk;
	(unsigned long) num;

	kprintf("\ncurrent thread thread_id: %s.\n\n", (char *) curthread->t_name);

	return;

}

int printmessage(int nargs, char **args) {

	int result;
	(void)nargs;
	(void)args;

	kprintf("%s", "Beginning message test..\n\n");

	kprintf("\ncurrent thread thread_id: %s.\n\n", (char *)  curthread->t_name);

	result = thread_fork("printmessage_child", NULL, NULL, printmessage_thread_printTID, NULL);
	if (result) {
		panic("printmessage: thread_fork failed: %s\n\n", strerror(result));
	}

	kprintf("%s", "David's message test complete..\n\n");

	return 0;

}

/* print out command line args
int printmessage(int nargs, char **args) {

	int i;
	(void)nargs;
	(void)args;

	kprintf("%s", "Beginning message test..\n\n");

	if (nargs < 2) kprintf("%s", "No arguments.\n\n");
	else {
		for (i = 1; i < (nargs - 1); i++) kprintf("arg #%d : %s, ", i , args[i]);
		kprintf("arg #%d : %s\n\n", nargs - 1, args[nargs - 1]);
	}
	kprintf("%s", "David's message test complete..\n\n");

	return 0;

}
*/



/*
#include <types.h>
#include <lib.h>
#include <synch.h>
#include <thread.h>
#include <test.h>
#include <clock.h>
*/



