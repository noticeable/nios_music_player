#include <stdio.h>
#include <system.h>
#include <altera_up_sd_card_avalon_interface.h>
#include <altera_up_avalon_audio_and_video_config.h>
#include <altera_up_avalon_audio.h>
#include <time.h>

short int sd_fileh;
char sample_message[512] = "WELCOME TO THE INTERFACE!!\r\n\0";

void av_config_setup() {
	alt_up_av_config_dev * av_config = alt_up_av_config_open_dev("/dev/audio_and_video_config_0");
	while (!alt_up_av_config_read_ready(av_config)) {
	}
}

void waitFor (unsigned int secs) {
    unsigned int retTime = time(0) + secs;   // Get finishing time.
    while (time(0) < retTime);               // Loop until it arrives.
}

void printWAVHeader(int file_handle){
	int i =0;
	int header_block_size;
	//PRINT CHAR: RIFF
	while(i < 3){
	  int a = alt_up_sd_card_read(sd_fileh);
	  printf("%c\n",a);
	  waitFor(1);
	  i++;
	}
	i=0;
	//dwChunkSize LENGTH OF REST OF THIS BLOCK
	while(i < 1){
	  int a = alt_up_sd_card_read(sd_fileh);
	  header_block_size = a;
	  printf("%d\n",a);
	  waitFor(1);
	  i++;
	}
	//wFormatTag PCM FORMAT, value = 1
	while(i < 1){
	  short int a = alt_up_sd_card_read(sd_fileh);
	  printf("%d\n",a);
	  waitFor(1);
	  i++;
	}
	//wChannels 1=mono, 2=stereo
	while(i < 1){
	 short int a = alt_up_sd_card_read(sd_fileh);
	  printf("%d\n",a);
	  waitFor(1);
	  i++;
	}
	//dwSamplesPerSec Audio Sampling Rate
	while(i < 1){
	  int a = alt_up_sd_card_read(sd_fileh);
	  printf("%d\n",a);
	  waitFor(1);
	  i++;
	}
	i=0;
	//dwSamplesPerSec Audio Sampling Rate
	while(i < 1){
	  int a = alt_up_sd_card_read(sd_fileh);
	  printf("%d\n",a);
	  waitFor(1);
	  i++;
	}
	i=0;
	//dwAvgBytesPerSec Audio frames per second, mem needed for file
	while(i < 1){
	  int a = alt_up_sd_card_read(sd_fileh);
	  printf("%d\n",a);
	  waitFor(1);
	  i++;
	}
	i=0;
	//dwBlockAlignPerSec Audio Sampling Rate
	while(i < 1){
	  short int a = alt_up_sd_card_read(sd_fileh);
	  printf("%d\n",a);
	  waitFor(1);
	  i++;
	}
	i=0;
	//dwBitsPerSample Bit Depth
	while(i < 1){
	  int a = alt_up_sd_card_read(sd_fileh);
	  printf("%d\n",a);
	  waitFor(1);
	  i++;
	}
	i=0;
	while(i < 300){
	  char a = alt_up_sd_card_read(sd_fileh);
	  printf("%d\n",a);
	  waitFor(1);
	  i++;
	}
	i=0;
}

int main()
{
  printf("SD Card Access Test\n");
  av_config_setup();
  alt_up_sd_card_dev *sd_card_dev = alt_up_sd_card_open_dev(ALTERA_UP_SD_CARD_AVALON_INTERFACE_0_NAME);
  av_config_setup();
  if(sd_card_dev != 0)
  {
      if(alt_up_sd_card_is_Present())
      {
          if(alt_up_sd_card_is_FAT16())
              printf("Card is FAT16\n");
          else
              printf("Card is not FAT16\n");
          // OPEN FILE
          sd_fileh = alt_up_sd_card_fopen("test.wav", false);
          //FILE FAILED TO OPEN
          if (sd_fileh < 0)
              printf("Problem creating file. Error %i", sd_fileh);
          //FILE SUCCESFUL
          else
          {
              printf("SD Accessed Successfully, writing data...");
              //
              int size;
              int counter;
              int i = 0;
              char read_one;
              char read_two;
              size = counter;
              int file[size];

              printf("Done!\n");
              printWAVHeader(sd_fileh);

              printf("Closing File...");
              alt_up_sd_card_fclose(sd_fileh);
              printf("Done!\n");
          }
      }
  }

  return 0;
}
