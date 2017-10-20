//Assignment 4 - 2016CSJ0008,2016CSJ0013
#include <iostream>
#include <vector>
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

vector<double> serviceTimeGen(double m, double v, int N) {
    vector<double> temp(N);
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> distribution(m - v, m + v);
    for (int i = 0; i < N; i++) {
        double number = distribution(gen);
        temp[i] = number;
    }
    return temp;
}

class Customer {
public:
    int queueNo;
    double arrivalTime;
    double departureTime;
};

class Counter {
public:
    int noOfCustomers;
    double ccDepTime; //departure time of its current customer
};

//heap 2 - customers   
class H2 {

};

//heap 1 - counters
class H1 {
private:
    Counter *counters;
public:
    H1(int k) {
        counters = new Counter[k];
        for (int i = 0; i < k; i++) {
            counters[i].noOfCustomers = 0;
            counters[i].ccDepTime = 0;
        }
    }

    void display(int k) {
        for (int i = 0; i < k; i++) {
            cout << counters[i].noOfCustomers << " " << counters[i].ccDepTime << "\n";
        }
    }
};

int main() {

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    double R, mu, sigma; //R : arrival rate, mu: mean, sigma: variance of service time
    int k, N; //k: no of billing counters , N : no of customers

    cin >> R >> mu >> sigma >> k >> N;

    vector<double> arrivalTimeVec(N), serviceTimeVec(N);
    //arrivalTimeVec = arrivalTimeGen(R, N);
    //assuming that the arrival rate is fixed - for time being, can be changed later 
    double arrTime = 0;
    for (int i = 0; i < N; i++) {
        arrivalTimeVec[i] = arrTime;
        arrTime += R;
    }

    for (int i = 0; i < N; i++) {
        cout << arrivalTimeVec[i] << " ";
    }
    cout << "\n";
    serviceTimeVec = serviceTimeGen(mu, sigma, N); //service time vector

    H1 heap1(k);
    heap1.display(k);

    return 0;
}