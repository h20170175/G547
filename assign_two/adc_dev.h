#ifndef CHARDEV_H
#define CHARDEV_H

#include <linux/ioctl.h>

#define MAGIC 'A'
 
 
#define ADC_CH_0 _IOR(MAGIC,0,unsigned int)
#define ADC_CH_1 _IOR(MAGIC,1,unsigned int)
#define ADC_CH_2 _IOR(MAGIC,2,unsigned int)
#define ADC_CH_3 _IOR(MAGIC,3,unsigned int)
#define ADC_CH_4 _IOR(MAGIC,4,unsigned int)
#define ADC_CH_5 _IOR(MAGIC,5,unsigned int)
#define ADC_CH_6 _IOR(MAGIC,6,unsigned int)
#define ADC_CH_7 _IOR(MAGIC,7,unsigned int)

#endif
