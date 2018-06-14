	#include "MRNMultiply.h"
#include <vector>
// Works
vector<long>
MRNMultiply::calculateIntermediateProduct(vector<long> xRNS, vector<long> yRNS, vector<long> modulesReversed) {
    vector<long> result;

    // iterate over all reversed modules
    for (long i = 0; i < modulesReversed.size(); ++i) {
        // Calculate value of current position in intermediate product
        long value = (xRNS[i] * yRNS[i]) % modulesReversed[i];
        result.push_back(value);
    }
    return result;
}

// FIXME: Overflow passes 64bit long long value i = 5
unsigned long long MRNMultiply::findModulesProduct(vector<long> modules, long end) {
    long long result = modules[0];
	//do 4
    for (long i = 1; i < end; ++i) {
        result = result * modules[i];
    }
    return result;
}

// Works
long MRNMultiply::findXParameterForMRNConversion(long pi, long pn) {
    long x = 0;
    while (((pi * x) % pn) != 1) {
        x++;
    }
    return x;
}

// FIXME: Errors inside
vector<long> MRNMultiply::calculateRNStoMRNConversionParameters(vector<long> modules,
                                                                vector<long> intermediateProductReversed) {
    vector<long> result;
    cout << endl;
    cout << "MRN Conversion Parameters:" << endl;
	
	// 1st parameter is the same as last value of intermediate product
    result.push_back(intermediateProductReversed[0]);
	
	// Print 1st param info
    cout << "    ==> A0: " << result[0] << endl;
    cout << "        ==> Modulus Product: " << 0 << endl;
    cout << "        ==> X Parameter: " << 0 << endl;
    cout << "        ==> First Formula Part: " << 0 << endl;
    cout << "        ==> Second Formula Part: " << 0 << endl;
    cout << "        ==> Third Formula Part: " << 0 << endl;
    cout << "        ==> Fourth Formula Part: " << 0 << endl;
    cout << "        ==> Value: " << result[0] << endl;

	// Iterate over all modules, skipping 1st position
    // Searching for parameter for each position of RNS number (intermediate product)
    for (long i = 1; i < modules.size(); ++i) {

        // Variables for single iteration of A
		unsigned long long currentModulusProduct = modules[0];
        long currentXParameter = 0;
        long formulaFirstPart = 0;
        long formulaSecondPart = 0;
        long formulaThirdPart = 0;
        long formulaFourthPart = 0;
				
			if (i == 1) {
				currentXParameter = findXParameterForMRNConversion(modules[0], modules[i]);
				formulaFirstPart = findXParameterForMRNConversion(modules[0], modules[i]);
			}
			else {
				currentModulusProduct = findModulesProduct(modules, i);
				currentXParameter = findXParameterForMRNConversion(currentModulusProduct, modules[i]);
				formulaFirstPart = currentXParameter;
			}

	
		// Calculating second part of formula
        formulaSecondPart = formulaFirstPart % modules[i];

        // Calculate third part of formula
        formulaThirdPart = 1;
        for (int j =1; j < i; ++j) {
			formulaThirdPart = formulaThirdPart*(result[j] * modules[j - 1]);
		}
		formulaThirdPart += result[0];
        // Calculate fourth part
        formulaFourthPart = intermediateProductReversed[i] - formulaThirdPart;

        // Calculate final value of current A
		long value = (modules[i] >= 0 ? modules[i] : -modules[i]) - 1 + (formulaSecondPart * formulaFourthPart + 1) % modules[i];
        // Save value	
        result.push_back(value);


        // Print information of current A calculations
        cout << "    ==> A" << i << ": " << endl;
        cout << "        ==> Modulus Product: " << currentModulusProduct << endl;
        cout << "        ==> X Parameter: " << currentXParameter << endl;
        cout << "        ==> First Formula Part: " << formulaFirstPart << endl;
        cout << "        ==> Second Formula Part: " << formulaSecondPart << endl;
        cout << "        ==> Third Formula Part: " << formulaThirdPart << endl;
        cout << "        ==> Fourth Formula Part: " << formulaFourthPart << endl;
        cout << "        ==> Value: " << value << endl;

    }
    return result;
}
long long MRNMultiply::calculateMRNnumber(vector<long> modules, vector<long> intermediateProduct, vector<long> mrnConversionParameters) {

	unsigned long long MRNnumber = mrnConversionParameters[0];
	unsigned long long currentModProduct = modules[0];
	for (size_t i = 1; i < modules.size(); i++)
	{
		currentModProduct = findModulesProduct(modules, i);
		cout << " curModProduct: "<<currentModProduct << "; i= " << i<<endl;

		MRNnumber += mrnConversionParameters[i] * currentModProduct;
	}
	cout << endl;
	return MRNnumber;
};


