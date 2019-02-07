#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <libspe2.h>
#include <pthread.h>

extern spe_program_handle_t hello_spu_handle;		//To use the hello_spu program handle pointing to embeded hello_spe.elf inside a ppu context

#define MAX_SPU_THREADS 	8		//Max # of spe to use (if availlable)


void *ppu_pthread_function(void *arg) {
	spe_context_ptr_t ctx;
	unsigned int entry = SPE_DEFAULT_ENTRY;
	
	ctx = *((spe_context_ptr_t *)arg);
	if (spe_context_run(ctx,&entry, 0, NULL, NULL, NULL) < 0) {
		perror ("Failed running context");
		exit (1);
	}
	pthread_exit(NULL);
}


int main()
{
	int i,spu_threads;
	spe_context_ptr_t ctxs[MAX_SPU_THREADS];
	pthread_t threads[MAX_SPU_THREADS];

	/* Determine the number of SPE threads to create 
	   On a PS3 this can go up to:	 6 on OtherOS
					 7 on OtherOS++
					 8 on OtherOS++ (with modified Syscon's EEPROM value located at 0x48C30 from 0x06 to 0x07)
	*/
	spu_threads = spe_cpu_info_get(SPE_COUNT_USABLE_SPES, -1);
	if (spu_threads > MAX_SPU_THREADS) 
		{
		printf("Using %i out of %i spu availaible as defined by MAX_SPU_THREADS constant\n\n", MAX_SPU_THREADS, spu_threads);
		spu_threads = MAX_SPU_THREADS;
		}

	/* Create several SPE-threads to execute 'hello_spu.elf' though the handle */
	for(i=0; i<spu_threads; i++) {
		/* Create context */
		if ((ctxs[i] = spe_context_create (0, NULL)) == NULL) {
			perror ("Failed creating context");
			exit (1);
			}
		/* Load program into context using the handle*/
		if (spe_program_load (ctxs[i],&hello_spu_handle)) {
			perror ("Failed loading program");
			exit (1);
			}
		/* Create thread for each SPE context */
		if (pthread_create (&threads[i], NULL,&ppu_pthread_function,&ctxs[i]))  {
			perror ("Failed creating thread");
			exit (1);
			}
		}	
	/* Wait for SPU-thread to complete execution. */
	for (i=0; i<spu_threads; i++) {
		if (pthread_join (threads[i], NULL)) {
			perror("Failed pthread_join");
			exit (1);
		}
	}

	printf("\nThe program has successfully executed.\n");

	return (0);
}
