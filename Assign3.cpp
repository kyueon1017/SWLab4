#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;
// 참고 사이트
// https://www.researchgate.net/figure/walsh-matrix-of-order-8_fig2_271134339
// 크기 반환. 

float amp(float* a) {
	float sum = 0, A;

	for (int i = 0; i < 8; i++) {
		sum += a[i] * a[i];
	}
	A = sqrt(sum);

	return A;
}

void transpose(int m, int n, float* a, float* at) {
	int ii = 0;
	for (int i = 0; i < m; i++, ii += n) {
		for (int j = 0; j < n; j++) {
			at[j * m + i] = a[ii + j];
		}
	}
}
void showmatrix(int m, int n, float* a) {
	cout << " matrix \n";
	int ii = 0;
	for (int i = 0; i < m; i++, ii += n) {
		for (int j = 0; j < n; j++)    cout << setw(8) << a[ii + j];
		cout << endl;
	}
}

// i8
void normmatrix(int m, int n, float* a) {
	cout << " normmatrix \n";
	int ii = 0;
	for (int i = 0; i < m; i++, ii += n) {
		for (int j = 0; j < n; j++)    cout << setw(8) << a[ii + j] / amp(a);
		cout << endl;
	}
}

// 행렬 곱하기. 
void matrixmult(int M, int N, int K, float* a, float* b, float* c) {
	for (int m = 0; m < M; m++) {
		for (int k = 0; k < K; k++) {
			float sum = 0;
			for (int n = 0; n < N; n++) sum += a[m * N + n] * b[n * K + k];
			c[m * K + k] = sum;
		}
	}
}


int main() {

	// assignment3 : 8*8 matrix
	float c[64] = { 1, 1, 1, 1, 1, 1, 1, 1,
			  1, 1, 1, 1, -1, -1, -1, -1,
			  1, 1, -1, -1, -1, -1, 1, 1,
			  1, 1, -1, -1, 1, 1, -1, -1, // c3
			  1, -1, -1, 1, 1, -1, -1, 1, // c4
			  1, -1, -1, 1, -1, 1, 1, -1,  //c5
			  1, -1, 1, -1, -1, 1, -1, 1, //c6
			  1, -1, 1, -1, 1, -1, 1, -1, //c7
	};

	// ct , i
	float ct[64], i[64];
	transpose(8, 8, c, ct);
	matrixmult(8, 8, 8, ct, c, i);
	showmatrix(8, 8, i);
	normmatrix(8, 8, i);


	float* c0, * c1, * c2, * c3, * c4, * c5, * c6, * c7, delta[64];
	c0 = c;
	c1 = c + 8;
	c2 = c + 16;
	c3 = c + 24;

	c4 = c + 32;
	c5 = c + 40;
	c6 = c + 48;
	c7 = c + 56;

	// c0 , c1
	matrixmult(1, 8, 1, c0, c1, delta + 1);
	showmatrix(1, 1, delta + 1);

	// c0 , c2
	matrixmult(1, 8, 1, c0, c2, delta + 1);
	showmatrix(1, 1, delta + 1);

	// c0 , c3
	matrixmult(1, 8, 1, c0, c3, delta + 1);
	showmatrix(1, 1, delta + 1);

	// c1 , c2
	matrixmult(1, 8, 1, c1, c2, delta + 1);
	showmatrix(1, 1, delta + 1);

	// c1 , c3
	matrixmult(1, 8, 1, c1, c3, delta + 1);
	showmatrix(1, 1, delta + 1);

	// c2, c3
	matrixmult(1, 8, 1, c2, c3, delta + 1);
	showmatrix(1, 1, delta + 1);

	// 정상 출력 확인. 
	for (int i = 0; i < 8; i++) {
		cout << c1[i] << endl;
	}

	// c1 크기. 
	cout << amp(c1) << endl;

	// c*ct = i


}
