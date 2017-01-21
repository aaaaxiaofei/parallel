// CSE 5441 Lab 1
// Fei Xiao (xiao.466@osu.edu)
//

#include "stdlib.h"
#include "Box.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include <chrono>

using namespace std;

int main(int argc, char* argv[])
{
	double AFFECT_RATE, EPSILON;
	if (argc>=3){
		AFFECT_RATE = strtod(argv[1],NULL);
		EPSILON = strtod(argv[2],NULL);
	}
	else {
		cout<<"Not enough inputs, please enter AFFECT_RATE, EPSILON and input file\n";
		return 0;
	}

	/////////////////////////////////////////
	//				Timer
	/////////////////////////////////////////
	time_t timer1, timer2;
	clock_t clock1, clock2;
	chrono::time_point<chrono::system_clock> chrono_start, chrono_end;

	/////////////////////////////////////////
	//			Read Input File
	/////////////////////////////////////////

	// total number of boxed, rows and columns
	int num_box, row, col; 

	// read in number of boxes, rows and columns
	cin >> num_box >> row >> col;

	// create a box object
	CBox *box = new CBox[num_box];

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
	//			Dissipation Model
	///////////////////////////////////////// 

	// computed temperature values
	double *T_temp = new double[num_box];
	
	double maxT, minT;

	int count=0;    // while loop counter
	time(&timer1);	// get start time
	clock1 = clock(); // get start clock
	chrono_start = chrono::system_clock::now();
	while(++count) {

		if( count%1000 ==0)
			cout<<"iteration "<<count<<endl;	

		// compute updated temperature
		for(int ibox=0; ibox<num_box; ibox++) {
			// array "box" is the input of function computeT(box)
			T_temp[ibox] = box[ibox].T - (box[ibox].T - box[ibox].computeT(box))*AFFECT_RATE; 
		
			// find max/min temperature
			if(ibox==0){
				maxT = T_temp[ibox];
				minT = T_temp[ibox];
			}
			else {
				if (T_temp[ibox]>maxT)
					maxT = T_temp[ibox];
				if (T_temp[ibox]<minT)
					minT = T_temp[ibox];
			}
		}
		
		//cout<<"maxT: "<<maxT<<", minT: "<<minT<<endl;
		if((maxT-minT)/maxT<EPSILON) {
			break;
		}

		// update temperature
		for(int ibox=0; ibox<num_box; ibox++) {
			box[ibox].T = T_temp[ibox]; 
		}
	}

	time(&timer2); // get end time
	clock2 = clock(); // get end clock
	chrono_end = chrono::system_clock::now();
	chrono::duration<double> chrono_time = chrono_end - chrono_start;
	
	/////////////////////////////////////////
	//			  Output
	///////////////////////////////////////// 
	printf("************************************************************\n");
	printf("dissipation converged in %d iterations, \n", count);
	printf("   with max DSV = %9.7f and min DSV = %9.7f \n", maxT, minT);
	printf("   affect rate  = %3.1f		 epsilon = %3.1f \n\n", AFFECT_RATE, EPSILON);
	
	printf("elapsed convergence loop time  (clock): %d  \n",clock2-clock1);
	printf("elapsed convergence loop time   (time): %.f \n",difftime(timer2,timer1));
	printf("elapsed convergence loop time (chrono): %3.1f \n",chrono_time.count());

	printf("************************************************************\n");




	delete [] box;
	delete [] T_temp;
	
	return 0;
}

