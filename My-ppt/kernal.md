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

######
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
######

## sysfs entry
===============


Let’s add a sysfs entry to your mychardev module so you can read and write the value variable from user-space.

## Step 1: Include necessary headers

#include <linux/kobject.h>
#include <linux/sysfs.h>


## Step 2: Declare kobject and attribute

# Sysfs show function (read)
static ssize_t value_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    return sprintf(buf, "%d\n", value);
}

# Sysfs store function (write)
static ssize_t value_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
    sscanf(buf, "%d", &value);
    printk(KERN_INFO "mychardev: sysfs value updated to %d\n", value);
    return count;
}

## Define the attribute (read/write)
static struct kobj_attribute value_attribute =
    __ATTR(value, 0664, value_show, value_store);


## step3: Create the sysfs entry in hello_init()

# Create /sys/kernel/mychardev directory
my_kobj = kobject_create_and_add("mychardev", kernel_kobj);
if (!my_kobj) {
    printk(KERN_ERR "mychardev: failed to create kobject\n");
    return -ENOMEM;
}

# Create value attribute
if (sysfs_create_file(my_kobj, &value_attribute.attr)) {
    printk(KERN_ERR "mychardev: failed to create sysfs file\n");
    kobject_put(my_kobj);
    return -ENOMEM;
}

## step4: Remove the sysfs entry in hello_exit()

kobject_put(my_kobj);  // removes the directory and all attributes



## /proc entry
===============


Let’s go step by step to add a /proc entry to your mychardev module so you can monitor internal stats (like data_size) from user-space.

# Step 1: Include necessary headers

Add at the top of your file (with other includes):

#include <linux/proc_fs.h>
#include <linux/seq_file.h>

proc_fs.h → functions to create/remove proc entries

seq_file.h → helper for sequential file output (clean way to implement /proc reads)

# step2: Create a show function

This function is called when user does cat /proc/<your_file>.

static int my_proc_show(struct seq_file *m, void *v)
{
    seq_printf(m, "mychardev buffer size = %d\n", data_size);
    seq_printf(m, "mychardev value = %d\n", value);
    return 0;
}

# Step 3: Implement open function for proc

static int my_proc_open(struct inode *inode, struct file *file)
{
    return single_open(file, my_proc_show, NULL);
}


single_open is a helper function for simple /proc files that only need one read.

# Step 4: Define proc operations

static const struct proc_ops my_proc_ops = {
    .proc_open    = my_proc_open,
    .proc_read    = seq_read,
    .proc_lseek   = seq_lseek,
    .proc_release = single_release,
};

# Step 5: Create the proc entry in init()

Add this in hello_init() after adding cdev:

proc_create("mychardev_info", 0444, NULL, &my_proc_ops);


"mychardev_info" → filename under /proc

0444 → read-only for everyone

NULL → parent directory (/proc)


# Step 6: Remove proc entry in exit()

Add this in hello_exit():

remove_proc_entry("mychardev_info", NULL);

Cleans up the entry when the module is removed.

# Step 7: Test from user-space
cat /proc/mychardev_info

Note:
/proc → read-only monitoring info
/sys → configuration / read/write attributes
Now your driver has both monitoring and configuration interfaces.


# /dev/mychardev appear automatically, so you no longer need mknod.

## step 1: Add global variables

Add these near top:

static struct class *my_class;
static struct device *my_device;

## Step 2: Add class + device creation in hello_init()

Put this after cdev_add():

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

## Step 3: Add cleanup in hello_exit()

Add BEFORE cdev_del():

device_destroy(my_class, dev_number);
class_destroy(my_class);


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

