# Kernal development

what is a kernal module?
A kernel module is a dynamically loadable object file (.ko) that runs in kernel space and adds support for additional features such as:

device drivers

file systems

network protocols

system calls

hardware support

It is loaded using:

insmod
modprobe


And removed using:

rmmod

2. module_param() is a macro used in Linux kernel modules to accept parameters from users at load time (using insmod or modprobe).

###
MODULE_LICENSE("GPL");

int value = 10;
module_param(value, int, 0644);
MODULE_PARM_DESC(value, "An integer value");

static int __init my_init(void)
{
    printk("Module loaded. value = %d\n", value);
    return 0;
}
###

sudo insmod mymodule.ko value=99

# Allocating major and minor number

what is major and minor number?

Major and minor numbers are identifiers used by the Linux kernel to connect a device file (/dev/xyz) to the correct driver.

## Major Number

Identifies which driver handles the device.

Think of it as driver ID.

Example:
If major = 240 → kernel looks up the driver registered with major 240.

## Minor Number

Identifies which specific device instance the driver handles.

Think of it as device ID inside the driver**.

```c
dev_t dev_number;   // major+minor number will be stored here

static int __init chardev_init(void)
{
    int ret;

    // Allocate a character device region
    ret = alloc_chrdev_region(&dev_number, 0, 1, "mychardev");
    if (ret < 0) {
        printk(KERN_ERR "Failed to allocate device number\n");
        return ret;
    }

    printk(KERN_INFO "Allocated Major = %d, Minor = %d\n",
           MAJOR(dev_number), MINOR(dev_number));

    return 0;
}
```

## sysfs entry

Let’s add a sysfs entry to your mychardev module so you can read and write the value variable from user-space.

### Step 1: Include necessary headers
```c
#include <linux/kobject.h>
#include <linux/sysfs.h>

```
### Step 2: Declare kobject and attribute
```c
static struct kobject *my_kobj;
```
#### Sysfs show function (read)
```c
static ssize_t value_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    return sprintf(buf, "%d\n", value);
}
```


#### Sysfs store function (write)
```c
static ssize_t value_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
    sscanf(buf, "%d", &value);
    printk(KERN_INFO "mychardev: sysfs value updated to %d\n", value);
    return count;
}
```

#### Define the attribute (read/write)
```c
static struct kobj_attribute value_attribute =
    __ATTR(value, 0664, value_show, value_store);

```
### step3: Create the sysfs entry in hello_init()

#### Create /sys/kernel/mychardev directory
```c
my_kobj = kobject_create_and_add("mychardev", kernel_kobj);
if (!my_kobj) {
    printk(KERN_ERR "mychardev: failed to create kobject\n");
    return -ENOMEM;
}
```

#### Create value attribute
```c
if (sysfs_create_file(my_kobj, &value_attribute.attr)) {
    printk(KERN_ERR "mychardev: failed to create sysfs file\n");
    kobject_put(my_kobj);
    return -ENOMEM;
}
```

### step4: Remove the sysfs entry in hello_exit()
```c
kobject_put(my_kobj);  // removes the directory and all attributes
```

# Key Differences  /dev/node and /sys/
=======================================
Aspect	        Device Nodes (/dev/)	        sysfs (/sys/)
Primary Use	    I/O Operations	            Information & Configuration
File Type	    Character/Block special     files	Regular text files
Operations	    read(), write(), ioctl()	read(), write()
Content	        Binary data streams	        Human-readable information
Created	By      mknod or devtmpfs	        Automatically by kernel


## /proc entry

Let’s go step by step to add a /proc entry to your mychardev module so you can monitor internal stats (like data_size) from user-space.

### Step 1: Include necessary headers

Add at the top of your file (with other includes):
```c
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
```
proc_fs.h → functions to create/remove proc entries

seq_file.h → helper for sequential file output (clean way to implement /proc reads)

### step2: Create a show function

This function is called when user does cat /proc/<your_file>.
```c
static int my_proc_show(struct seq_file *m, void *v)
{
    seq_printf(m, "mychardev buffer size = %d\n", data_size);
    seq_printf(m, "mychardev value = %d\n", value);
    return 0;
}
```

### Step 3: Implement open function for proc
```c
static int my_proc_open(struct inode *inode, struct file *file)
{
    return single_open(file, my_proc_show, NULL);
}
```
single_open is a helper function for simple /proc files that only need one read.

### Step 4: Define proc operations
```c
static const struct proc_ops my_proc_ops = {
    .proc_open    = my_proc_open,
    .proc_read    = seq_read,
    .proc_lseek   = seq_lseek,
    .proc_release = single_release,
};
```
### Step 5: Create the proc entry in init()

