/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
#include <syscall.h>
#include <setjmp.h>

/*
 * Author: Arun Dharankar <ADharankar@ATTBI.Com>
 *
 * A very simple thread/schedular model:
 *   - only one master thread, and no parent child relation maintained
 *   - parent thread cannot be stopped or deleted
 *   - no permissions or credentials
 *   - no elaborate safety checks
 *   - cooperative multi threading
 *   - Simple round-robin scheduleing with no priorities
 *   - no metering/statistics collection
 *
 * Basic idea of implementing this is to allow more than one tests to
 * execute "simultaneously".
 *
 * This may be modified such thread_yield may be called in syscalls, and
 * timer interrupts.
 */


#define MAX_THREADS 8

#define CTX_SIZE 512
#define STK_SIZE 8*1024

#define STATE_EMPTY 0
#define STATE_RUNNABLE 1
#define STATE_STOPPED 2
#define STATE_TERMINATED 2

#define MASTER_THREAD 0

#define RC_FAILURE	(-1)
#define	RC_SUCCESS	(0)

struct lthread {
	int state;
	int retval;
	char stack[STK_SIZE];
	uchar context[CTX_SIZE];
	int (*func) (void *);
	void *arg;
};
static volatile struct lthread lthreads[MAX_THREADS];
static volatile int current_tid = MASTER_THREAD;


static uchar dbg = 0;

#define DEBUG(fmt, args...)	 {												\
		if(dbg != 0) {														\
			mon_printf("[%s %d %s]: ", __FILE__, __LINE__, __FUNCTION__);	\
			mon_printf(fmt, ##args);										\
			mon_printf("\n");												\
		}																	\
	}

static int testthread (void *);
static void sched_init (void);
static int thread_create (int (*func) (void *), void *arg);
static int thread_start (int id);
static void thread_yield (void);
static int thread_delete (int id);
static int thread_join (int *ret);
#if 0 /* not used yet */
static int thread_stop (int id);
#endif /* not used yet */

/* An example of schedular test */

#define NUMTHREADS 7
int sched (bd_t *bd, int ac, char *av[])
{
	int i, j;
	int tid[NUMTHREADS];
	int names[NUMTHREADS];

	sched_init ();

	for (i = 0; i < NUMTHREADS; i++) {
		names[i] = i;
		j = thread_create (testthread, (void *) &names[i]);
		if (j == RC_FAILURE)
			mon_printf ("schedtest: Failed to create thread %d\n",
			i);
		if (j > 0) {
			mon_printf ("schedtest: Created thread with id %d, name %d\n",
				j, i);
			tid[i] = j;
		}
	}
	mon_printf ("schedtest: Threads created\n");

	mon_printf ("sched_test: function=0x%08x\n", testthread);
	for (i = 0; i < NUMTHREADS; i++) {
		mon_printf ("schedtest: Setting thread %d runnable\n", tid[i]);
		thread_start (tid[i]);
		thread_yield ();
	}
	mon_printf ("schedtest: Started %d threads\n", NUMTHREADS);

	while (1) {
		mon_printf ("schedtest: Waiting for threads to complete\n");
		if (mon_tstc () && mon_getc () == 0x3) {
			mon_printf ("schedtest: Aborting threads...\n");
			for (i = 0; i < NUMTHREADS; i++) {
				mon_printf ("schedtest: Deleting thread %d\n",
					tid[i]);
				thread_delete (tid[i]);
			}
			return RC_SUCCESS;
		}
		j = -1;
		i = thread_join (&j);
		if (i == RC_FAILURE) {
			mon_printf ("schedtest: No threads pending, "
				"exiting schedular test\n");
			return RC_SUCCESS;
		}
		mon_printf ("schedtest: thread is %d returned %d\n", i,
					j);
		thread_yield ();
	}

	return RC_SUCCESS;
}

static int testthread (void *name)
{
	int i;

	mon_printf ("testthread: Begin executing thread, myname %d, &i=0x%08x\n",
		 *(int *) name, &i);

	mon_printf ("Thread %02d, i=%d\n", *(int *) name);

	for (i = 0; i < 0xffff * (*(int *) name + 1); i++) {
		if (mon_tstc () && mon_getc () == 0x3) {
			mon_printf ("testthread: myname %d terminating.\n",
				*(int *) name);
			return *(int *) name + 1;
		}

		if (i % 100 == 0)
			thread_yield ();
	}

	mon_printf ("testthread: returning %d, i=0x%x\n",
		*(int *) name + 1, i);

	return *(int *) name + 1;
}


static void sched_init (void)
{
	int i;

	for (i = MASTER_THREAD + 1; i < MAX_THREADS; i++)
		lthreads[i].state = STATE_EMPTY;

	current_tid = MASTER_THREAD;
	lthreads[current_tid].state = STATE_RUNNABLE;
	DEBUG ("sched_init: master context = 0x%08x",
		lthreads[current_tid].context);
	return;
}

