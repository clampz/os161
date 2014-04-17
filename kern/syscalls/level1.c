/*  file: level1.c
 *  date: 4/15/14
 *  author: david weinman
 *
 *  * * * *
 *  description: level1.c
 *  is a collection of system
 *  calls which represent the
 *  'first level' of system
 *   calls i defined in os161
 * */

/* sys__exit is the program
 * used to exit a sys call
 *
 * this was part 2 in project 02
 * */
void sys__exit(void) {

	thread_exit();
	panic("[SYSEXIT] thread_exit failed!");

}

/* sys_printint is a simple
 * sys call that only prints
 * a given int
 *
 * this was part 3 in project 02
 * */
int sys_printint(int x) {

	kprintf("[PRINTINT] the given int is: %d\n", x);

}

/* sys_printstring is a simple
 * sys call that only prints
 * a given string.
 *
 * this was part 4 in project 02
 * */
int sys_printstring(char * str, int len) {

	kprintf("[PRINTSTR] the given str is: %s (its size is: %d)\n", str, len);

}


