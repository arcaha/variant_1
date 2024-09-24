#include "QAM_demodulator.h"
#include <cmath>
#include <iostream>


QAM_demodulator::QAM_demodulator(vector<vector<double>> signal_points) { 
	this->signal_points = signal_points; 
}

QAM_demodulator::~QAM_demodulator() {}

int QAM_demodulator::demodulator(vector<double> noisy_signal_points){
	vector<double> dist;
	
	for (int i = 0; i < signal_points.size(); i++)
		dist.push_back(sqrt(pow(noisy_signal_points[0] - signal_points[i][0], 2) + pow(noisy_signal_points[1] - signal_points[i][1], 2)));

	double min = dist[0];
	int min_index = 0;

	for (int i = 1; i < dist.size(); i++) {
		if (dist[i] < min) {
			min = dist[i];
			min_index = i;
		}
	}

	return min_index;
}

