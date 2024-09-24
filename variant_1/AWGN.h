#ifndef AWGN_h
#define AWGN_h
#include <vector>
#include <cmath>
#include "MyFunc.h"
using namespace std;

class AWGN {
private:
	int* SNRdb;
	int size;
	double* sigma;
public:
	AWGN(int start, int finish, int step, int count_q, double* E);
	~AWGN();
	vector<double> apply_noise(vector<double> s, int count_q, vector<double> fi_1, vector<double> fi_2, int indx, double dt);
	int* Get_SNRdb();
	double Get_sigma_index(int ind);
	int Get_size_SNR();
};
#endif 