This Device Driver code will execute delay in milliseconds through 8254 PIT

 
Follow these steps to build the program after cloning:

#1
$ make all
$ sudo insmod timer.ko

This will load the device driver into kernel.

#2
$ gcc timer.c -o timer
$ sudo ./timer

The program will ask for 1 of 2 choices:
a. Read current timer counter value.
b. Insert delay (in milliseconds).
	- Selection of this choice will ask for delay in milliseconds.
	- Upon entering value, the delay will be executed.


