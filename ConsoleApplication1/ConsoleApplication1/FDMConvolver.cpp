#include "stdafx.h"
#include "FFT.cpp"
using namespace std;

class FDMConvolver {

	public:
		void convolve(vector<double> x, vector<double> h, vector<double> * y){
			FFT transform;
			int P, origP;
			vector<ComplexNumber *> xC, hC;

			P = origP = x.size() + h.size() - 1;
			if (!power_of_two(P)) 
				P = pow(2, next_power_of_two(P));

			pad(&x, P);
			pad(&h, P);

			getComplex(x, &xC);
			getComplex(h, &hC);

			transform.fft(&xC);
			transform.fft(&hC);

			multiplySignals(&xC, hC);
			transform.ifft(&xC);
			getReal(xC, y, origP);

			xC.erase(xC.begin(), xC.end());
			hC.erase(hC.begin(), hC.end());
		}

	private:
		void pad(vector<double> * array, int desiredLength) {
			int numToAdd;
			numToAdd = desiredLength - array->size();
			for (int i = 0; i < numToAdd; i++) {
				array->push_back(0.0);
			}
		}

		bool power_of_two(int num) {
			return !(num == 0) && !(num && (num - 1));
		}

		int next_power_of_two(int num) {
			return ceil(log2(num));
		}
		void multiplySignals(vector<ComplexNumber *> * x, vector<ComplexNumber *> h) {
			int n = x->size();

			for (int i = 0; i < n; i++) {
				ComplexNumber * temp = (*x)[i];
				(*x)[i] = temp->multiply(*h[i]);
				delete temp;
			}
		}

		void getComplex(vector<double> real, vector<ComplexNumber *> * complex) {

			for (int i = 0; i < real.size(); i++) {
				complex->push_back(new ComplexNumber(real[i]));
			}
		}

		void getReal(vector<ComplexNumber *> complex, vector<double> * real, int size) {
			for (int i = 0; i < size; i++) {
				real->push_back(complex[i]->getReal());
			}
		}

};