# sched_deadline
Minimal example of using SCHED_DEADLINE for realtime scheduling of C programs in Linux


## What is this?
Since version 3.14, the Linux kernel supports a new deadline scheduler, but it is not easy to use.
This repo presents a simple way to use the `sched_getattr` and `sched_setattr` syscalls.
See [this](https://stackoverflow.com/questions/50082317/is-sched-deadline-officially-supported-in-ubuntu-16-04) SO issue for more details.

## How to use
Just include `sd_hdsr.h` into your own C program and use `sched_getattr` and `sched_setattr` as described in the [manpages](https://man7.org/linux/man-pages/man2/sched_setattr.2.html).

## Compiling test example

Compile with
```Shell
gcc sd_hdr.h main.c -lpthread -lm -o a.out
sudo ./a.out
```

## Caveats
1. If you are working with periods smaller than 1 millisecond, you need to enable the high resolution tick for the scheduler.

```Shell
sudo su
cd /sys/kernel/debug
echo HRTICK > sched_features
```

This needs to be done every time the system boots, so write a script to do that.

2. To use `SHCED_DEADLINE` the user application needs to have superuser permissions. If you do not use `sudo`, the application will run as fast as possible.
3. As explained in the references below, the kernel does not allow the application to take up more than 95% od runtime every second. Basically, `sched_runtime/sched_deadline <= 0.95`. This is to prevent the system from locking up if the user program goes into an infinite loop because of a bug. If you want to use more than 95% CPU time, you can disable this limitation by

```Shell
sudo su
cd /proc/sys/kernel
echo -1 > sched_rt_runtime_us
```
Before doing this, make sure your realtime application is bug free or else your system could become unstable and even crash.


## Some nice references

- [Using SCHED_DEADLINE](https://youtu.be/TDR-rgWopgM)
- [Juri Lelli's talk](https://youtu.be/AmyfSjRMcIY)
- [Realtime Linux checklist](https://youtu.be/NrjXEaTSyrw)
- [Kernel documentation](https://docs.kernel.org/scheduler/sched-deadline.html)
