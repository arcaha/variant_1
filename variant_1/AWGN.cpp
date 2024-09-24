#define _USE_MATH_DEFINES
#include "AWGN.h"

using namespace std;

AWGN::AWGN(int start, int finish, int step, int count_q, double* E){
	
		size = floor((double)(finish - start) / step) + 1;
		SNRdb = new int[size];
		for (int i = start, j = 0; j < size; i += step, j++)
			SNRdb[j] = i;

		double sum = 0;
		for (int i = 0; i < count_q; i++)
			sum += E[i];

		sigma = new double[size];
		for (int i = 0; i < size; i++)
			sigma[i] = sqrt(sum / (2 * log2(count_q) * pow(10, ((double)SNRdb[i] / 10.0))));
}

AWGN::~AWGN() { delete[] SNRdb; delete[] sigma;}

vector<double> AWGN::apply_noise(vector<double> s, int count_q, vector<double> fi_1, vector<double> fi_2, int indx, double dt){

	vector<double> noisy_signal, noisy_signal_fi_1, noisy_signal_fi_2, noisy_signal_points;
	
	for (int i = 0; i < s.size(); i++) {
		double randn = sqrt(-2 * log(random(0, 1))) * cos(2 * M_PI * random(0, 1));
		noisy_signal_fi_1.push_back((s[i] + (sigma[indx] * randn)) * fi_1[i]);
		noisy_signal_fi_2.push_back((s[i] + (sigma[indx] * randn)) * fi_2[i]);
	}

	noisy_signal_points.push_back(trapezoidalIntegral(dt, noisy_signal_fi_1));
	noisy_signal_points.push_back(trapezoidalIntegral(dt, noisy_signal_fi_2));

	return noisy_signal_points;
}

int* AWGN::Get_SNRdb(){ return SNRdb; }

double AWGN::Get_sigma_index(int ind) { 
	if (ind >= 0 && ind < size) return sigma[ind];
	else throw "Going beyond the noise array";
}

int AWGN::Get_size_SNR(){ return size; }


