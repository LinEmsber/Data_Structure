/*
 * Demonstrates command line argument passing to a module, module_param().
 */


// type command lind as follow:
// > sudo insmod module_param_01.ko my_int=100 my_long=50000 my_string="hello world" my_int_array=5,6,7
// > dmesg


#include <linux/init.h>                         // __intit, __exit
#include <linux/module.h>                       // module_init(), moduel_exit()
#include <linux/moduleparam.h>                  // module_param()
#include <linux/kernel.h>
#include <linux/stat.h>


static int my_int = 0;
static long int my_long = 0;
static char *my_string = "";
static int my_int_array[3] = { -1, -1, -1 };
static int my_array_argc = 0;


// 101  * module_param - typesafe helper for a module/cmdline parameter
// 102  * @value: the variable to alter, and exposed parameter name.
// 103  * @type: the type of the parameter
// 104  * @perm: visibility in sysfs.
//
// 119  * Standard types are:
// 120  *      byte, short, ushort, int, uint, long, ulong
// 121  *      charp: a character pointer
// 122  *      bool: a bool, values 0/1, y/n, Y/N.
//
// http://lxr.free-electrons.com/source/include/linux/moduleparam.h#L125
module_param(my_int, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
module_param(my_long, long, S_IRUSR);
module_param(my_string, charp, 0000);


// 32 /* One for each parameter, describing how to use it.  Some files do
// 33    multiple of these per line, so can't just use MODULE_INFO. */
//
// http://lxr.free-electrons.com/source/include/linux/moduleparam.h#L34
MODULE_PARM_DESC(my_int, "An integer");
MODULE_PARM_DESC(my_long, "A long integer");
MODULE_PARM_DESC(my_string, "A character string");


// 416  * module_param_array - a parameter which is an array of some type
// 417  * @name: the name of the array variable
// 418  * @type: the type, as per module_param()
// 419  * @nump: optional pointer filled in with the number written
// 420  * @perm: visibility in sysfs
//
//
// http://lxr.free-electrons.com/source/include/linux/moduleparam.h#L428
module_param_array(my_int_array, int, &my_array_argc, 0000);
MODULE_PARM_DESC(my_int_array, "An array of integers");

static int __init module_param_init(void)
{
	int i;

	printk(KERN_INFO "\nhello, module_param_init");
	printk(KERN_INFO "my_int is an integer: %d\n", my_int);
	printk(KERN_INFO "my_long is a long integer: %ld\n", my_long);
	printk(KERN_INFO "my_string is a string: %s\n", my_string);

	for (i = 0; i < (sizeof my_int_array / sizeof (int)); i++){
		printk(KERN_INFO "my_int_array[%d] = %d\n", i, my_int_array[i]);
	}

	printk(KERN_INFO "got %d arguments for my_int_array.\n", my_array_argc);
	return 0;
}

static void __exit module_param_exit(void)
{
	printk(KERN_INFO "Goodbye, module_param_exit\n");
}

module_init(module_param_init);
module_exit(module_param_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Lin Emsber");
MODULE_DESCRIPTION("how to use module_param()\n");
