//#define _GNU_SOURCE
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "sd_hdr.h"

int cycle_primes(int limit)
{
	int n;
	int pcount=1;

	for (n=3; n<=limit; n++)
	{
		int q= 1 + (int)sqrt(n);

		for (int k=2; k<=q; k++)
		{
			if (n%k==0)
			{
				break;
			}
			
			if(k==q)
			{
				pcount++;
			}

		}

	}
	return pcount;
}

int main(int argc, char* argv[])
{
	struct sched_attr sat;
	
	int rc = sched_getattr(gettid(), &sat, sizeof(sat), 0);
	
	if (rc != 0)
	{
		perror("sched_getattr");
	}

	sat.sched_policy=SCHED_DEADLINE;
	
	//runtime and deadline are in nanoseconds
	sat.sched_runtime=950*1000*1000;
	sat.sched_deadline=1000*1000*1000;

	rc = sched_setattr(gettid(), &sat, 0);

	if (rc != 0)
	{
		perror("sched_setattr");
	}

	for (int limit=500; limit<=20000; limit+=500)
	{

	struct timespec start, end;
	timespec_get(&start, TIME_UTC);
	int pc=cycle_primes(limit);
	timespec_get(&end, TIME_UTC);
	long long unsigned elapsed= (end.tv_sec - start.tv_sec)*1000000 + (end.tv_nsec - start.tv_nsec)/1000;
	
	printf("Total number of primes upto %d = %d\n", limit, pc);
	sched_yield(); 
	//tells the scheduler we are done for the current period
	//process gives up CPU, and woken up at the next period 

	//printf("Micros elapsed= %llu\n", elapsed);
	//uncomment to check how much time function takes
	}
	return 0;
}