#include "stdafx.h"
#include "ComplexNumber.cpp"
#include <vector>
#include <math.h>
//#include <intrin.h> 
	
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

		int count_trailing_zeros(int num) {
			int size = sizeof(num) * 8;
			int temp = num;
			for (int i = 0;  i < size; i++, temp = temp >> 1) {
				if (temp & 1) {
					return i;
				}
			}
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
		vector<ComplexNumber *>  fft(vector<ComplexNumber *> x) {
			int n = x.size();

			if (n == 1) return vector<ComplexNumber *>{ x[0] };

			vector<ComplexNumber *> even = vector<ComplexNumber *>();
			vector<ComplexNumber *> odd = vector<ComplexNumber *>();
			vector<ComplexNumber *> combined = vector<ComplexNumber *>(n, 0);

			for (int i = 0; i < n; i+=2) {
				even.push_back(x[i]);
				odd.push_back(x[i + 1]);
			}

			even = fft(even);
			odd = fft(odd);

			for (int i = 0; i < (n/2); i++) {
				double k = -2.0 * i *  PI / n;
				ComplexNumber * wk = new ComplexNumber(cos(k), sin(k));
				wk = wk->multiply(*odd[i]);
				combined[i] = even[i]->add(*wk);
				combined[i + (n/2)] = (even[i]->subtract(*wk));
				delete wk;
			}

			return combined;
		}

		vector<ComplexNumber *> inplacefft(vector<ComplexNumber *> x) {
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

			y = inplacefft(y);
			double inverseN = 1.0 / n;

			for (int i = 0; i < n; i++) {
				ComplexNumber * conj = y[i]->conjugate();
				y[i] = conj->multiply(inverseN);
			}

			return y;
		}

};