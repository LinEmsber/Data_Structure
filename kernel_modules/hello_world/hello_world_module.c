/*
 * An implementation of kernel module using a device file in /dev, and this device is miscellanceous device.
 */

// 1. sudo insmod hello_world_module.ko
// 2. sudo cat /dev/hello


#include <linux/fs.h>                   // file_operations
#include <linux/init.h>                 // __intit, __exit
#include <linux/miscdevice.h>           // struct miscdevice,
#include <linux/module.h>               // module_init(), moduel_exit()

#include <asm/uaccess.h>                // copy_to_user(), copy_from_user()

// hello_read() is the function called when a process calls read() on /dev/hello.
// It writes "Hello, world!" to the buffer passed in the read() call.
static ssize_t hello_read(struct file * file, char * buf, size_t count, loff_t *ppos)
{
	char *hello_str = "Hello, world!\n";
	int len = strlen(hello_str); /* Don't include the null byte. */

	// We only support reading the whole string at once.
	if (count < len)
		return -EINVAL;

	// If file position is non-zero, then assume the string has been read and indicate
	// there is no more data to be read.
	if (*ppos != 0)
		return 0;

	// Besides copying the string to the user provided buffer, this function also checks that
	// the user has permission to write to the buffer, that it is mapped, etc.
	if (copy_to_user(buf, hello_str, len))
		return -EINVAL;

	// Tell the user how much data we wrote.
	*ppos = len;

	return len;
}



static const struct file_operations hello_fops = {
	.owner         = THIS_MODULE,
	.read          = hello_read,
};



static struct miscdevice hello_dev = {

	// We don't care what minor number we end up with, so tell thekernel to just pick one.
	.minor = MISC_DYNAMIC_MINOR,

	// Name, /dev/hello.
	.name = "hello",

	// What functions to call when a program performs file operations on the device.
	.fops = &hello_fops
};

static int __init hello_init(void)
{
	int ret;

	// Create the "hello" device in the /sys/class/misc directory.
	// This devices will automatically create the /dev/hello device using the default rules.
	ret = misc_register(&hello_dev);
	if (ret)
		printk(KERN_ERR "Unable to register \"Hello, world!\" misc device\n");

	return ret;
}


static void __exit hello_exit(void)
{
	misc_deregister(&hello_dev);
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Lin Emsber");
MODULE_DESCRIPTION("Hello, world!\n");
MODULE_VERSION("dev");
