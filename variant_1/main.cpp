#include "modeling.h"
using namespace std;

int main() {
	try {
		start_the_simulation();
	}
	catch (const char* error_message) {
		cout << error_message << endl;
	}
	return 0;
}