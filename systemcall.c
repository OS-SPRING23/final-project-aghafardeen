#include <linux/linkage.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/pid.h>
#include <linux/sched.h>
#include <linux/mutex.h>
#include <linux/syscalls.h>

static int initialized = 0;

asmlinkage long sys_spinlock(unsigned int *lock)
{
    if (!initialized) {
        struct mutex *mutex = (struct mutex *) lock;
        mutex_init(mutex);
        initialized = 1;
    }

    struct mutex *mutex = (struct mutex *) lock;
    mutex_lock(mutex);

    return 0;
}
