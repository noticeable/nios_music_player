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
#include <time.h>
#include <stdlib.h>
#include <sys/alt_alarm.h>
#include <sys/alt_timestamp.h>
#include <altera_avalon_timer.h>

void computeMatrix(void){
	int a[100][100];
	int b[100][100];
	int c[100][100];
	int start_time = 1;
	int end_time = 2;
	int i;
	int k;
	int j;
	int sum;
	//Initialize
	for(i=0; i <100; i++){
		for(j=0; j <100; j++){
			a[i][j] = rand();
			b[i][j] = rand();
		}
	}
	i = 0;
	j = 0;
	//START COMPUTE
	start_time = (int) alt_timestamp();
	for(i=0; i <100; i++){
		sum = 0;
		for(j=0; j <100; j++){
			for(k=0; k <100; k++){
				sum = sum + a[i][k]*b[k][j];
			}
			c[i][j] = sum;
		}
	}
	end_time = (int) alt_timestamp();
	printf("time taken: %d clock ticks\n", end_time - start_time);
	printf("             %f seconds\n", (float)(end_time - start_time)/(float)alt_timestamp_freq());

}
int main()
{
  printf("Hello from Nios II!\n");
  computeMatrix();
  return 0;
}
