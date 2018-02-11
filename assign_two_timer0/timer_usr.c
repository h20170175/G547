#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdlib.h>

#include "chardev.h"

unsigned int val;

int delay_ms(int fd,unsigned int val)
{

  int ret;
	  	ret = ioctl(fd,delay,&val);
	   	if(ret<0){
	  	printf("TIMER0_IOCTL failed: %u\n",ret);
	  	exit(-1);
	  	}
	 	printf("TIMER0 delay of %ums exec.\n",val);
 	
 return 0;
}

int main(int argc,char *argv[])
{
	int fd,ip,ret,count;
	char buf[2];
	//ch = atoi(argv[1]);
	fd = open("/dev/TIMER0",0);
	if(fd<0){
	printf("cannot open file: %d\n",fd);
	exit(-1);
	}
	printf("\t\t\t***************************************************\n");
	printf("\t\t\t** Enter 1 to read counter and 2 for using delay **\n");
	printf("\t\t\t***************************************************\n");
	scanf("%d",&ip);
	switch(ip)
	{
          case 1:
	  ret=read(fd,buf,2);
	  count=(unsigned char)buf[0];
	  count=count|((unsigned char)buf[1]<<8);
	  printf("counter value is %d\n",count);
	  break;
	  case 2:
	  printf("\t\t\t****************************************\n");
	  printf("\t\t\t* How many ms delay you want. Enter it *\n");
	  printf("\t\t\t****************************************\n");
	  scanf("%u",&val);
  	  delay_ms(fd,val);	
	  break;
	  default:
	  printf("Kindly enter valid input\n");
	}
	
  	return 0;
}
