#include "stdafx.h"
#include "FFT.cpp"
using namespace std;

class FDMConvolver {

	public:
		vector<double> convolve(vector<double> x, vector<double> h) {
			FFT transform;
			int P, origP;
			P = origP = x.size() + h.size() - 1;
			if (!power_of_two(P)) 
				P = pow(2, next_power_of_two(P));

			x= pad(x, P);
			h= pad(h, P);

			vector<ComplexNumber *> xC  = getComplex(x);
			vector<ComplexNumber *> hC  = getComplex(h);

			xC = transform.inplacefft(xC);
			hC = transform.inplacefft(hC);

			vector<ComplexNumber *> result = multiplySignal(xC, hC, P);
			xC.erase(xC.begin(), xC.end());
			hC.erase(hC.begin(), hC.end());

			result = transform.ifft(result);

			vector<double> realResult = getReal(result, origP);

			result.erase(result.begin(), result.end());

			return realResult;
		}

	private:
		vector<double> pad(vector<double> array, int desiredLength) {
			vector<double> result = array;
			int numToAdd = desiredLength - array.size();

			for (int i = 0; i < numToAdd; i++) {
				result.push_back(0.0);
			}

			return result;
		}

		bool power_of_two(int num) {
			return !(num == 0) && !(num && (num - 1));
		}

		int next_power_of_two(int num) {
			return ceil(log2(num));
		}
		vector<ComplexNumber *> multiplySignal(vector<ComplexNumber *> x, vector<ComplexNumber *> h, int size) {
			vector<ComplexNumber *> result = vector<ComplexNumber *>();

			for (int i = 0; i < size; i++) {
				result.push_back(x[i]->multiply(*h[i]));
			}

			return result;
		}

		vector<ComplexNumber *> getComplex(vector<double> real) {
			vector<ComplexNumber *> result = vector<ComplexNumber *>();

			for (int i = 0; i < real.size(); i++) {
				result.push_back(new ComplexNumber(real[i]));
			}
			return result;
		}

		vector<double> getReal(vector<ComplexNumber *> complex, int size) {
			vector<double> result = vector<double>();

			for (int i = 0; i < size; i++) {
				result.push_back(complex[i]->getReal());
			}

			return result;
		}

};