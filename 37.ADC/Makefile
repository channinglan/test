#CC = /usr/local/arm-2009q3/bin/arm-none-linux-gnueabi-gcc
CC = gcc
#STRIP = /usr/local/arm-2009q3/bin/arm-none-linux-gnueabi-strip
OBJ=adc
OBJ2=adc_check
OBJ3=adc_show
all:
	$(CC) $(INCLUDE) $(OBJ).c -o $(OBJ)
#	$(STRIP) $(OBJ)
	$(CC) $(INCLUDE) $(OBJ2).c -o $(OBJ2)
	$(CC) $(INCLUDE) $(OBJ3).c -o $(OBJ3)	
	#$(STRIP) $(OBJ2)
	
		

clean:
	rm -rf $(OBJ)
	rm -rf $(OBJ2)	
	rm -rf $(OBJ3)	
