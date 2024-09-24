#ifndef QAM_demodulator_h
#define QAM_demodulator_h
#include <vector>

using namespace std;

class QAM_demodulator {
private:
	vector<vector<double>> signal_points;
public:
	QAM_demodulator(vector<vector<double>> signal_points);
	~QAM_demodulator();
	int demodulator(vector<double> noisy_signal_points);
};
#endif