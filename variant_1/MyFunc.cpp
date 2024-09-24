#include "MyFunc.h"

double trapezoidalIntegral(double dt, vector<double> f) {
	double trapezoidal_integral = 0;
	for (int i = 0; i < f.size(); i++)
		trapezoidal_integral += f[i] * dt;

	return trapezoidal_integral;
}

double random(double min, double max) {
	return (double)(rand()) / RAND_MAX * (max - min) + min;
}

vector<int> int_to_binary(int a, int count_bit) {
	vector<int> bin;
	do {
		bin.push_back(a % 2);
		a /= 2;
	} while (a > 0);

	while ((bin.size() % count_bit) != 0) {
		bin.push_back(0);
	}
	reverse(bin.begin(), bin.end());

	return bin;
}

vector<int> random_message(int count_bit){
	srand(time(0));
	int rnd = rand();
	vector<int> mess = int_to_binary(rnd, count_bit);

	return mess;
}

vector<int> random_message_to_index_signal(vector<int> message, int count_bit){
	vector<int> mess_indx;
	for (int i = 0; i <= message.size() - count_bit; i += count_bit) {
		int sum = 0;
		for (int j = count_bit - 1, ii = i; j >= 0; j--, ii++) {
			if (message[ii] == 1) sum += pow(2, j);
		}
		mess_indx.push_back(sum);
	}
	
	return mess_indx;
}

vector<int> index_signal_to_message(vector<int> index_s, int count_bit){
	vector<int> mess;
	for (int i = 0; i < index_s.size(); i++){
		vector<int> tmp = int_to_binary(index_s[i], count_bit);
		for (int j = 0; j < tmp.size(); j++)
			mess.push_back(tmp[j]);
	}
	
	return mess;
}

