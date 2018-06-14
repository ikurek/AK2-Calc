#include <iostream>
#include "Conversions.h"
#include "MRNMultiply.h"

// Works
vector<long> Conversions::machineValueToRNS(unsigned long long machineValue, vector<long> modules) {
    vector<long> result;

    for (auto module: modules) {
        result.push_back(machineValue % module);
    }

    reverse(result.begin(), result.end());

    return result;
}

long long Conversions::decimalToMachineValue(float number, long fractionalPartLength, vector<long> modules) {
    long long moduleProduct = 1;

    for (int i = 0; i < fractionalPartLength; ++i) {
        moduleProduct = moduleProduct * modules[i];
    }

    long long result = number * moduleProduct;

    return result;
}

unsigned long long Conversions::truncatedMRN(unsigned long long mrnNumber, long fractionalPartLength, vector<long> modules) {
	long long moduleProduct = 1;
	for (int i = 0; i < fractionalPartLength; ++i) {
		moduleProduct = moduleProduct * modules[i];
	}
	long long result = mrnNumber / moduleProduct;
	return result;
}

double Conversions::RNStoDec(vector<long> rnsNum, int fractionalPartLength, vector<long> modules) {
	unsigned long long allModProduct = MRNMultiply::findModulesProduct(modules, modules.size());
	cout << "\n Big M: " << allModProduct << endl;
	vector<long> paramM;
	vector<long> paramB;
	long param;
	for (int i = 0; i < modules.size(); ++i) {
		paramM.push_back(allModProduct / modules[i]);
		param = MRNMultiply::findXParameterForMRNConversion(paramM[i], modules[i]);
		paramB.push_back(param);
	}	
	
	long long sum;
	for (int i = 0; i < modules.size(); ++i) {
		sum += rnsNum[i] * paramB[i] * paramM[i];
	}
	sum %=allModProduct;

	//find Rf - float modulo range
	long long moduleProduct = 1;
	for (int i = 0; i < fractionalPartLength; ++i) {
		moduleProduct *= modules[i];
	}
	
	double result = (double)sum / moduleProduct;
	return result;

}
