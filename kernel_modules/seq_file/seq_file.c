/* Simple demonstration of the seq_file interface. */

// We'll look at the seq_file interface via an extremely simple example: a loadable module
// which creates a file called /proc/sequence.
//
// The /proc/sequence iterator just uses the count of the next number it will output as its position.
// > cat /proc/sequence


// reference:
// http://lwn.net/Articles/22359/
// http://lxr.free-electrons.com/source/include/linux/seq_file.h
// http://lxr.free-electrons.com/source/include/linux/proc_fs.h


#include <linux/init.h>			// __intit, __exit
#include <linux/module.h>		// module_init(), moduel_exit()
#include <linux/fs.h>			// file_operations
#include <linux/slab.h>			// kmalloc()

#include <linux/seq_file.h>		// struct seq_file, struct seq_operations
#include <linux/proc_fs.h>

// ==================== struct seq_operations ====================

// The sequence iterator functions.
// We simply use the count of the next line as our internal position.
static void *count_line_seq_start(struct seq_file *s, loff_t *pos)
{
	loff_t *spos = kmalloc(sizeof(loff_t), GFP_KERNEL);
	if (! spos)
		return NULL;
	*spos = *pos;
	return spos;
}

static void *count_line_seq_next(struct seq_file *s, void *v, loff_t *pos)
{
	loff_t *spos = (loff_t *) v;
	*pos = ++(*spos);
	return spos;
}

static void count_line_seq_stop(struct seq_file *s, void *v)
{
	kfree (v);
}

// The show function.
static int count_line_seq_show(struct seq_file *s, void *v)
{
	loff_t *spos = (loff_t *) v;
	seq_printf(s, "%Ld\n", *spos);
	return 0;
}

// struct seq_operations.
static struct seq_operations count_line_seq_ops = {
	.start = count_line_seq_start,
	.next  = count_line_seq_next,
	.stop  = count_line_seq_stop,
	.show  = count_line_seq_show
};


// ==================== struct file_operations ====================

// file open
static int count_line_open(struct inode *inode, struct file *file)
{
	return seq_open(file, &count_line_seq_ops);
};

// The file operations structure
static struct file_operations count_line_file_ops = {
	.owner   = THIS_MODULE,
	.open    = count_line_open,
	.read    = seq_read,
	.llseek  = seq_lseek,
	.release = seq_release
};


// ==================== Module ====================
static int count_line_init(void)
{
	struct proc_dir_entry *entry;
	entry = proc_create("sequence", 0, NULL, &count_line_file_ops);

	return 0;
}

static void count_line_exit(void)
{
	remove_proc_entry("sequence", NULL);
}

module_init(count_line_init);
module_exit(count_line_exit);

MODULE_AUTHOR("Lin Emsber");
MODULE_LICENSE("Dual BSD/GPL");
