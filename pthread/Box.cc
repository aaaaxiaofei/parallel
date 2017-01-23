#include "Box.h"
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

CBox::CBox(void)
{
}


CBox::~CBox(void)
{
}

void CBox::input(istream& myfile){

	// read in box id 
	myfile >> boxID;

	// read in position information
	myfile >> upper_y >> left_x >> height >> width;
	lower_y = upper_y + height;
	right_x = left_x + width;

	// read in number of neighbouring boxes
	int num_neighbour, temp_id;

	// read in id of top boxes
	myfile >> num_neighbour;
	for(int i=0; i<num_neighbour; i++){
		myfile >> temp_id;
		top_id.push_back(temp_id);
	}

	// read in id of bottom boxes
	myfile >> num_neighbour;
	for(int i=0; i<num_neighbour; i++){
		myfile >> temp_id;
		bottom_id.push_back(temp_id);
	}

	// read in id of left boxes
	myfile >> num_neighbour;
	for(int i=0; i<num_neighbour; i++){
		myfile >> temp_id;
		left_id.push_back(temp_id);
	}

	// read in id of right boxes
	myfile >> num_neighbour;
	for(int i=0; i<num_neighbour; i++){
		myfile >> temp_id;
		right_id.push_back(temp_id);
	}

	// read in temperature
	myfile >> T;

}

void CBox::print(){
	// output basic information of a box
	cout<<"=========== Box "<<boxID<<" =========="<<endl;
	cout<<"left  x: "<<left_x<<"   right x: "<<right_x<<endl;
	cout<<"upper y: "<<upper_y<<"   lower y: "<<lower_y<<endl;
	cout<<"width: "<<width<<"   height: "<<height<<endl<<endl;
	
	cout<<"Temperature: "<<T<<endl<<endl;
	
	// output neighboring boxes IDs
	vector<int>::iterator it;
	for(it=left_id.begin(); it!= left_id.end(); it++)
		cout<<"left box id: "<<*it<<endl;
	for(it=right_id.begin(); it!= right_id.end(); it++)
		cout<<"right box id: "<<*it<<endl;
	for(it=top_id.begin(); it!= top_id.end(); it++)
		cout<<"top box id: "<<*it<<endl;
	for(it=bottom_id.begin(); it!= bottom_id.end(); it++)
		cout<<"bottom box id: "<<*it<<endl;
}

double CBox::computeT(CBox box[]){
	
	// dist is the overlapping length of two neighbor boxes
	// perimeter is for current box
	// sumT is the weighted summation of temperature
	double dist=0, perimeter=0, sumT=0;
	
	// vector iterator
	vector<int>::iterator it;

	// box to the left
	if(left_id.size()==0 ){
		perimeter += height;
		sumT += height*T;
	}
	else {
		for(it=left_id.begin(); it!= left_id.end(); it++) {
			dist = min(lower_y, box[*it].lower_y)- max(upper_y, box[*it].upper_y);
			if(dist<=0)
				cout<<"dist is wrong"<<endl;
			perimeter += dist;
			sumT += dist*box[*it].T;
		}
	}

	// box to the right
	if(right_id.size()==0 ){
		perimeter += height;
		sumT += height*T;
	}
	else {
		for(it=right_id.begin(); it!= right_id.end(); it++) {
			dist = min(lower_y, box[*it].lower_y)- max(upper_y, box[*it].upper_y);
			if(dist<=0)
				cout<<"dist is wrong"<<endl;
			perimeter += dist;
			sumT += dist*box[*it].T;
		}
	}

	// box to the top
	if(top_id.size()==0 ){
		perimeter += width;
		sumT += width*T;
	}
	else {
		for(it=top_id.begin(); it!= top_id.end(); it++) {
			dist = min(right_x, box[*it].right_x)- max(left_x, box[*it].left_x);
			if(dist<=0)
				cout<<"dist is wrong"<<endl;
			perimeter += dist;
			sumT += dist*box[*it].T;
		}
	}

	// box to the bottom
	if(bottom_id.size()==0 ){
		perimeter += width;
		sumT += width*T;
	}
	else {
		for(it=bottom_id.begin(); it!= bottom_id.end(); it++) {
			dist = min(right_x, box[*it].right_x)- max(left_x, box[*it].left_x);
			if(dist<=0)
				cout<<"dist is wrong"<<endl;
			perimeter += dist;
			sumT += dist*box[*it].T;
		}
	}

	//cout<<"sumT is: "<<sumT<<", perimeter is: "<<perimeter<<", average T is: "<<sumT/perimeter<<endl;
	return sumT/perimeter;
}
