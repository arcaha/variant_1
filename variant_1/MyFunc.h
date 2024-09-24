#ifndef MyFunc_h
#define MyFunc_h
#include <ctime>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

double trapezoidalIntegral(double dt, vector<double> f);
double random(double min, double max);
vector<int> int_to_binary(int a, int count_bit);
vector<int> random_message(int count_bit);
vector<int> random_message_to_index_signal(vector<int> message, int count_bit);
vector<int> index_signal_to_message(vector<int> index_s, int count_bit);

#endif 
