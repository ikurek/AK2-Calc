#ifndef RNS_MULTIPLY_CONVERSIONS_H
#define RNS_MULTIPLY_CONVERSIONS_H

#include <vector>

using namespace std;

static class Conversions {
public:
    static vector<long> machineValueToRNS(unsigned long long  machineValue, vector<long> modules);

    static long long decimalToMachineValue(float number, long fractionalPartLength, vector<long> modules);
	static unsigned long long truncatedMRN(unsigned long long MRNnumber, long fractionalPartLength, vector<long> modules);


	//static vector<long> findDecimalParameters(vector<long> modules);
	static double RNStoDec(vector<long> rnsNum, int fractionalPartLength, vector<long> modules);
};


#endif //RNS_MULTIPLY_CONVERSIONS_H
