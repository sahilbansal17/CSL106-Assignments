//Assignment 4 - 2016CSJ0008,2016CSJ0013
#include <bits/stdc++.h>
using namespace std;

double arrtimegen(double R) {
	double m = 1/R;
	std :: default_random_engine generator;
	std :: uniform_real_distribution<double> distribution(0.0, m);
	double number = distribution(generator);
	return number;
}

double servtimegen(double m, double v) {
	std :: default_random_engine generator;
	std :: uniform_real_distribution<double> distribution(m-v, m+v);
	double number = distribution(generator);
	return number;
}

int main() {

    double R, mu, sigma; //R : arrival rate, mu: mean, sigma: variance of service time
    int k, N; //k: no of billing counters , N : no of customers

    cin >> R >> k >> mu >> sigma >> N;

    return 0;
}