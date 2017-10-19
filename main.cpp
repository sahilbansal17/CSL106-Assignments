//Assignment 4 - 2016CSJ0008,2016CSJ0013
#include <iostream>
#include <random>

using namespace std;

vector<double> arrivalTimeGen(double R, int N) {
    vector<double> temp(N);
    double m = 1 / R;
    random_device rd; //non-deterministic engine, to seed mt engine
    mt19937 gen(rd()); //mersenne-twister engine
    uniform_real_distribution<double> distribution(0.0, m); //uniform distribution
    for (int i = 0; i < N; i++) {
        double number = distribution(gen);
        temp[i] = number;
    }
    return temp;
}

double serviceTimeGen(double m, double v) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> distribution(m - v, m + v);
    double number = distribution(gen);
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

    vector<double> arrivalTimeVec(N);
    arrivalTimeVec = arrivalTimeGen(R, N);
    for (int i = 0; i < N; i++) {
        cout << arrivalTimeVec[i] << " ";
    }
    // TESTING THE SERVICE TIME GENERATION FUNCTION
    /*
    cout << "\n";
    for(int i = 0 ; i < N; i++){
    	cout << serviceTimeGen(mu,sigma) << " ";
    }
    */
    return 0;
}