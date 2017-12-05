#include "stdafx.h"
#include <vector>
using namespace std;

class TDMConvolver {


	public: 
		vector<double> convolve(vector<double> x,  vector<double> h) {
			int N = x.size();
			int M = h.size();
			int P = M + N - 1;
			vector<double> y = vector<double>();

			for (int n = 0; n < P; n++) 
				y.push_back(0.0);
				
			for (int n = 0; n < N; n++) {
				for (int m = 0; m < M; m++) {
					y[n + m] += x[n] * h[m];
				}
			}
			return y;
		}
};