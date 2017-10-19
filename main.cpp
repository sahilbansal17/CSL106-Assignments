//Assignment 4 - 2016CSJ0008,2016CSJ0013
#include <iostream>
#include <random>
using namespace std;

vector<double> arrivalTimeGen(double R, int N) {
    vector<double> temp(N);
	double m = 1/R;
    default_random_engine generator;
    uniform_real_distribution<double> distribution(0.0, m);
    for (int i = 0; i < N; i++) {
        double number = distribution(generator);
        temp[i] = number;
    }
    return temp;
}

double serviceTimeGen(double m, double v) {
    default_random_engine generator;
    uniform_real_distribution<double> distribution(m - v, m + v);
	double number = distribution(generator);
	return number;
}

int main() {

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    double R, mu, sigma; //R : arrival rate, mu: mean, sigma: variance of service time
    int k, N; //k: no of billing counters , N : no of customers

    cin >> R >> k >> mu >> sigma >> N;

    vector<double> arrivalTimeVec(N), t2(N);
    arrivalTimeVec = arrivalTimeGen(R, N);
    t2 = arrivalTimeGen(R, N);
    for (int i = 0; i < N; i++) {
        //arrivalTimeVec[i] = arrivalTimeGen(R);
        cout << arrivalTimeVec[i] << " " << t2[i] << "\n";
    }
    return 0;
}