static void thread_yield (void)
{
	static int i;

	DEBUG ("thread_yield: current tid=%d", current_tid);

#define SWITCH(new) 							\
	if(lthreads[new].state == STATE_RUNNABLE) {			\
		DEBUG("thread_yield: %d match, ctx=0x%08x",		\
			new, lthreads[current_tid].context); 		\
		if(setjmp(lthreads[current_tid].context) == 0) {	\
			current_tid = new;				\
			DEBUG("thread_yield: tid %d returns 0",		\
				new); 					\
			longjmp(lthreads[new].context, 1);		\
		} else {						\
			DEBUG("thread_yield: tid %d returns 1",		\
				new); 					\
			return;						\
		}							\
	}

	for (i = current_tid + 1; i < MAX_THREADS; i++) {
		SWITCH (i);
	}

	if (current_tid != 0) {
		for (i = 0; i <= current_tid; i++) {
			SWITCH (i);
		}
	}

	DEBUG ("thread_yield: returning from thread_yield");
	return;
}

static int thread_create (int (*func) (void *), void *arg)
{
	int i;

	for (i = MASTER_THREAD + 1; i < MAX_THREADS; i++) {
		if (lthreads[i].state == STATE_EMPTY) {
			lthreads[i].state = STATE_STOPPED;
			lthreads[i].func = func;
			lthreads[i].arg = arg;
			DEBUG ("thread_create: returns new tid %d", i);
			return i;
		}
	}

	DEBUG ("thread_create: returns failure");
	return RC_FAILURE;
}

static int thread_delete (int id)
{
	if (id <= MASTER_THREAD || id > MAX_THREADS)
		return RC_FAILURE;

	if (current_tid == id)
		return RC_FAILURE;

	lthreads[id].state = STATE_EMPTY;
	return RC_SUCCESS;
}

static void thread_launcher (void)
{
	DEBUG ("thread_launcher: invoking func=0x%08x",
		   lthreads[current_tid].func);

	lthreads[current_tid].retval =
			lthreads[current_tid].func(lthreads[current_tid].arg);

	DEBUG ("thread_launcher: tid %d terminated", current_tid);

	lthreads[current_tid].state = STATE_TERMINATED;
	thread_yield ();
	mon_printf ("thread_launcher: should NEVER get here!\n");

	return;
}

static int thread_start (int id)
{
	DEBUG ("thread_start: id=%d", id);
	if (id <= MASTER_THREAD || id > MAX_THREADS) {
		return RC_FAILURE;
	}

	if (lthreads[id].state != STATE_STOPPED)
		return RC_FAILURE;

	if (setjmp (lthreads[current_tid].context) == 0) {
		lthreads[id].state = STATE_RUNNABLE;
		current_tid = id;
		DEBUG ("thread_start: to be stack=0%08x", lthreads[id].stack);
		setctxsp (&lthreads[id].stack[STK_SIZE]);
		thread_launcher ();
	}

	DEBUG ("thread_start: Thread id=%d started, parent returns", id);

	return RC_SUCCESS;
}

#if 0	/* not used so far */
static int thread_stop (int id)
{
	if (id <= MASTER_THREAD || id >= MAX_THREADS)
		return RC_FAILURE;

	if (current_tid == id)
		return RC_FAILURE;

	lthreads[id].state = STATE_STOPPED;
	return RC_SUCCESS;
}
#endif /* not used so far */

static int thread_join (int *ret)
{
	int i, j = 0;

	DEBUG ("thread_join: *ret = %d", *ret);

	if (!(*ret == -1 || *ret > MASTER_THREAD || *ret < MAX_THREADS)) {
		DEBUG ("thread_join: invalid tid %d", *ret);
		return RC_FAILURE;
	}

	if (*ret == -1) {
		DEBUG ("Checking for tid = -1");
		while (1) {
			/* DEBUG("thread_join: start while-loopn"); */
			j = 0;
			for (i = MASTER_THREAD + 1; i < MAX_THREADS; i++) {
				if (lthreads[i].state == STATE_TERMINATED) {
					*ret = lthreads[i].retval;
					lthreads[i].state = STATE_EMPTY;
					/* DEBUG("thread_join: returning retval %d of tid %d",
						ret, i); */
					return RC_SUCCESS;
				}

				if (lthreads[i].state != STATE_EMPTY) {
					DEBUG ("thread_join: %d used slots tid %d state=%d",
						j, i, lthreads[i].state);
					j++;
				}
			}
			if (j == 0) {
				DEBUG ("thread_join: all slots empty!");
				return RC_FAILURE;
			}
			/*  DEBUG("thread_join: yielding"); */
			thread_yield ();
			/*  DEBUG("thread_join: back from yield"); */
		}
	}

	if (lthreads[*ret].state == STATE_TERMINATED) {
		i = *ret;
		*ret = lthreads[*ret].retval;
		lthreads[*ret].state = STATE_EMPTY;
		DEBUG ("thread_join: returing %d for tid %d", *ret, i);
		return RC_SUCCESS;
	}

	DEBUG ("thread_join: thread %d is not terminated!", *ret);
	return RC_FAILURE;
}
