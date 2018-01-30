#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/ioctl.h>
#include <linux/random.h>
#include <asm/uaccess.h>

#include "adc_dev.h"

static dev_t d_num;
static struct cdev c_dev;
static struct class *cls;
unsigned int adc;
unsigned int val;

int adc_ioctl(struct file *file,unsigned int cmd,unsigned long ioctl_param)
{
	get_random_bytes(&adc,sizeof(adc));
	val = (adc%1024);
	switch (cmd)
	{
		case ADC_CH_0:
			printk(KERN_INFO "ADC0 CH 0 Value returned = %u\n",val);
			put_user(val,(unsigned int *)ioctl_param); //int * tells that ioctl_param holds address of int number i.e 2nd argu holds 										the address of buffer where data is to be copied from k2u
 		break;
 		
 		case ADC_CH_1:
			printk(KERN_INFO "ADC0 CH 1 Value returned = %u\n",val);
			copy_to_user((unsigned int *)ioctl_param,&val,sizeof(unsigned int));
 		break;
 		
 		case ADC_CH_2:
			printk(KERN_INFO "ADC0 CH 2 Value returned = %u\n",val);
			copy_to_user((unsigned int *)ioctl_param,&val,sizeof(unsigned int));
 		break;
 		
 		case ADC_CH_3:
			printk(KERN_INFO "ADC0 CH 3 Value returned = %u\n",val);
			copy_to_user((unsigned int *)ioctl_param,&val,sizeof(unsigned int));
 		break;
 		
 		case ADC_CH_4:
			printk(KERN_INFO "ADC0 CH 4 Value returned = %u\n",val);
			copy_to_user((unsigned int *)ioctl_param,&val,sizeof(unsigned int));
 		break;
 		
 		case ADC_CH_5:
			printk(KERN_INFO "ADC0 CH 5 Value returned = %u\n",val);
			copy_to_user((unsigned int *)ioctl_param,&val,sizeof(unsigned int));
 		break;
 		
 		case ADC_CH_6:
			printk(KERN_INFO "ADC0 CH 6 Value returned = %u\n",val);
			copy_to_user((unsigned int *)ioctl_param,&val,sizeof(unsigned int));
 		break;
 		
 		case ADC_CH_7:
			printk(KERN_INFO "ADC0 CH 7 Value returned = %u\n",val);
			copy_to_user((unsigned int *)ioctl_param,&val,sizeof(unsigned int));
 		break;
	}
  return 0;
}


static int adc_open(struct inode *i,struct file *f)
{
	printk(KERN_INFO "ADC0 is OPENED()\n");
	return 0;
}

static int adc_close(struct inode *i,struct file *f)
{
	printk(KERN_INFO "ADC0 is CLOSED()\n");
	return 0;
}

static int adc_read(struct file *f,char __user *buf,size_t len,loff_t *off)
{
	printk(KERN_INFO "ADC0 is READ()\n");
	return 0;
}

static int adc_write(struct file *f,const char __user *buf,size_t len,loff_t *off)
{
	printk(KERN_INFO "ADC0 is WRITTEN()\n");
	return 0;
}

static struct file_operations fops = 
{
	.owner = THIS_MODULE,
	.open = adc_open,
	.release = adc_close,
	.read = adc_read,
	.write = adc_write,
	.unlocked_ioctl = adc_ioctl
};


static int __init adc_init(void)
{
	printk(KERN_INFO "ADC0 REGISTERED \n\n");
	
	if(alloc_chrdev_region(&d_num,0,1,"ADC0")<0)
	{
		return -1;
	}
	printk(KERN_INFO "Major and Minor are %d & %d\n",MAJOR(d_num),MINOR(d_num));
	
	//STEP 2  Dynamically create device node in /dev directory
	
	if((cls = class_create(THIS_MODULE,"ADCDRV")) == NULL)
	{
		unregister_chrdev_region(d_num,1);
		return -1;
	}
	
	if(device_create(cls,NULL,d_num,NULL,"ADC0")==NULL)
	{
		class_destroy(cls);
		unregister_chrdev_region(d_num,1);
		return -1;
	}
	
	// STEP 3 Link Fops and Cdev to Device Node
	cdev_init(&c_dev,&fops);
	
	if(cdev_add(&c_dev,d_num,1) == -1)
	{
		device_destroy(cls,d_num);
		class_destroy(cls);
		unregister_chrdev_region(d_num,1);
		return -1;
	}
	
	
	return 0;
}


static void __exit adc_exit(void)
{
	cdev_del(&c_dev);
	device_destroy(cls,d_num);
	class_destroy(cls);
	unregister_chrdev_region(d_num,1);
	printk(KERN_INFO "ADC0 UNREGISTERD");
}

module_init(adc_init);
module_exit(adc_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Deepan Gulati");
MODULE_DESCRIPTION("ADC0 Implementation");
