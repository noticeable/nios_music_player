/*
 * "Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It runs with or without the MicroC/OS-II RTOS and requires a STDOUT
 * device in your system's hardware.
 * The memory footprint of this hosted application is ~69 kbytes by default
 * using the standard reference design.
 *
 * For a reduced footprint version of this template, and an explanation of how
 * to reduce the memory footprint for a given application, see the
 * "small_hello_world" template.
 *
 */

#include <stdio.h>
#include <string.h>

#define RS232_Control (*(volatile unsigned char *)(0x84000200))
#define RS232_Status (*(volatile unsigned char *)(0x84000200))
#define RS232_TxData (*(volatile unsigned char *)(0x84000202))
#define RS232_RxData (*(volatile unsigned char *)(0x84000202))
#define RS232_Baud (*(volatile unsigned char *)(0x84000204))
#define GPS_Control (*(volatile unsigned char *)(0x84000210))
#define GPS_Status (*(volatile unsigned char *)(0x84000210))
#define GPS_TxData (*(volatile unsigned char *)(0x84000212))
#define GPS_RxData (*(volatile unsigned char *)(0x84000212))
#define GPS_Baud (*(volatile unsigned char *)(0x84000214))
#define BlueTooth_Control (*(volatile unsigned char *)(0x84000220))
#define BlueTooth_Status (*(volatile unsigned char *)(0x84000220))
#define BlueTooth_TxData (*(volatile unsigned char *)(0x84000222))
#define BlueTooth_RxData (*(volatile unsigned char *)(0x84000222))
#define BlueTooth_Baud (*(volatile unsigned char *)(0x84000224))

#define TRUE 1
#define FALSE 0

int main()
{
//	Init_GPS();
//	  printf("Hello from Nios II!\n");
////	  printf("%d", GPS_Status);
//	int GPSbinInfo[100];
//	unsigned char temp;
//	int i;
//	//for(i =0; i<100; i++){
//	while(1){
////		printf("%c", GPSTestForReceivedData());
//		//GPSbinInfo[i] = getcharGPS();
//		temp = getcharGPS();
//	//	printf("%d", getcharGPS());
//	//	printf("%c", GPSbinInfo[i]);
//		printf("%d ",temp);
//	}
//  printf("Hello from Nios II!\n");

	write_BlueToothTOGPS();


  return 0;
}


void write_BlueToothTOGPS (void){
	Init_BlueTooth();
	Init_GPS();
	putcharBlueTooth(0x52);
	putcharGPS(getcharBlueTooth());
		putchar(getcharGPS());
		printf("%d \n",getcharGPS());

}

void Init_BlueTooth(void)
{
// set up 6850 Control Register to utilise a divide by 16 clock,
// set RTS low, use 8 bits of data, no parity, 1 stop bit,0010101
// transmitter interrupt disabled
	BlueTooth_Control = 0x15;
// program baud rate generator to use 9600 baud (larger than 0b100)
	BlueTooth_Baud = 0x05 ;
}
int putcharBlueTooth(int c)
{
// poll Tx bit in 6850 status register. Wait for it to become '1'
// write 'c' to the 6850 TxData register to output the character
	while(BlueTooth_Status && 0x02 != 0x02){

	}
	BlueTooth_TxData = c;
return c ; // return c
}
int getcharBlueTooth( void )
{
// poll Rx bit in 6850 status register. Wait for it to become '1'
// read received character from 6850 RxData register.
	while(BlueTooth_Status && 0x01 != 0x01){
	}
	return BlueTooth_RxData;
}

