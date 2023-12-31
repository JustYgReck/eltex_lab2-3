#include <linux/module.h> 
#include <linux/printk.h> 
#include <linux/kobject.h> 
#include <linux/sysfs.h> 
#include <linux/init.h> 
#include <linux/fs.h> 
#include <linux/string.h>

static struct kobject *example_kobject;
static int lab2_file;

static ssize_t sys_show(struct kobject *kobj, struct kobj_attribute *attr,
                      char *buf)
{
        return sprintf(buf, "%d\n", test);
}

static ssize_t sys_store(struct kobject *kobj, struct kobj_attribute *attr,
                      const char *buf, size_t count)
{
        sscanf(buf, "%du", &test);
        return count;
}


static struct kobj_attribute foo_attribute =__ATTR(lab2_file, 0775, sys_show,
                                                   sys_store);

static int __init sys_init (void)
{
        int error = 0;

        pr_debug("Module initialized successfully \n");

        example_kobject = kobject_create_and_add("lab2test",
                                                 kernel_kobj);
        if(!example_kobject)
                return -ENOMEM;

        error = sysfs_create_file(example_kobject, &foo_attribute.attr);
        if (error) {
                pr_debug("failed to create lab2_file in /sys/kernel/lab2test \n");
        }

        return error;
}

static void __exit sys_exit (void)
{
        pr_debug ("Module uninitialized successfully \n");
        kobject_put(example_kobject);
}

MODULE_LICENSE("GPL");
module_init(sys_init);
module_exit(sys_exit);