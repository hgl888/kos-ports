/*
 * kosh.c - console shell for kallistios (A Rough version)
 *
 * (C) 2000 Jordan DeLong
 */

#include <stdio.h>
#include <assert.h>
#include <pthread.h>
#include "kosh.h"
#include "chdir.h"
#include "builtin.h"

/* global exit flag:  if someone sets this we quit */
#define KE_YES		1	// Requesting exit
#define KE_NO		0	// Run mode
#define KE_QUITTING	-1	// Thread has returned
#define KE_JOINED	-2	// Not running
volatile int kosh_exit = KE_JOINED;

/* Our exit semaphore - signaled when the thread exits */
static pthread_t thd;

static void * kosh_thread(void *p) {
	conio_printf("  **** KOSH, The KallistiOS Shell ****\n");
	kosh_chdir("/");
	while (kosh_exit == KE_NO)
		input_oneloop();
	conio_printf("Kosh is done\n");
	kosh_exit = KE_QUITTING;

	return NULL;
}

void kosh_join() {
	assert( kosh_exit != KE_JOINED );
	pthread_join(thd, NULL);
	kosh_exit = KE_JOINED;
}

int kosh_init() {
	if (kosh_exit != KE_JOINED)
		return -1;

	kosh_exit = KE_NO;
	kosh_builtins_init();
	pthread_create(&thd, NULL, kosh_thread, NULL);
	return 0;
}

void kosh_shutdown() {
	if (kosh_exit != KE_JOINED) {
		kosh_exit = KE_YES;
		kosh_join();
	}
	kosh_builtins_shutdown();
}
