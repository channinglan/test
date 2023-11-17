#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/ioctl.h>

#include "../30.GPIO/gpio.h"


typedef struct {
	unsigned int adc_ch;
	unsigned int bass_voltage;
	unsigned int value;
}adc_params;

/* Use 'g' as magic number */
#define IOC_MAGIC  'g'

#define ADC_SET_GET_FUN _IOW(IOC_MAGIC, 0x00, adc_params)

#define DEF_LOW	0x350

int main(int argc, char *argv[]) {
	gpio_params gpio;	
	adc_params adc;
	unsigned int cmd;
	char *stop_at;
	int fd,gpio_fd,low_value=DEF_LOW;

	if (argc <= 1) {
		printf("Use Default Low Value 0x%x\n",low_value);
	} else {
		low_value = strtol(argv[1], &stop_at, 0);
		printf("Low Value 0x%x\n",low_value);		
	}
	/* open the /dev/icpgpio dev file */
	gpio_fd = open("/dev/icpgpio", O_RDONLY);
	if(gpio_fd < 0) {
		printf("Can not open /dev/icpgpio\n");
		return -1;
	}

	/* open the /dev/icpadc dev file */
	fd = open("/dev/icpadc", O_RDONLY);
	if(fd < 0) {
		printf("Can not open /dev/icpadc\n");
		return -1;
	}

	adc.adc_ch = 0;
	adc.bass_voltage = 5; // set 5V
	adc.value = 0;
	ioctl(fd, ADC_SET_GET_FUN, &adc);
	close(fd);
	
		
	printf("\nADC0 = 0x%x\n", adc.value);
	if(adc.value < low_value) {
		printf("\n POWER OFF\n");
		gpio.group = GPIO_GROUP2;
		gpio.gpionum = GPIO10;
		gpio.data_out = 0;
		ioctl(gpio_fd, GPIO_WRITE_DATA_OUTPUT, &gpio);
		close(gpio_fd);					
	}

	return 0;
}
