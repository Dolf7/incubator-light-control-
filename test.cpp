#include <iostream>
#include "Fuzzy_for_Incubator_Light_Control/fuzzySugeno.h"

using namespace std;

int main(int argc, char** argv){

	float err = 1;
	float delErr = 1;

	fuzzy fuzzy(err, delErr);

	cout << "Error       = \t" << fuzzy.error << endl;
	cout << "Delta Error = \t" << fuzzy.deltaError << endl;
	cout << "OUTPUT      = \t" << fuzzy.pwmOuput << endl;

	fuzzy.testing();

	return 0;
}