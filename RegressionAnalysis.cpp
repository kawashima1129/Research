#include "RegressionAnalysis.h"

RegressionAnalysis::RegressionAnalysis() {

}

RegressionAnalysis::~RegressionAnalysis() {

}

/*
t���z�̉����ݐϊm��
double p_t(int df, double t)
��1�����F���R�x
��2�����Ft�l
*/
double RegressionAnalysis::p_t(int df, double t)
{
	int i;
	double c2, p, s;

	c2 = df / (df + t * t);  /* cos^2 */
	s = sqrt(1 - c2);
	if (t < 0) s = -s;  /* sin */

	p = 0;
	for (i = df % 2 + 2; i <= df; i += 2) {
		p += s;
		s *= (i - 1) * c2 / i;
	}

	if (df & 1)     /* ���R�x��� */
		return 0.5 + (p*sqrt(c2) + atan(t / sqrt(df))) / PI;
	else            /* ���R�x������ */
		return (1 + p) / 2;
}

/*
t���z�̏㑤�ݐϊm��
double q_t(int df, double t)
��1�����F���R�x
��2�����Ft�l
*/
double RegressionAnalysis::q_t(int df, double t)
{
	return 1 - p_t(df, t);
}



void RegressionAnalysis::fit(vector<double>& centerX, vector<double>& centerY) {

	
	double x_average = accumulate(centerX.begin(), centerX.end(), 0) / double(centerX.size());
	double y_average = accumulate(centerY.begin(), centerY.end(), 0) / double(centerY.size());

	double sumX, sumY, sum;
	sumX = sumY = sum = 0;
	for (int i = 0; i < centerX.size(); i++){
		sumX += pow(centerX[i] - x_average, 2);
		sumY += pow(centerY[i] - y_average, 2);

		sum += (centerX[i] - x_average) * (centerY[i] - y_average);
	}

	double Sx = sumX / double(centerX.size());//x���U
	double Sy = sumY / double(centerY.size());//y���U
	double Sxy = sum / double(centerY.size());//�����U

	a = Sxy / Sx;
	b = y_average - (a * x_average);
	
	double error = 0;
	for (int i = 0; i < centerX.size(); i++){
		error += pow(centerY[i] - (b + a * centerX[i]), 2);
	}

	t_value = a * sqrt(centerX.size() - 2) / sqrt(error / sumX);//�X����t�l
	
	if (t_value < 0) p_value = p_t(centerX.size() - 2, t_value) * 2;
	else p_value = q_t(centerX.size() - 2, t_value) * 2;
}