//**********************          GPS           ********************
void Init_GPS(void)
{
// set up 6850 Control Register to utilise a divide by 16 clock,
// set RTS low, use 8 bits of data, no parity, 1 stop bit,0010101
// transmitter interrupt disabled
	GPS_Control = 0x15;
// program baud rate generator to use 9600 baud (larger than 0b100)
	GPS_Baud = 0x05 ;
}
int putcharGPS(int c)
{
// poll Tx bit in 6850 status register. Wait for it to become '1'
// write 'c' to the 6850 TxData register to output the character
	while(GPS_Status && 0x02 != 0x02){

	}
	GPS_TxData = c;	//*****************************************************************************
return c ; // return c
}
int getcharGPS( void )
{
// poll Rx bit in 6850 status register. Wait for it to become '1'
// read received character from 6850 RxData register.
	while(GPS_Status && 0x01 != 0x01){
	}
	return GPS_RxData;
}
// the following function polls the 6850 to determine if any character
// has been received. It doesn't wait for one, or read it, it simply tests
// to see if one is available to read
int GPSTestForReceivedData(void)
{
// Test Rx bit in 6850 serial comms chip status register
// if RX bit is set, return TRUE, otherwise return FALSE
	int boolean;
	if(RS232_Status && 0x01 == 0x01){
		boolean = TRUE;
	}
	else
		boolean = FALSE;
	return boolean;
}
/**************************************************************************
/* Subroutine to initialise the RS232 Port by writing some data
** to the internal registers.
** Call this function at the start of the program before you attempt
** to read or write to data via the RS232 port
**
** Refer to 6850 data sheet for details of registers and
***************************************************************************/
void Init_RS232(void)
{
// set up 6850 Control Register to utilise a divide by 16 clock,
// set RTS low, use 8 bits of data, no parity, 1 stop bit,0010101
// transmitter interrupt disabled
	RS232_Control = 0x15;
// program baud rate generator to use 115k baud
	RS232_Baud = 0x01 ;
}
int putcharRS232(int c)
{
// poll Tx bit in 6850 status register. Wait for it to become '1'
// write 'c' to the 6850 TxData register to output the character
	while(RS232_Status != 0x02){
	}
	RS232_TxData = c;	//*****************************************************************************
return c ; // return c
}
int getcharRS232( void )
{
// poll Rx bit in 6850 status register. Wait for it to become '1'
// read received character from 6850 RxData register.
	while(RS232_Status != 0x00){
	}
	return RS232_RxData;
}
// the following function polls the 6850 to determine if any character
// has been received. It doesn't wait for one, or read it, it simply tests
// to see if one is available to read
int RS232TestForReceivedData(void)
{
// Test Rx bit in 6850 serial comms chip status register
// if RX bit is set, return TRUE, otherwise return FALSE
	int boolean;
	if(RS232_Status != 0x01){
		boolean = TRUE;
	}
	else
		boolean = FALSE;
	return boolean;
}

void presentGPS(void){

	//skip msg id
	char * UTCTime [10];
	char * status;
	char * latitude [9];
	char NS;
	char * longditude [9];
	char * EW;
	char * speed [5];
	char * unused [10];
	char * date[6];
	//skip mag
	//skip mag dir
	//skip mode
	//skip checksum

	char * data;
	data = (char *) malloc(60);

	int i=0;
	int commas=0;

	void findGPRMC();

	while(commas < 9){
		*(data+i) = getCharGPS();			// HOW TO iterate
		if( data[i] == 44)//,
			commas ++;
		i++;
	}
	*UTCTime = strsep(&data,",");
	status = strsep(&data,",");
	*latitude = strsep(&data,",");
	NS = strsep(&data,",");
	*longditude = strsep(&data,",");
	EW = strsep(&data,",");
	*speed = strsep(&data,",");
	*unused = strsep(&data,",");
	*date = strsep(&data,",");

	printf("speed = %c\n", speed);
}
void findGPRMC(){
	while(36!=getcharGPS()){//$
	}
	if(71==getcharGPS){//G
		if(80==getcharGPS){//P
			if(82==getcharGPS){//82 R
				if(77==getcharGPS){//M
					if(67==getcharGPS){//C
						if(44==getcharGPS){//,
						return;
						}
					}
				}
			}
		}
	}
	findGPRMC();
	return;
}
