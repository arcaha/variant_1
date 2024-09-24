#define _USE_MATH_DEFINES
#include "QAM_modulator.h"

using namespace std;

QAM_modulator::QAM_modulator(int V_mod, int V_inf, int f0, int A) {

		this->V_mod = V_mod; 
		this->V_inf = V_inf; 
		this->f0 = f0;
		this->A = A;
		this->q = pow(2, (V_inf / V_mod)); 
		this->T = (double)1 / V_mod;
		this->dt = (double)1 / (f0 * Ns);
		E_sr = new double[q];
		modulator();
}

QAM_modulator::~QAM_modulator() { delete[] E_sr; }

int QAM_modulator::Get_V_mod(){ return V_mod;}

int QAM_modulator::Get_V_inf(){ return V_inf;}

int QAM_modulator::Get_f_0(){return f0; }

int QAM_modulator::Get_A(){ return A; }

void QAM_modulator::modulator(){

	double si1 = 0, si2 = 0;
	int num_signal = 0;
	int i1_ = 0, i2_ = 0;
	for(int i = 0; i < q; i++)
		signals.push_back(vector<double>());

	for (int i1 = 0; i1 < sqrt(q); i1++) {
		for (int i2 = 0; i2 < sqrt(q); i2++) {
			i1_ = i1 ^ (i1 >> 1);
			i2_ = i2 ^ (i2 >> 1);
			num_signal = i1_ * sqrt(q) + i2_;
			si1 = A * (1.0 - (2.0 * i1) / (sqrt(q) - 1.0));
			si2 = A * (1.0 - (2.0 * i2) / (sqrt(q) - 1.0));
			for (double t = 0; t < T; t += dt)
				signals[num_signal].push_back((si1 * sqrt(2.0 / T) * cos(2.0 * M_PI * (double)f0 * t)) + (si2 * sqrt(2.0 / T) * sin(2.0 * M_PI * (double)f0 * t)));
		}
	}
	
	for (double t = 0; t < T; t += dt) {
		fi_1.push_back(sqrt(2.0 / T) * cos(2.0 * M_PI * (double)f0 * t));
		fi_2.push_back(sqrt(2.0 / T) * sin(2.0 * M_PI * (double)f0 * t));
	}

	for (int i = 0; i < q; i++) {
		double E = 0;
		vector<double> signal_fi_1;
		vector<double> signal_fi_2;
		signal_points.push_back(vector<double>());
		for (int j = 0; j < signals[i].size(); j++) {
			E += pow(signals[i][j], 2);
			signal_fi_1.push_back(signals[i][j] * fi_1[j]);
			signal_fi_2.push_back(signals[i][j] * fi_2[j]);
		}
		
		E_sr[i] = E  / q;
		
		signal_points[i].push_back(trapezoidalIntegral(dt, signal_fi_1));
		signal_points[i].push_back(trapezoidalIntegral(dt, signal_fi_2));

	}
}

int QAM_modulator::Get_q(){ return q; }

double QAM_modulator::Get_T(){ return T; }

double QAM_modulator::Get_dt(){ return dt; }

int QAM_modulator::Get_count_bit(){ return V_inf / V_mod; }

double* QAM_modulator::Get_E_sr(){ return E_sr; }

vector<vector<double>> QAM_modulator::Get_signals(){ return signals;}

vector<double> QAM_modulator::Get_signal_an_index(int index){ 
	if (index >= 0 && index < q) return signals[index];
	else throw "Going beyond the signal array";
 }

vector<vector<double>> QAM_modulator::Get_signal_points(){ return signal_points;}

vector<double> QAM_modulator::Get_fi_1(){ return fi_1; }

vector<double> QAM_modulator::Get_fi_2(){ return fi_2; }
