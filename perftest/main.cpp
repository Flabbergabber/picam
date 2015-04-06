#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <stdint.h>
#include <stdlib.h>
#include <sys/time.h>
using namespace std;


#define MAIN_TEXTURE_WIDTH 480
#define MAIN_TEXTURE_HEIGHT 320


void writeFrameToFile(){

        char mybuffer[MAIN_TEXTURE_WIDTH*MAIN_TEXTURE_HEIGHT*4];

        timespec start2;
        clock_gettime(CLOCK_REALTIME, &start2);

        for (int i = 0; i <  MAIN_TEXTURE_WIDTH*MAIN_TEXTURE_HEIGHT*4; i+=20){

                uint16_t tmp16 = 0;

		
                tmp16 |= ((mybuffer[i] >> 3)) << 11;
                tmp16 |= ((mybuffer[i+1] >> 2)) << 5;
                tmp16 |= ((mybuffer[i+2] >> 3));
		
		tmp16 = 0;
		tmp16 |= ((mybuffer[i+4] >> 3)) << 11;
                tmp16 |= ((mybuffer[i+5] >> 2)) << 5;
                tmp16 |= ((mybuffer[i+6] >> 3));

		tmp16 = 0;
                tmp16 |= ((mybuffer[i+8] >> 3)) << 11;
                tmp16 |= ((mybuffer[i+9] >> 2)) << 5;
                tmp16 |= ((mybuffer[i+10] >> 3));
		
		tmp16 = 0;
                tmp16 |= ((mybuffer[i+10] >> 3)) << 11;
                tmp16 |= ((mybuffer[i+11] >> 2)) << 5;
                tmp16 |= ((mybuffer[i+12] >> 3));
		
		tmp16 = 0;
                tmp16 |= ((mybuffer[i+14] >> 3)) << 11;
                tmp16 |= ((mybuffer[i+15] >> 2)) << 5;
                tmp16 |= ((mybuffer[i+16] >> 3));

	}

	timespec end2;
        clock_gettime(CLOCK_REALTIME, &end2);
        cout << "Processing:" << end2.tv_nsec - start2.tv_nsec << " nSec" << endl;
}

int main(){
	for(int i = 0; i<= 100 ;i++){
		writeFrameToFile();
	}
}
