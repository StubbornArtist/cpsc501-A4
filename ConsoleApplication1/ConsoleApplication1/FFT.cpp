#include "stdafx.h"
#include "ComplexNumber.cpp"
#include <vector>
#include <math.h>
	
#define PI 3.14159265359
using namespace std;

class FFT {
		

	private:

		int reverse_integer(int num) {
			int temp = num;
			int reverse = 0;
			int size = sizeof(int) * 8;

			for (int i = 0; i < size; i++) {
				reverse <<= 1;
				reverse |= (temp & 1);
				temp >>= 1;
			}

			return reverse;
		}

		int count_leading_zeros(int num) {
			int temp = num;
			int count = 0;
			while (temp >= 0) {
				temp = temp << 1;
				count++;
			}

			return count;
		}


	public:
		vector<ComplexNumber *> fft(vector<ComplexNumber *> x) {
			int n = x.size();

			if (n == 0) throw "Cannot use zero length vector";

			int shift = 1 + count_leading_zeros(n);
			for (int i = 0; i < n; i++) {
				int j = (unsigned int)reverse_integer(i) >> shift;
				if (j > i) {
					ComplexNumber * temp = x[j];
					x[j] = x[i];
					x[i] = temp;
				}
			}

	
			for (int i = 2; i <= n; i = i + i) {
				for (int k = 0; k < (i / 2); k++) {
					double kth = -2.0 * k * PI / i;
					ComplexNumber * wk = new ComplexNumber(cos(kth), sin(kth));
					for (int j = 0; j < (n / i); j++) {
						ComplexNumber * t = wk->multiply(*x[j*i + k + i/2]);
						x[j*i + k + i/2] = x[j * i + k]->subtract(*t);
						x[j*i + k] = x[j * i + k]->add(*t);
					}
				}
			}

			return x;
		}

		vector<ComplexNumber *> ifft(vector<ComplexNumber *> x) {
			int n = x.size();
			vector<ComplexNumber *> y = vector<ComplexNumber *>();

			for (int i = 0; i < n; i++) {
				y.push_back(x[i]->conjugate());
			}

			y = fft(y);
			double inverseN = 1.0 / n;

			for (int i = 0; i < n; i++) {
				ComplexNumber * conj = y[i]->conjugate();
				y[i] = conj->multiply(inverseN);
			}

			return y;
		}

};