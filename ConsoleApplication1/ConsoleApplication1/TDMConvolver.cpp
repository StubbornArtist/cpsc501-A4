#include <vector>
using namespace std;

class TDMConvolver {


	public: 
		void convolve(vector<double> x,  vector<double> h, vector<double> * y) {
			int N = x.size();
			int M = h.size();
			int P = M + N - 1;

			for (int n = 0; n < P; n++) 
				y->push_back(0.0);
				
			for (int n = 0; n < N; n++) {
				for (int m = 0; m < M; m++) {
					(*y)[n + m] += x[n] * h[m];
				}
			}
		}
};