#include "modeling.h"

void start_the_simulation(){
	cout << "Parameters for QAM" << endl;
	int v_mod, v_inf, f, a;
	cout << "Information rate = ";
	cin >> v_inf;
	cout << "Modulation rate = ";
	cin >> v_mod;
	cout << "The central frequency = ";
	cin >> f;
	cout << "The amplitude = ";
	cin >> a;
	if (v_mod <= 0 || v_inf <= 0 || a <= 0 || floor(v_inf / v_mod) != (v_inf / v_mod) || (v_inf / v_mod) % 2 != 0) throw  "Non-correct data for QAM";
	
	QAM_modulator signals_QAM(v_mod, v_inf, f, a);
	QAM_demodulator demod_QAM(signals_QAM.Get_signal_points());

	cout << "Parameters for noise" << endl;
	int str, fin, stp;
	cout << "The initial value of the SNR = ";
	cin >> str;
	cout << "The final value of the SNR = ";
	cin >> fin;
	cout << "Step SNR = ";
	cin >> stp;
	if (stp <= 0 || str < 0 || fin < 0) throw "Non-correct data for noise";
	AWGN noise(str, fin, stp, signals_QAM.Get_q(), signals_QAM.Get_E_sr());

	cout << "The maximum number of errors in the simulation = ";
	int max_error;
	cin >> max_error;
	//int max_error = 10000 * signals_QAM.Get_q();
	ofstream txt;
	string name = "graph/QAM_";
	string q_ = to_string(signals_QAM.Get_q());
	string file = ".txt";
	txt.open(name + q_ + file);

	int i = 0;
	for (; i < noise.Get_size_SNR(); i++) {
		int count_trans_bits = 0;
		int error_trans_bits = 0;
		double Pe_bit = 0;
		while (max_error > error_trans_bits) {
			vector<int> message = random_message(signals_QAM.Get_count_bit()),
				message_indx = random_message_to_index_signal(message, signals_QAM.Get_count_bit()),
				message_indx_demod, message_demod;
			
			count_trans_bits += message.size();

			for (int j = 0; j < message_indx.size(); j++)
				message_indx_demod.push_back(demod_QAM.demodulator(

					noise.apply_noise(signals_QAM.Get_signal_an_index(message_indx[j]),

					signals_QAM.Get_q(), signals_QAM.Get_fi_1(), signals_QAM.Get_fi_2(), 

				    i, signals_QAM.Get_dt())));

			message_demod = index_signal_to_message(message_indx_demod, signals_QAM.Get_count_bit());
			
			for (int j = 0; j < message.size(); j++)
				if (message[j] != message_demod[j]) error_trans_bits++;
		}
		Pe_bit = (double) error_trans_bits / (double) count_trans_bits;
		cout << noise.Get_sigma_index(i) << " " << Pe_bit << endl;
		
		txt <<  noise.Get_sigma_index(i) << " "  << Pe_bit << endl;
	}
	txt.close();
}
