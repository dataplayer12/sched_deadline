# sched_deadline
Minimal example of using SCHED_DEADLINE for realtime scheduling of C programs in Linux


# What is this?
Since version 3.14, the Linux kernel supports a new deadline scheduler, but it is not easy to use.
This repo presents a simple way to use the `sched_getattr` and `sched_setattr` syscalls.
See [this](https://stackoverflow.com/questions/50082317/is-sched-deadline-officially-supported-in-ubuntu-16-04) SO issue for more details.

# How to use
Just include `sd_hdsr.h` into your own C program and use `sched_getattr` and `sched_setattr` as described in the [manpages](https://man7.org/linux/man-pages/man2/sched_setattr.2.html).

# Compiling test example

Compile with
```Shell
gcc sd_hdr.h main.c -lpthread -lm -o a.out
```

# Caveat
If you are working with periods smaller than 1 millisecond, you need to enable the high resolution tick for the scheduler.

```Shell
sudo su
cd /sys/kernel/debug
echo HRTICK > sched_features
```

This needs to be done every time the system boots, so write a script to do that.
