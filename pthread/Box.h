#pragma once

#include <vector>
#include <string>
#include <fstream>
using namespace std;

class CBox
{
public:
	int boxID;
	double left_x, right_x, upper_y, lower_y, width, height, T, T_temp;
	vector<int> left_id, right_id, top_id, bottom_id;

	CBox(void);
	~CBox(void);

	void input(istream&);
	void print();
	double computeT(CBox box[]);
};

