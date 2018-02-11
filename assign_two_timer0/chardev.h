#ifndef CHARDEV_H
#define CHARDEV_H

#include <linux/ioctl.h>

#define MAGIC 'T'
 
 
#define delay _IOW(MAGIC,0,unsigned int)

#endif
