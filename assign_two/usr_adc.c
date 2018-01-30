#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdlib.h>

#include "adc_dev.h"

unsigned int val;

int adc_read(int fd,int ch)
{

  int ret;
	  switch(ch)
	  {
	  	case 0:
	  	ret = ioctl(fd,ADC_CH_0,&val);
	   	if(ret<0){
	  	printf("ADC0_IOCTL failed: %u\n",ret);
	  	exit(-1);
	  	}
	 	printf("ADC0 CH 0 = %u\n",val); 
	 	break;
 	
 		case 1:
 		ret = ioctl(fd,ADC_CH_1,&val);
	   	if(ret<0){
	  	printf("ADC0_IOCTL failed: %u\n",ret);
	  	exit(-1);
	  	}
	 	printf("ADC0 CH 1 = %u\n",val); 
	 	break;
	 	
	 	case 2:
 		ret = ioctl(fd,ADC_CH_2,&val);
	   	if(ret<0){
	  	printf("ADC0_IOCTL failed: %u\n",ret);
	  	exit(-1);
	  	}
	 	printf("ADC0 CH 2 = %u\n",val); 
	 	break;
	 	
	 	case 3:
 		ret = ioctl(fd,ADC_CH_3,&val);
	   	if(ret<0){
	  	printf("ADC0_IOCTL failed: %u\n",ret);
	  	exit(-1);
	  	}
	 	printf("ADC0 CH 3 = %u\n",val); 
	 	break;
	 	
	 	case 4:
 		ret = ioctl(fd,ADC_CH_4,&val);
	   	if(ret<0){
	  	printf("ADC0_IOCTL failed: %u\n",ret);
	  	exit(-1);
	  	}
	 	printf("ADC0 CH 4 = %u\n",val); 
	 	break;
	 	
	 	case 5:
 		ret = ioctl(fd,ADC_CH_5,&val);
	   	if(ret<0){
	  	printf("ADC0_IOCTL failed: %u\n",ret);
	  	exit(-1);
	  	}
	 	printf("ADC0 CH 5 = %u\n",val); 
	 	break;
	 	
	 	case 6:
 		ret = ioctl(fd,ADC_CH_6,&val);
	   	if(ret<0){
	  	printf("ADC0_IOCTL failed: %u\n",ret);
	  	exit(-1);
	  	}
	 	printf("ADC0 CH 6 = %u\n",val); 
	 	break;
	 	
	 	case 7:
 		ret = ioctl(fd,ADC_CH_7,&val);
	   	if(ret<0){
	  	printf("ADC0_IOCTL failed: %u\n",ret);
	  	exit(-1);
	  	}
	 	printf("ADC0 CH 7 = %u\n",val); 
	 	break;
	 	
	 	default:
	 	printf("Kindly add a valid input (0 to 7)\n");
	 	break;
	 }
 return 0;
}

int main(int argc,char *argv[])
{
	int fd,ch=-1;
	ch = atoi(argv[1]);
	fd = open("/dev/ADC0",0);
	if(fd<0){
	printf("cannot open file: %d\n",fd);
	exit(-1);
	}
  	adc_read(fd,ch);
  	return 0;
}
