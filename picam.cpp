#include <stdio.h>
#include <unistd.h>
#include "camera.h"
#include "graphics.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdint.h>
#include <stdlib.h>
#include <sys/time.h>

using namespace std;

#define MAIN_TEXTURE_WIDTH 480
#define MAIN_TEXTURE_HEIGHT 320

char tmpbuff[MAIN_TEXTURE_WIDTH*MAIN_TEXTURE_HEIGHT*4];

void writeFrameToFile(CCamera* cam);

//entry point
int main(int argc, const char **argv)
{
	//should the camera convert frame data from yuv to argb automatically?
	bool do_argb_conversion = true;

	//how many detail levels (1 = just the capture res, > 1 goes down by half each level, 4 max)
	int num_levels = 1;

	//init graphics and the camera
	InitGraphics();
	CCamera* cam = StartCamera(MAIN_TEXTURE_WIDTH, MAIN_TEXTURE_HEIGHT,30,num_levels,do_argb_conversion);

	printf("Running frame loop\n");
/*        
       char mybuffer[MAIN_TEXTURE_WIDTH*MAIN_TEXTURE_HEIGHT*4];
       cam->ReadFrame(0, mybuffer, sizeof(mybuffer));
       ofstream file;
       file.open("out.txt");
       
       string byte;

       int j = 0;
       for (int i = 0; i <  MAIN_TEXTURE_WIDTH*MAIN_TEXTURE_HEIGHT*4; i = i+4){
           uint16_t tmp16 = 0;
           tmp16 |= ((mybuffer[i] / 8) & 31) << 11;
           tmp16 |= ((mybuffer[i+1] / 4) & 63) << 5;
           tmp16 |= ((mybuffer[i+2] / 8) & 31);

           file.write((char*)&tmp16, sizeof(uint16_t));
           j++;
       }
       file.close();
       cout << j << endl;
*/
	for(int i = 0; i < 150; i++)
	{
             writeFrameToFile(cam);
	}

	StopCamera();
}

void writeFrameToFile(CCamera* cam){
	timespec start;
	char mybuffer[MAIN_TEXTURE_WIDTH*MAIN_TEXTURE_HEIGHT*4];
	
	ofstream file;
	file.open("out.txt");
	
	clock_gettime(CLOCK_REALTIME, &start);
	cam->ReadFrame(0, mybuffer, sizeof(mybuffer));
	timespec end;	
	clock_gettime(CLOCK_REALTIME, &end);
	

	timespec start2;
	clock_gettime(CLOCK_REALTIME, &start2);
	for (int i = 0; i <  MAIN_TEXTURE_WIDTH*MAIN_TEXTURE_HEIGHT*4; i = i+4){

		uint16_t tmp16 = 0;
		tmp16 |= ((mybuffer[i] / 8) & 31) << 11;
		tmp16 |= ((mybuffer[i+1] / 4) & 63) << 5;
		tmp16 |= ((mybuffer[i+2] / 8) & 31);
	
		//file.write((char*)&tmp16, sizeof(uint16_t));
	}

	timespec end2;	
	clock_gettime(CLOCK_REALTIME, &end2);
	cout << "Processing:" << end2.tv_nsec - start2.tv_nsec << endl;

	cout << end.tv_nsec - start.tv_nsec << endl;
	file.close();
	system("cp out.txt /dev/fb1");
}

