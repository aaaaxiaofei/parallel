#include "stdlib.h"
#include "Box.h"
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <chrono>
#include <pthread.h>

using namespace std;

int num_box, num_threads;
double *T_temp, maxT, minT, AFFECT_RATE, EPSILON;
CBox *box;


void *dissipate(void *threadid)
{
  long tid = (long)threadid;
  
  // number of calculations in each thread
  int block_size = num_box/num_threads+1;
  
  for(int ibox=tid*block_size; ibox<(tid+1)*block_size && ibox<num_box; ibox++) {
      // array "box" is the input of function computeT(box)
      T_temp[ibox] = box[ibox].T - (box[ibox].T - box[ibox].computeT(box))*AFFECT_RATE;
  }

  pthread_exit(NULL);
}



int main(int argc, char* argv[])
{
	//double AFFECT_RATE, EPSILON;
	if (argc>=4){
		AFFECT_RATE = strtod(argv[1],NULL);
		EPSILON = strtod(argv[2],NULL);
		num_threads = strtod(argv[3],NULL);

	}
	else {
		cout<<"Not enough inputs, please enter AFFECT_RATE, EPSILON and input file\n";
		return 0;
	}

	/////////////////////////////////////////
	//		 Timer  	       //
	/////////////////////////////////////////
	time_t timer1, timer2;
	clock_t clock1, clock2;
	//chrono::time_point<chrono::system_clock> chrono_start, chrono_end;

	/////////////////////////////////////////
	//	   Read Input File	       // 
	/////////////////////////////////////////

	// total number of boxed, rows and columns
	int row, col;

	// read in number of boxes, rows and columns
	cin >> num_box >> row >> col;

	// create a box object
	box = new CBox[num_box];

	// read in all boxes parameters
	for(int ibox=0; ibox<num_box; ibox++){
		box[ibox].input(cin);
	}

	// check if the input file is read completely
	int last_line;
	cin >> last_line;
	if(last_line!=-1)
		cout<<"Input file read incorrectly...Please check input file "<<endl;


	/////////////////////////////////////////
	//	   Dissipation Model	       //
	///////////////////////////////////////// 

	// computed temperature values
	T_temp = new double[num_box];

	int count=0;    // while loop counter
	time(&timer1);	// get start time
	clock1 = clock(); // get start clock
	auto chrono_start = chrono::system_clock::now();
  
	 while(++count) {

		// call dissipation model
		for(int ibox=0; ibox<num_box; ibox++) {
		  // array "box" is the input of function computeT(box)
		  T_temp[ibox] = box[ibox].T - (box[ibox].T - box[ibox].computeT(box))*AFFECT_RATE;
		}
    
		for(int ibox=0; ibox<num_box; ibox++) {
			box[ibox].T = T_temp[ibox];
		}

		// Compute min/max temperature
		minT = T_temp[0];
		maxT = minT;
    
		for (int ibox=0; ibox<num_box; ibox++) {
		  maxT = max(T_temp[ibox],maxT);
		  minT = min(T_temp[ibox],minT);
		}
    
		if((maxT-minT)/maxT<EPSILON) {
			break;
		}
	}

	time(&timer2); // get end time
	clock2 = clock(); // get end clock
	auto chrono_time = chrono::system_clock::now()-chrono_start;
	
	/////////////////////////////////////////
	//			  Output
	///////////////////////////////////////// 
	printf("************************************************************\n");
	printf("dissipation converged in %d iterations, \n", count);
	printf("   with max DSV = %9.7f and min DSV = %9.7f \n", maxT, minT);
	printf("   affect rate  = %3.1f		 epsilon = %3.1f \n\n", AFFECT_RATE, EPSILON);
	
	printf("elapsed convergence loop time  (clock): %d  \n",clock2-clock1);
	printf("elapsed convergence loop time   (time): %.f \n",difftime(timer2,timer1));
	printf("elapsed convergence loop time (chrono): %3.1f \n",chrono::duration<double, std::milli>(chrono_time).count());

	printf("************************************************************\n");




	delete [] box;
	delete [] T_temp;
	
	return 0;
}

