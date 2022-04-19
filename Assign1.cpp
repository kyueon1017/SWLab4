#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

using namespace std;
void showmatrix(int m, int n, float*);
void transpose(int m, int n, float*, float*);
void matrixmult(int m, int n, int k, float*, float*, float*);

int main() {
    float A[6] = { 1, 2, 3, 4, 5, 6 };
    float B[4] = { 1, 2, 3, 4 };
    float c[6];

    showmatrix(2, 3, A);//sprint 1
    showmatrix(3, 2, A);

    matrixmult(3, 2, 2, A, B, c);//sprint 2
    showmatrix(3, 2, c);

    float C[16] = { 0.5, 0.5, 0.5, 0.5,//sprint 3
            0.5, 0.5, -0.5, -0.5,
            0.5, -0.5, -0.5, 0.5,
            0.5, -0.5, 0.5, -0.5 };
    float* c0, * c1, * c2, * c3, delta[16];
    c0 = C;
    c1 = C + 4;
    c2 = C + 8;
    c3 = C + 12;

    matrixmult(1, 4, 1, c0, c1, delta + 1);
    showmatrix(1, 1, delta + 1);

    matrixmult(1, 4, 1, c0, c2, delta + 1);
    showmatrix(1, 1, delta + 1);

    matrixmult(1, 4, 1, c0, c3, delta + 1);
    showmatrix(1, 1, delta + 1);

    matrixmult(1, 4, 1, c1, c2, delta + 1);
    showmatrix(1, 1, delta + 1);

    matrixmult(1, 4, 1, c1, c3, delta + 1);
    showmatrix(1, 1, delta + 1);

    matrixmult(1, 4, 1, c2, c3, delta + 1);
    showmatrix(1, 1, delta + 1);


    float CT[16], I[16];//sprint 4
    transpose(4, 4, C, CT);
    matrixmult(4, 4, 4, CT, C, I);
    showmatrix(4, 4, I);

    float a1[4] = { 100, 120, -4, 2 }; //sprint 5, (a0,a1,a2,a3) = (100, 120, -4, 2) 
    float AA1[4];
    matrixmult(4, 4, 1, C, a1, AA1);
    showmatrix(4, 1, AA1);

    float a2[4] = { 100, 20, 120, 32 }; //sprint 5, (a0,a1,a2,a3) = (100, 20, 120, 32) 
    float AA2[4];
    matrixmult(4, 4, 1, C, a2, AA2);
    showmatrix(4, 1, AA2);

    float a3[4] = { 10, 120, 108, 8 }; //sprint 5, (a0,a1,a2,a3) = (10, 120, 108, 8) 
    float AA3[4];
    matrixmult(4, 4, 1, C, a3, AA3);
    showmatrix(4, 1, AA3);

    float aa1[4];//sprint 6, AA1 = (109, 111, -7, -13)
    matrixmult(4, 4, 1, CT, AA1, aa1);
    showmatrix(4, 1, aa1);

    float aa2[4];//sprint 6, AA2 = (136, -16, -4, 84) 
    matrixmult(4, 4, 1, CT, AA2, aa2);
    showmatrix(4, 1, aa2);

    float aa3[4];//sprint 6, AA3 = (123, 7, -105, -5) 
    matrixmult(4, 4, 1, CT, AA3, aa3);
    showmatrix(4, 1, aa3);


    //sprint 7 - set two smallest |A|'s out of AA to be zeros and do sprint 6 again
    float newAA1[4] = { 109,111,0,0 };
    float newaa1[4];
    matrixmult(4, 4, 1, CT, newAA1, newaa1);
    showmatrix(4, 1, newaa1);

    float newAA2[4] = { 136,0,0,84 };
    float newaa2[4];
    matrixmult(4, 4, 1, CT, newAA2, newaa2);
    showmatrix(4, 1, newaa2);

    float newAA3[4] = { 123,0,-105,0 };
    float newaa3[4];
    matrixmult(4, 4, 1, CT, newAA3, newaa3);
    showmatrix(4, 1, newaa3);


    // sprint 8 - Write 12 values of 3 sets of A[4] on a binary file. 

    ofstream xx("dat1.wav", ios::out | ios::binary);
    if (!xx) {
        cout << " can't open dat.wav \n";
        return 777;
    }
    xx.write((char*)AA1, 4 * sizeof(float));
    xx.close();

    xx.open("dat2.wav", ios::out | ios::binary);
    if (!xx) {
        cout << " can't open dat.wav \n";
        return 777;
    }
    xx.write((char*)AA2, 4 * sizeof(float));
    xx.close();

    xx.open("dat3.wav", ios::out | ios::binary);
    if (!xx) {
        cout << " can't open dat.wav \n";
        return 777;
    }
    xx.write((char*)AA3, 4 * sizeof(float));
    xx.close();

    // sprint9 - ifstream으로 txt file읽기.
    float readAA1[4];
    float readaa1[4];
    ifstream yy("dat1.wav", ios::in | ios::binary);
    if (!yy) {
        cout << " can't open dat.bin \n";
        return 666;
    }
    yy.read((char*)readAA1, 4 * sizeof(float));
    yy.close();
    matrixmult(4, 4, 1, CT, readAA1, readaa1);
    showmatrix(4, 1, readaa1);


    float readAA2[4];
    float readaa2[4];
    yy.open("dat2.wav", ios::in | ios::binary);
    if (!yy) {
        cout << " can't open dat.bin \n";
        return 666;
    }
    yy.read((char*)readAA2, 4 * sizeof(float));
    yy.close();
    matrixmult(4, 4, 1, CT, readAA2, readaa2);
    showmatrix(4, 1, readaa2);

    float readAA3[4];
    float readaa3[4];
    yy.open("dat3.wav", ios::in | ios::binary);
    if (!yy) {
        cout << " can't open dat.bin \n";
        return 666;
    }
    yy.read((char*)readAA3, 4 * sizeof(float));
    yy.close();
    matrixmult(4, 4, 1, CT, readAA3, readaa3);
    showmatrix(4, 1, readaa3);

    return 0;



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
void matrixmult(int M, int N, int K, float* a, float* b, float* c) {
    for (int m = 0; m < M; m++) {
        for (int k = 0; k < K; k++) {
            float sum = 0;
            for (int n = 0; n < N; n++) sum += a[m * N + n] * b[n * K + k];
            c[m * K + k] = sum;
        }
    }
}