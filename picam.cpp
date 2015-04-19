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

#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

using namespace std;

#define MAIN_TEXTURE_WIDTH 480
#define MAIN_TEXTURE_HEIGHT 320

char tmpbuff[MAIN_TEXTURE_WIDTH*MAIN_TEXTURE_HEIGHT*4];

void writeFrameToFile(CCamera* cam);
void writeFrameToMemory(CCamera* cam, char* buffer, struct fb_var_screeninfo vinfo, struct fb_fix_screeninfo finfo);

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
	
	int fbfd = 0;
	struct fb_var_screeninfo vinfo;
	struct fb_fix_screeninfo finfo;
	long int screensize = 0;
	char* fbp = 0;
	long int location = 0;

	fbfd = open("/dev/fb1", O_RDWR);

	if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1) {
        	perror("Error reading fixed information");
	        exit(2);
	}	

	if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
        	perror("Error reading variable information");
	        exit(3);
        }
	screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

	fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
	if ((int)fbp == -1) {
        	perror("Error: failed to map framebuffer device to memory");
        	exit(4);
	}
	printf("The framebuffer device was mapped to memory successfully.\n");
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
             //writeFrameToFile(cam);
		writeFrameToMemory(cam, fbp, vinfo, finfo);
	}

	munmap(fbp, screensize);
	close(fbfd);
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
	for (int i = 0; i < MAIN_TEXTURE_WIDTH*MAIN_TEXTURE_HEIGHT*4; i = i+4){

		uint16_t tmp16 = 0;
		tmp16 |= ((mybuffer[i] / 8) & 31) << 11;
		tmp16 |= ((mybuffer[i+1] / 4) & 63) << 5;
		tmp16 |= ((mybuffer[i+2] / 8) & 31);
	
		file.write((char*)&tmp16, sizeof(uint16_t));
	}

	timespec end2;	
	clock_gettime(CLOCK_REALTIME, &end2);
	cout << "Processing:" << end2.tv_nsec - start2.tv_nsec << endl;

	cout << end.tv_nsec - start.tv_nsec << endl;
	file.close();
	system("cp out.txt /dev/fb1");
}

void writeFrameToMemory(CCamera* cam, char* buffer, struct fb_var_screeninfo vinfo, struct fb_fix_screeninfo finfo){
	char mybuffer[MAIN_TEXTURE_WIDTH*MAIN_TEXTURE_HEIGHT*4];
	cam->ReadFrame(0, mybuffer, sizeof(mybuffer));
	int x = 0, y = 0;
	int location = 0;
	int i = 0;
	/*
	int j = 0;
	for (int i = 0; i <  MAIN_TEXTURE_WIDTH*MAIN_TEXTURE_HEIGHT*4; i += 4){

		uint16_t tmp16 = 0;
		tmp16 |= ((mybuffer[i] / 8) & 31) << 11;
		tmp16 |= ((mybuffer[i+1] / 4) & 63) << 5;
		tmp16 |= ((mybuffer[i+2] / 8) & 31);

		buffer[j] = tmp16;
		j++;
	}*/
	for (y = 0; y < MAIN_TEXTURE_HEIGHT; y++) {
        	for (x = 0; x < MAIN_TEXTURE_WIDTH; x++) {

            		location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       		(y+vinfo.yoffset) * finfo.line_length;

		uint16_t tmp16 = 0;
		tmp16 |= ((mybuffer[i] / 8) & 31) << 11;
		tmp16 |= ((mybuffer[i+1] / 4) & 63) << 5;
		tmp16 |= ((mybuffer[i+2] / 8) & 31);
                *((uint16_t*)(buffer + location)) = tmp16;
		
		i += 4;
        	}
	}
}