Add this in hello_init() after adding cdev:
```c
proc_create("mychardev_info", 0444, NULL, &my_proc_ops);

```
"mychardev_info" → filename under /proc

0444 → read-only for everyone

NULL → parent directory (/proc)


### Step 6: Remove proc entry in exit()

Add this in hello_exit():
```c
remove_proc_entry("mychardev_info", NULL);
```
Cleans up the entry when the module is removed.

## Step 7: Test from user-space
cat /proc/mychardev_info

Note:
/proc → read-only monitoring info
/sys → configuration / read/write attributes
Now your driver has both monitoring and configuration interfaces.


**# Different Users, Different Needs
User	                Primary Need	            Preferred Interface
====                    ============                ====================
Application Developer	Read/write data	            /dev
System Administrator	Configure device	        /sys
Support Engineer	    Debug issues	            /proc + /sys
Monitoring Tool	        Gather metrics	            /proc
**

## /dev/mychardev appear automatically, so you no longer need mknod.

### step 1: Add global variables

Add these near top:

static struct class *my_class;
static struct device *my_device;

### Step 2: Add class + device creation in hello_init()

Put this after cdev_add():
```c
// Create device class
my_class = class_create("mychardev_class");
if (IS_ERR(my_class)) {
    printk(KERN_ERR "Failed to create class\n");
    cdev_del(&my_cdev);
    unregister_chrdev_region(dev_number, 1);
    return PTR_ERR(my_class);
}

// Create device node /dev/mychardev
my_device = device_create(my_class, NULL, dev_number, NULL, "mychardev");
if (IS_ERR(my_device)) {
    printk(KERN_ERR "Failed to create device\n");
    class_destroy(my_class);
    cdev_del(&my_cdev);
    unregister_chrdev_region(dev_number, 1);
    return PTR_ERR(my_device);
}

printk(KERN_INFO "/dev/mychardev created successfully\n");
```

### Step 3: Add cleanup in hello_exit()

Add BEFORE cdev_del():
```c
device_destroy(my_class, dev_number);
class_destroy(my_class);
```

# Errors in kernal

## kernal panic

A kernel panic happens when the kernel detects a critical error and cannot continue running safely, so it crashes to avoid further damage.

Why does kernel panic happen? (Main Reasons)
1️⃣ NULL pointer dereference

Driver or kernel code tries to access memory at address 0.

2️⃣ Accessing invalid memory

Out-of-bounds array access, corrupted pointer, use-after-free, etc.

3️⃣ Invalid device tree configuration

Wrong address, wrong interrupt number, bad DT properties.

4️⃣ Driver bugs

Incorrect probe/remove, incorrect initialization, wrong clock/regulator.

5️⃣ Filesystem or rootfs errors

Kernel cannot mount the root filesystem.

Example message:
Kernel panic - not syncing: VFS: Unable to mount root fs

6️⃣ Memory corruption

Slab corruption, stack overflow, heap overflow, double free.

7️⃣ Hardware faults

Bad RAM, faulty storage, bad power, overheating.

8️⃣ Wrong kernel or U-Boot configuration


## How to debg kernal panic

How to debug a kernel panic
✔ Step 1: Check the panic message

The first line tells the reason.

✔ Step 2: Check the call stack

It shows which function caused it.

✔ Step 3: Capture logs

Use:

dmesg


or boot log from UART.

✔ Step 4: Reproduce with debug config

Enable in kernel:

CONFIG_DEBUG_KERNEL
CONFIG_DEBUG_SLAB
CONFIG_DEBUG_KMEMLEAK

✔ Step 5: Use JTAG if required

For advanced debugging.

## poll support

let's add poll() support to your driver.
This will allow user-space programs to use:

select()

poll()

epoll()

Just like real OS drivers.

### Why do drivers need poll()?

Your driver currently supports read/write, but:
**
❌ read() blocks
❌ users cannot wait for “data available”
❌ threads cannot use select() or epoll()**

Real drivers (UART, sensors, touch panels, network stacks, etc.) all implement poll() so user programs can wait for data instead of busy-looping.

### What we will add
✔ A wait queue
✔ A flag indicating "data available"
✔ poll callback inside file_operations
✔ Wake up readers when new data is written

### step1: Add these global variables

Add at top:
```c
static DECLARE_WAIT_QUEUE_HEAD(wq);
static int data_available = 0;
```

