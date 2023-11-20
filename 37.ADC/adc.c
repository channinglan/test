#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/ioctl.h>

//test

typedef struct {
	unsigned int adc_ch;
	unsigned int bass_voltage;
	unsigned int value;
}adc_params;

/* Use 'g' as magic number */
#define IOC_MAGIC  'g'

#define ADC_SET_GET_FUN _IOW(IOC_MAGIC, 0x00, adc_params)

void listitem() {
	printf("1.  ADC 0 get value\n");
	printf("2.  ADC 1 get value\n");
	printf("3.  ADC 2 get value\n");
	printf("4.  ADC 3 get value\n");

	printf("44. Exit Program\n");
	printf("Please enter the choice>> ");
}

int main(void) {
	adc_params adc;
	unsigned int cmd;
	int fd;

	/* open the /dev/icpadc dev file */
	fd = open("/dev/icpadc", O_RDONLY);
	if(fd < 0) {
		printf("Can not open /dev/icpadc\n");
		return -1;
	}

	while(1) {
		listitem();
		if (scanf("%d",&cmd)==0) {
			scanf("%*[\n]");
			getchar();
			continue;
		}

		switch (cmd) {
		case 1:
			adc.adc_ch = 0;
			adc.bass_voltage = 5; // set 5V
			adc.value = 0;
			ioctl(fd, ADC_SET_GET_FUN, &adc);
			printf("\nADC0 = 0x%x\n", adc.value);
			break;
		case 2:
			adc.adc_ch = 1;
			adc.bass_voltage = 5; // set 5V
			adc.value = 0;
			ioctl(fd, ADC_SET_GET_FUN, &adc);
			printf("\nADC1 = 0x%x\n", adc.value);
			break;
		case 3:
			adc.adc_ch = 2;
			adc.bass_voltage = 5; // set 5V
			adc.value = 0;
			ioctl(fd, ADC_SET_GET_FUN, &adc);
			printf("\nADC2 = 0x%x\n", adc.value);
			break;
		case 4:
			adc.adc_ch = 3;
			adc.bass_voltage = 5; // set 5V
			adc.value = 0;
			ioctl(fd, ADC_SET_GET_FUN, &adc);
			printf("\nADC3 = 0x%x\n", adc.value);

			break;
		case 44:
			close(fd);
			exit(0);
			break;
		default:
			break;
		}
	}

	return 0;
}
