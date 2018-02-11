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
#include <asm/io.h>
#include <linux/interrupt.h>
#include "chardev.h"

#define PIT_CH0 0x40
#define PIT_CH2 0x42
#define PIT_CMD 0x43
#define PIT_GATE 0x61

static dev_t d_num;
static struct cdev c_dev;
static struct class *cls;

unsigned int val;
int counter=0;

void delay_ms(int val)
{
	int wait,dumy2;
	wait = counter + val;
	while(counter<wait)//delay
	{
	   if(((dumy2=inb(PIT_GATE))&0x20)==0x20)
		if(((dumy2=inb(PIT_GATE))&0x20)==0x00)
		{
		counter++;
		//printk(KERN_INFO "Counter=%d\n",counter);
		}
	}
	counter =0;
}

long timer_ioctl(struct file *file,unsigned int cmd,unsigned long ioctl_param)
{
	if(cmd==delay){
	get_user(val,(unsigned int *)ioctl_param); //int * tells that ioctl_param holds address of int number i.e 2nd argu holds 												the address of buffer where data is copied from u2k
	delay_ms(val);
	}
	return 0;
}

static int timer_open(struct inode *i,struct file *f)
{
	printk(KERN_INFO "TIMER0 is OPENED()\n");
	return 0;
}

static int timer_close(struct inode *i,struct file *f)
{
	printk(KERN_INFO "TIMER0 is CLOSED()\n");
	return 0;
}

static ssize_t timer_read(struct file *f,char __user *buf,size_t len,loff_t *off)
{
	char ret[2];
	printk(KERN_INFO "TIMER0 is READ()\n");
	outb(0x20,PIT_CMD);
	ret[0]=inb(PIT_CH2);//lo-by
	put_user(ret[0],buf);
	ret[1]=inb(PIT_CH2);//hi-by
	put_user(ret[1],buf+1);
	return 0;
}

static ssize_t timer_write(struct file *f,const char __user *buf,size_t len,loff_t *off)
{
	printk(KERN_INFO "TIMER0 is WRITTEN()\n");
	return 0;
}

static struct file_operations fops = 
{
	.owner = THIS_MODULE,
	.open = timer_open,
	.release = timer_close,
	.read = timer_read,
	.write = timer_write,
	.unlocked_ioctl = timer_ioctl
};


static int __init timer_init(void)
{	
	int count,dumy,dumy1,dumy2;
	printk(KERN_INFO "TIMER0 REGISTERED \n\n");
	
	if(alloc_chrdev_region(&d_num,0,1,"TIMER0")<0)
	{
		return -1;
	}
	printk(KERN_INFO "Major and Minor are %d & %d\n",MAJOR(d_num),MINOR(d_num));
	
	//STEP 2  Dynamically create device node in /dev directory
	
	if((cls = class_create(THIS_MODULE,"TIMERDRV")) == NULL)
	{
		unregister_chrdev_region(d_num,1);
		return -1;
	}
	
	if(device_create(cls,NULL,d_num,NULL,"TIMER0")==NULL)
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
	
	printk(KERN_INFO "Timer0 cntl wrd and value being loaded\n");
	dumy=inb(PIT_GATE);
	
	count = 590;// 1 ms delay count
	outb(0xB6,PIT_CMD);// ch2,Mode 3 ,binary,access lo/hi
	outb((dumy | 0x01),PIT_GATE);
	outb(count&0xff,PIT_CH2);//lowb	
	outb(count >> 8,PIT_CH2);//highb
	printk(KERN_INFO "Timer0 cntl wrd and value loaded\n");
	dumy2=inb(PIT_GATE);
	printk(KERN_INFO "output = %d\n",(dumy2&0x20));	
	outb(0x20,PIT_CMD);
	dumy1=inb(PIT_CH2);
	dumy1=dumy1|(inb(PIT_CH2)<<8);
	printk(KERN_INFO "counter =%d\n",dumy1);
	return 0;
}


static void __exit timer_exit(void)
{
	cdev_del(&c_dev);
	device_destroy(cls,d_num);
	class_destroy(cls);
	unregister_chrdev_region(d_num,1);
	printk(KERN_INFO "TIMER0 UNREGISTERD");
}

module_init(timer_init);
module_exit(timer_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Deepan Gulati");
MODULE_DESCRIPTION("TIMER0 IMPLEMENTATION");

