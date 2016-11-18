/* An example of platform_device */

// Using platform_device_alloc() + platform_device_add() instead of platform_device_register()
// to avoid message, "Device does not have a release() function, it is broken and must be fixed."


#include <linux/module.h>			// module_init(), module_exit()
#include <linux/device.h>			// dev_info()
#include <linux/printk.h>			// pr_info()
#include <linux/platform_device.h>

#define DEVNAME "new"

// ================ platform device ================
// struct platform_device
static struct platform_device *brook_device;


// ================ platform driver ================

// probe
static int new_probe(struct platform_device *pdev)
{
	pr_info("%s(#%d)\n", __func__, __LINE__);
	return 0;
}

// remove
static int new_remove(struct platform_device *pdev)
{
	pr_info("%s(#%d)\n", __func__, __LINE__);
	return 0;
}

// struct platform_driver
static struct platform_driver new_driver = {
	.driver = {
		.name  = DEVNAME,
		.owner = THIS_MODULE,
	},
	.probe  = new_probe,
	.remove = new_remove,
};


// ================ module ================
static int __init new_init(void)
{
	int err;
	pr_info("%s(#%d)\n", __func__, __LINE__);

	// platform_device_alloc
        brook_device = platform_device_alloc(DEVNAME, 0);
        if (!brook_device) {
		pr_err("%s(#%d): platform_device_alloc fail\n", __func__, __LINE__);
		return -ENOMEM;
        }

	// platform_device_add
        err = platform_device_add(brook_device);
        if (err) {
		pr_err("%s(#%d): platform_device_add failed\n", __func__, __LINE__);
		goto dev_add_failed;
        }

	err = platform_driver_register(&new_driver);
	if (err) {
		dev_err(&(new_device.dev), "%s(#%d): platform_driver_register fail(%d)\n", __func__, __LINE__, err);
		goto dev_reg_failed;
	}
	return err;

dev_reg_failed:
	platform_device_unregister(&new_device);

	return err;
}
module_init(new_init);

static void __exit new_exit(void)
{
	dev_info(&(new_device.dev), "%s(#%d)\n", __func__, __LINE__);
	platform_device_unregister(&new_device);
	platform_driver_unregister(&new_driver);
}
module_exit(new_exit);


MODULE_AUTHOR("Lin Emsber");
MODULE_DESCRIPTION("platform device");
MODULE_LICENSE("GPL");
