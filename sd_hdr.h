#ifndef __SD_HDR__
#define __SD_HDR__

#include <sys/syscall.h>
#include <pthread.h>
#include <linux/sched.h>
#include <unistd.h>

#define gettid() syscall(__NR_gettid)

#define SCHED_DEADLINE 6

//Tested, works
#ifdef __x86_64__

#ifndef __NR_sched_setattr
#define __NR_sched_setattr 314
#endif

#ifndef __NR_sched_getattr
#define __NR_sched_getattr 315
#endif

#endif

//These values were not correct for
//NVIDIA Jetson boards, but maybe they work for other arm boards?
//(correct values were defined in sched.h)
//Tested on raspberry pi

#ifdef __arm__

#ifndef __NR_sched_setattr
#define __NR_sched_setattr 380
#endif

#ifndef __NR_sched_getattr
#define __NR_sched_getattr 381
#endif

#endif


struct sched_attr {
	__u32 size;
	__u32 sched_policy;
	__u64 sched_flags;

	__s32 sched_nice;

	__u32 sched_priority;

	__u64 sched_runtime;
	__u64 sched_deadline;
	__u64 sched_period;
};

int sched_setattr(pid_t pid,
	const struct sched_attr *attr,
	unsigned int flags)
	{
		return syscall(__NR_sched_setattr, pid, attr, flags);
	}

int sched_getattr(pid_t pid,
	const struct sched_attr *attr,
	unsigned int size,
	unsigned int flags)
	{
		return syscall(__NR_sched_getattr, pid, attr, size, flags);
	}


#endif
