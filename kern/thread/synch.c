/*
 * Synchronization primitives.
 * See synch.h for specifications of the functions.
 */

#include <types.h>
#include <lib.h>
#include <synch.h>
#include <thread.h>
#include <curthread.h>
#include <machine/spl.h>

////////////////////////////////////////////////////////////
//
// Semaphore.

struct semaphore *
sem_create(const char *namearg, int initial_count)
{
	struct semaphore *sem;

	assert(initial_count >= 0);

	sem = kmalloc(sizeof(struct semaphore));
	if (sem == NULL) {
		return NULL;
	}

	sem->name = kstrdup(namearg);
	if (sem->name == NULL) {
		kfree(sem);
		return NULL;
	}

	sem->count = initial_count;
	return sem;
}

void
sem_destroy(struct semaphore *sem)
{
	int spl;
	assert(sem != NULL);

	spl = splhigh();
	assert(thread_hassleepers(sem)==0);
	splx(spl);

	/*
	 * Note: while someone could theoretically start sleeping on
	 * the semaphore after the above test but before we free it,
	 * if they're going to do that, they can just as easily wait
	 * a bit and start sleeping on the semaphore after it's been
	 * freed. Consequently, there's not a whole lot of point in 
	 * including the kfrees in the splhigh block, so we don't.
	 */

	kfree(sem->name);
	kfree(sem);
}

void 
P(struct semaphore *sem)
{
	int spl;
	assert(sem != NULL);

	/*
	 * May not block in an interrupt handler.
	 *
	 * For robustness, always check, even if we can actually
	 * complete the P without blocking.
	 */
	assert(in_interrupt==0);

	spl = splhigh();
	while (sem->count==0) {
		thread_sleep(sem);
	}
	assert(sem->count>0);
	sem->count--;
	splx(spl);
}

void
V(struct semaphore *sem)
{
	int spl;
	assert(sem != NULL);
	spl = splhigh();
	sem->count++;
	assert(sem->count>0);
	thread_wakeup(sem);
	splx(spl);
}

////////////////////////////////////////////////////////////
//
// Lock.

struct lock *
lock_create(const char *name)
{
	struct lock *lock;

	lock = kmalloc(sizeof(struct lock));
	if (lock == NULL) {
		return NULL;
	}

	lock->name = kstrdup(name);
	if (lock->name == NULL) {
		kfree(lock);
		return NULL;
	}

	lock->owner_thread_id = NULL;

	// add stuff here as needed
	assert(lock->owner_thread_id == NULL); // make sure that no thread is holding the lock.
	
	return lock;
}

void
lock_destroy(struct lock *lock)
{
	assert(lock != NULL);

	// add stuff here as needed
	assert(lock->owner_thread_id == NULL); // make sure that no thread is holding the lock.
	
	kfree(lock->name);
	kfree(lock);
}

/* lock_acquire pseudocode --
 * check if the lock has a thread owner, if so, sleep and check again.
 * else, set the lock thread owner to the current thread name
 * */
void
lock_acquire(struct lock *lock)
{
	(void)lock;  // suppress warning until code gets written
	// Write this

	// okay - -
	int spl;

	assert(in_interrupt == 0);

	assert(lock != NULL);

	spl = splhigh();

	// while the lock has a thread owner
	while (lock->owner_thread_id != NULL) {
		thread_sleep(lock);
	}

	assert(lock->owner_thread_id == NULL);
	lock->owner_thread_id = curthread->t_name;
	splx(spl);

}

/* lock_release pseudocode --
 * check if the lock's thread owner is equal to the current thread id, if not, return.
 * else set the lock's thread owner to null.
 * */
void
lock_release(struct lock *lock)
{

	// Write this
	(void)lock;  // suppress warning until code gets written

	// you got it, bud - -
	int spl;
	assert(in_interrupt == 0);
	assert(lock != NULL);

	spl = splhigh();
	if (strcmp(lock->owner_thread_id, curthread->t_name) != 0) panic("%s is trying to release a lock when it is not the owner.\n", curthread->t_name);

	lock->owner_thread_id = NULL;

	thread_wakeup(lock);
	splx(spl);

}

/* do_i_hold pseudocode --
 * if lock has no thread holding it, return 0
 * return 1 if current thread has the same id as the thread
 * holding the lock 'lock'.
 * else, return 0
 * */
int
lock_do_i_hold(struct lock *lock)
{
	// Write this
	(void)lock;  // suppress warning until code gets written

	// k

//	int spl;
	assert(in_interrupt == 0);
	assert(lock != NULL);

//	spl = splhigh();

	// should the check below be an assert instead?
	if (lock->owner_thread_id == NULL) return 0;

//	splx(spl);

	return !strcmp(lock->owner_thread_id, curthread->t_name);

	return 1;

}

////////////////////////////////////////////////////////////
//
// CV


struct cv *
cv_create(const char *name)
{
	struct cv *cv;

	cv = kmalloc(sizeof(struct cv));
	if (cv == NULL) {
		return NULL;
	}

	cv->name = kstrdup(name);
	if (cv->name==NULL) {
		kfree(cv);
		return NULL;
	}
	
	// add stuff here as needed
	
	return cv;
}

void
cv_destroy(struct cv *cv)
{
	assert(cv != NULL);

	// add stuff here as needed
	
	kfree(cv->name);
	kfree(cv);
}

void
cv_wait(struct cv *cv, struct lock *lock)
{
	// Write this
	(void)cv;    // suppress warning until code gets written
	(void)lock;  // suppress warning until code gets written
/*
	int spl;

	assert(in_interrupt == 0);
	assert(lock != NULL);
	assert(!strcmp(lock->owner_thread_id, curthread->t_name));

	spl = splhigh();

	lock_release(lock);

	thread_sleep(cv);

	lock_acquire(lock);

	slpx(spl);
*/
}

void
cv_signal(struct cv *cv, struct lock *lock)
{
	// Write this
	(void)cv;    // suppress warning until code gets written
	(void)lock;  // suppress warning until code gets written
/*
	int spl;

	assert(in_interrupt == 0);
	assert(lock != NULL);
	assert(!strcmp(lock->owner_thread_id, curthread->t_name));

	spl = splhigh();

	thread_wake_only_one(cv);

	splx(spl);
*/
}

void
cv_broadcast(struct cv *cv, struct lock *lock)
{
	// Write this
	(void)cv;    // suppress warning until code gets written
	(void)lock;  // suppress warning until code gets written
}
