#include "stdafx.h"
#include "ComplexNumber.cpp"
#include <vector>
#include <math.h>
	
#define PI 3.14159265359
using namespace std;

class FFT {
		

	private:

		int reverse_integer(int num) {
			int temp, reverse, size;
			temp = num;
			reverse = 0;
			size = sizeof(int) * 8;

			for (int i = 0; i < size; i++) {
				reverse <<= 1;
				reverse |= (temp & 1);
				temp >>= 1;
			}
			return reverse;
		}

		int count_leading_zeros(int num) {
			int temp, count;
			temp = num;
			count = 0;
			while (temp > 0) {
				temp = temp >> 1;
				count++;
			}
			return (sizeof(int) * 8 )-count;
		}


	public:
		void fft(vector<ComplexNumber *> * x) {
			int n, shift;
			ComplexNumber * temp;
			ComplexNumber * temp2;
			double kth;
			n= x->size();

			shift = 1 + count_leading_zeros(n);
			for (int i = 0; i < n; i++) {
				unsigned int j = (unsigned int)reverse_integer(i) >> shift;
				if (j > i) {
					temp = (*x)[j];
					(*x)[j] = (*x)[i];
					(*x)[i] = temp;
				}
			}
	
			for (int i = 2; i <= n; i = i + i) {
				for (int k = 0; k < (i / 2); k++) {
					kth = -2.0 * k * PI / i;
					ComplexNumber * wk = new ComplexNumber(cos(kth), sin(kth));
					for (int j = 0; j < (n / i); j++) {
						temp = wk->multiply(*(*x)[j*i + k + i/2]);
						delete (*x)[j*i + k + i / 2];
						(*x)[j*i + k + i / 2] = (*x)[j * i + k]->subtract(*temp);
						temp2 = (*x)[j*i + k];
						(*x)[j*i + k] = (*x)[j * i + k]->add(*temp);
						delete temp2;
						delete temp;
					}
					delete wk;
				}
			}

		}

		void ifft(vector<ComplexNumber *> * x) {
			int n;
			double inverseN;

			n = x->size();
			inverseN = 1.0 / n;

			for (int i = 0; i < n; i++) {
				ComplexNumber * temp = (*x)[i];
				(*x)[i] = temp->conjugate();
				delete temp;
			}

			fft(x);

			for (int i = 0; i < n; i++) {
				ComplexNumber * temp = (*x)[i];
				ComplexNumber * conj = (*x)[i]->conjugate();
				(*x)[i] = conj->multiply(inverseN);
				delete temp;
				delete conj;
			}

		}

		~FFT(){}
};