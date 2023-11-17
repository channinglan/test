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
	int fd,adc_ch=0;

	if (argc <= 1) {
		printf("EXAMPLE: adc_show adc_channel \n");
		printf("EXAMPLE: adc_show 0 \n");		
	} else {
		adc_ch = strtol(argv[1], &stop_at, 0);
		//printf("show adc_ch 0x%x\n",adc_ch);		
	}
	

	if(adc_ch > 2) {
		printf("adc_ch %d err\n",adc_ch);
		return -1;
	}	
	

	/* open the /dev/icpadc dev file */
	fd = open("/dev/icpadc", O_RDONLY);
	if(fd < 0) {
		printf("Can not open /dev/icpadc\n");
		return -1;
	}



	adc.adc_ch = adc_ch;
	adc.bass_voltage = 5; // set 5V
	adc.value = 0;
	ioctl(fd, ADC_SET_GET_FUN, &adc);
	close(fd);
	
		
	printf("\nADC%d = 0x%x\n",adc.adc_ch, adc.value);

	return 0;
}
