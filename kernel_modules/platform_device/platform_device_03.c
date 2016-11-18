/* A simple sample code about platform device */

// A platform device is one which is hardwired on the board and hence not hot-pluggable.
// The driver for this device need not check for the presence of the device and can just go on
// and do what is required to enable the device to make it operational.
// If the device is not found, the driver is simply ignored.

#include <linux/init.h>
#include <linux/module.h>


#include <linux/platform_device.h>              // struct platform_device, platform_driver
#include <linux/device.h>                       // strcut device_driver, dev_get_platdata()
#include <linux/mod_devicetable.h>              // struct platform_device_id


#define DEVIEC_NAME "new_device"

// ========== device setting ==========

// data structrure for the platform data
sturct my_device_platform_data{
        int     data_1;
        chahr   data_2;
};
static struct my_device_platform_data new_data = {
        .data_1         = 1,
        .data_2         = 'a',
};


// Each platform device is associated with a set of I/O resources, referenced in the platform_device structure
static struct resource my_sources[] = {
        [0] = {
                .start  = 0x00100000,
                .end    = 0x001000FF,
                .flags  = IORESOURCE_MEM,
        },
};


// ========== platform device setting ==========
// struct platform_device
// http://lxr.free-electrons.com/source/include/linux/platform_device.h#L23
static struct platform_device my_device = {
        .name                   = DEVIEC_NAME,
        .id                     = 0,
        .dev.platform_data      = &new_data,
        .resource               = my_sources,
};

// struct platform_device_id
// http://lxr.free-electrons.com/source/include/linux/mod_devicetable.h#L498
static const struct platform_device_id my_device_id_table[] = {
	{
		.name = DEVIEC_NAME,
	}
};

// ========== driver setting ==========
// struct paltform_driver
// http://lxr.free-electrons.com/source/include/linux/platform_device.h#L180
// struct device_driver
// http://lxr.free-electrons.com/source/include/linux/device.h#L263
struct struct paltform_driver my_driver = {
        .probe          = my_driver_probe,
        .remove         = my_driver_remove,
        .driver         = {
                .name   = DEVIEC_NAME,
                .owner  = THIS_MODULE,
        }
        .id_table       = my_device_id_table,
};


// ========== driver operation =========

static int my_driver_probe(struct platform_device *pdev)
{
        struct my_device_platform_data * my_device_pdata;
        struct my_driver_data * driver_data;

        printk(KERN_ALERT " %s\n", __FUNCTION__);

        // http://lxr.free-electrons.com/source/include/linux/device.h#L263
        my_device_pdata = dev_get_platdata(&pdev->dev);

}

static int my_driver_remove(struct platform_device *pdev)
{

}


static int __init platform_device_init(void)
{
        int ret;

        paltform_device_register(&my_device);

        // http://lxr.free-electrons.com/source/include/linux/platform_device.h#L206
        ret = platform_driver_probe(&my_driver, my_driver_probe);

        return ret;
}

static void __exit platform_device_exit(void)
{
        platform_driver_unregister(&my_driver);
}


module_init(platform_device_init);
module_exit(platform_device_exit);



// https://lwn.net/Articles/448499/
// https://gist.github.com/itrobotics/1b91a51289bee3f14a3d
// http://www.codeproject.com/Tips/1080177/Linux-Platform-Device-Driver