### step2: Modify my_read()
```c
ssize_t my_read(struct file *file, char __user *buf, size_t len, loff_t *off)
{
    ssize_t ret = 0;

    mutex_lock(&my_mutex);

    if (*off >= data_size) {
        data_available = 0;      // No more data
        ret = 0;
        goto out;
    }

    if (len > data_size - *off)
        len = data_size - *off;

    if (copy_to_user(buf, kbuf + *off, len)) {
        ret = -EFAULT;
        goto out;
    }

    *off += len;

    if (*off >= data_size)
        data_available = 0;      // All data read

    ret = len;

out:
    mutex_unlock(&my_mutex);
    return ret;
}
```

### step 3 Modify my_write()

After successful write, notify poll/select:
```c
ssize_t my_write(struct file *file, const char __user *buf, size_t len, loff_t *off)
{
    ssize_t ret = 0;

    mutex_lock(&my_mutex);

    if (len > 1024)
        len = 1024;

    if (copy_from_user(kbuf, buf, len)) {
        ret = -EFAULT;
        goto out;
    }

    data_size = len;
    *off = len;

    data_available = 1;                // Data ready
    wake_up_interruptible(&wq);       // Wake any waiting process

    ret = len;

out:
    mutex_unlock(&my_mutex);
    return ret;
}
```

### step 4: Add poll() callback

This is the core part.

Add this function:
```c
__poll_t my_poll(struct file *file, poll_table *wait)
{
    __poll_t mask = 0;

    // Add process to wait queue
    poll_wait(file, &wq, wait);

    // Check if data is available
    if (data_available)
        mask |= POLLIN | POLLRDNORM;  // Data available for read

    // Always writable
    mask |= POLLOUT | POLLWRNORM;

    return mask;
}
```
### step5: Add poll to file_operations
```c
struct file_operations fops = {
    .owner   = THIS_MODULE,
    .open    = my_open,
    .release = my_release,
    .read    = my_read,
    .write   = my_write,
    .poll    = my_poll,     // <---- ADD THIS
};
```

## Implement ioctl and test in userspace program

### Step 1 — Why ioctl?
**
ioctl() lets user-space send custom commands to the driver.
Examples:

Clear buffer

Get buffer size

Set/get configuration

Reset driver

Trigger hardware actions**

Your driver will now support custom operations just like real device drivers.

### Step 2 — Define ioctl Commands

We use the Linux ioctl number convention:

**_IO  - for simple commands (no data)
_IOR - read data to user
_IOW - write data from user
_IOWR - both directions**

Let’s define three ioctls:

Command	Meaning
**CLEAR_BUFFER	Clear kbuf[]
GET_SIZE	    Return data_size
SET_VALUE	    Update global 'value' variable**

Add this at top of your driver:
```c
#include <linux/ioctl.h>

#define MY_IOCTL_MAGIC 'A'

#define IOCTL_CLEAR_BUFFER _IO(MY_IOCTL_MAGIC, 1)
#define IOCTL_GET_SIZE     _IOR(MY_IOCTL_MAGIC, 2, int)
#define IOCTL_SET_VALUE    _IOW(MY_IOCTL_MAGIC, 3, int)
```

### Step 3 — Implement ioctl handler

Add this function inside your driver:
```c
long my_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    int temp;

    switch (cmd)
    {
        case IOCTL_CLEAR_BUFFER:
            mutex_lock(&my_mutex);
            data_size = 0;
            memset(kbuf, 0, sizeof(kbuf));
            mutex_unlock(&my_mutex);
            printk(KERN_INFO "mychardev: buffer cleared\n");
            break;

        case IOCTL_GET_SIZE:
            if (copy_to_user((int __user *)arg, &data_size, sizeof(int)))
                return -EFAULT;
            printk(KERN_INFO "mychardev: returned data_size = %d\n", data_size);
            break;

        case IOCTL_SET_VALUE:
            if (copy_from_user(&temp, (int __user *)arg, sizeof(int)))
                return -EFAULT;
            value = temp;
            printk(KERN_INFO "mychardev: value updated to %d\n", value);
            break;

        default:
            return -EINVAL;
    }

    return 0;
}
```
## Step 4 — Add ioctl to file_operations

Modify your struct file_operations:
```c
struct file_operations fops = {
    .owner   = THIS_MODULE,
    .open    = my_open,
    .release = my_release,
    .read    = my_read,
    .write   = my_write,
    .poll    = my_poll,
    .unlocked_ioctl = my_ioctl,   // <-- ADD THIS
};
```
























# tasklet and workqueue

Why do we need Tasklets and Workqueues at all?

Because some work cannot be done in interrupt context.

Example:

In an interrupt handler → you must return quickly

You cannot sleep

You cannot do long operations

You should not block

So kernel provides two ways to defer work:

Tasklet → short, fast, atomic work

Workqueue → longer, sleepable, threaded work

Together, they are the backbone of Linux driver design.

