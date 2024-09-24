#ifndef QAM_modulator_h
#define QAM_modulator_h
#include <vector>     
#include "MyFunc.h"

using namespace std;

class QAM_modulator {
private:
	int V_mod;
	int V_inf;
	int f0;
	int A;
	int q;
	double T;
	double* E_sr;
	int Ns = 12;
	double dt;
	vector<vector<double>> signals;
	vector<vector<double>> signal_points;
	vector<double> fi_1;
	vector<double> fi_2;
	void modulator();
	
public:

	QAM_modulator(int V_mod, int V_inf, int f0, int A);
	~QAM_modulator();

	int Get_V_mod();
	int Get_V_inf();
	int Get_f_0();
	int Get_A();
	int Get_q();
	double Get_T();
	double Get_dt();
	int Get_count_bit();
	double* Get_E_sr();
	
	vector< vector<double> > Get_signals();
	vector<double> Get_signal_an_index(int index);
	vector< vector<double> > Get_signal_points();
	vector<double> Get_fi_1();
	vector<double> Get_fi_2();
	
};
#endif 

