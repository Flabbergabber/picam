#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>
#include <string>
#include <stdint.h>
#include <stdlib.h>
#include <sys/time.h>
#include <vector>
using namespace std;


#define MAIN_TEXTURE_WIDTH 480
#define MAIN_TEXTURE_HEIGHT 320
char mybuffer[MAIN_TEXTURE_WIDTH*MAIN_TEXTURE_HEIGHT*4];

void writeFrameToFile(){

	for (int i = 0; i <  MAIN_TEXTURE_WIDTH*MAIN_TEXTURE_HEIGHT*4; i = i+4){

		uint16_t tmp16 = 0;

		tmp16 |= ((mybuffer[i] / 8) & 31) << 11;
		tmp16 |= ((mybuffer[i+1] / 4) & 63) << 5;
		tmp16 |= ((mybuffer[i+2] / 8) & 31);
	}
}	


void writeFrameToFileOptimised(){

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
}

typedef struct thdata
{
	int start;
	int end;
} myData;

void *writeFrameToFileMultithreaded(void* tData){
	myData *tdat;
	tdat = (myData*) tData;

        for (int i = tdat->start; i < tdat->end; i+=20){

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
	pthread_exit(NULL);
}

#define ITERATION 800000
#define NBTEST 2

int main(){
	std::vector<long> exeTimeA(ITERATION);
	std::vector<long> exeTimeB(ITERATION);
	std::vector<long> exeTimeC(ITERATION);

	for(int i = 0; i <= ITERATION ;i++){
                timespec start1;
                clock_gettime(CLOCK_REALTIME, &start1);

                writeFrameToFile();

                timespec end1;
                clock_gettime(CLOCK_REALTIME, &end1);

		long elapsedTime = end1.tv_nsec-start1.tv_nsec;
		if (elapsedTime > 0){
			exeTimeA.push_back(elapsedTime);	
		} else i--;
        }
	cout << "test 1 " << endl;

	for(int i = 0; i <= ITERATION ;i++){
		timespec start2;
        	clock_gettime(CLOCK_REALTIME, &start2);

		writeFrameToFileOptimised();

		timespec end2;
        	clock_gettime(CLOCK_REALTIME, &end2);
		
		long elapsedTime = end2.tv_nsec-start2.tv_nsec;
                if (elapsedTime > 0){
                        exeTimeB.push_back(elapsedTime);                
                } else i--;

	}
	
	cout << "test 2 " << endl;
	
	for(int i = 0; i <= ITERATION ;i++){
                timespec start3;
                clock_gettime(CLOCK_REALTIME, &start3);

		pthread_t thread1, thread2;
		myData dat1,dat2;
	
		dat1.start = 0;
		dat1.end = MAIN_TEXTURE_WIDTH*MAIN_TEXTURE_HEIGHT*2;

		dat2.start = MAIN_TEXTURE_WIDTH*MAIN_TEXTURE_HEIGHT*2+1;
		dat2.end = MAIN_TEXTURE_WIDTH*MAIN_TEXTURE_HEIGHT*4;
		
		pthread_create(&thread1, NULL, writeFrameToFileMultithreaded, (void*) &dat1);
 		pthread_create(&thread2, NULL, writeFrameToFileMultithreaded, (void*) &dat2);

		pthread_join(thread1, NULL);
    		pthread_join(thread2, NULL);
                
		timespec end3;
                clock_gettime(CLOCK_REALTIME, &end3);
		
		long elapsedTime = end3.tv_nsec-start3.tv_nsec;
                if (elapsedTime > 0){
                        exeTimeC.push_back(elapsedTime);
                } else i--;

        }
	
	cout << "test 3 " << endl;
	
	long moyA,moyB,moyC;
	
	cout << "calcul moyenne" << endl;

	for(int b=0;b<= exeTimeA.size();b++){
		moyA += exeTimeA[b];
	}
	moyA /= exeTimeA.size();
	
	cout << "calcul moyenne a faite" << endl;
	
	for(int b=0;b<= exeTimeB.size();b++){
                moyB += exeTimeB[b];
        }

	moyB /= exeTimeB.size();
	cout << "calcul moyenne B faite" << endl;

	for(int b=0;b<= exeTimeC.size();b++){
                moyC += exeTimeC[b];
        }

        moyC /= exeTimeC.size();
        cout << "calcul moyenne C faite" << endl;
	

        cout << "average processing for standard function is: " << moyA << " nSec" << endl;
	cout << "average processing for standard function is: " << moyB << " nSec" << endl;
	cout << "average processing for standard function is: " << moyC << " nSec" << endl;

}














