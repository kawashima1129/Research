#pragma once

#include <vector>
#include <math.h>
#include <iostream>
#include <numeric>

#define PI 3.14159265358979323846264
using namespace std;

class RegressionAnalysis{
public:
	RegressionAnalysis();
	~RegressionAnalysis();
	void fit(vector<double>& centerX, vector<double>& centerY);
	double p_t(int df, double t);
	double q_t(int df, double t);

	double a;//�X��
	double b;//�ؕ�

	double t_value;//�X����t�l
	double p_value;//�X����p�l
};