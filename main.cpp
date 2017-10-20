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

    Customer(Customer &c1) {
        queueNo = c1.queueNo;
        arrivalTime = c1.arrivalTime;
        departureTime = c1.departureTime;
    }

    Customer() {
        queueNo = 0;
        arrivalTime = 0;
        departureTime = 0;
    }
};

class Counter {
public:
    int id; 
    int noOfCustomers;
    double ccDepTime; //departure time of its current customer
    Counter(Counter &c1) {
        id = c1.id;
        noOfCustomers = c1.noOfCustomers;
        ccDepTime = c1.ccDepTime;
    }

    Counter() {
        id = 0;
        noOfCustomers = 0;
        ccDepTime = 0;
    }
};

//heap 2 - customers   
class H2 {
private:
    int size; // the current no of customers yet to be served
    Customer *customers;
public:
    H2(int N) {
        customers = new Customer[N]; //at most there can be N customers in the shop
        for (int i = 0; i < N; i++) {
            customers[i].queueNo = 0;
            customers[i].arrivalTime = 0;
            customers[i].departureTime = 0;
        }
        size = 0; //since there are no customers initially
    }

    void display(int N) {
        for (int i = 0; i < N; i++) {
            cout << customers[i].queueNo << " " << customers[i].arrivalTime << " " << customers[i].departureTime
                 << "\n";
        }
    }
};

//heap 1 - counters
class H1 {
private:
    Counter *counters;
    int size;

    int leftChild(int i) {
        int left = 2 * i + 1;
        if (left >= size)
            return -1;
        return left;
    }

    int rightChild(int i) {
        int right = 2 * i + 2;
        if (right >= size) {
            return -1;
        }
        return right;
    }

    void heapify(int loc) {
        Counter temp;
        int l, r, max;
        l = leftChild(loc);
        r = rightChild(loc);
        if (l != -1 && counters[l].noOfCustomers > counters[loc].noOfCustomers) {
            max = l;
        } else {
            max = loc;
        }
        if (r != -1 && counters[r].noOfCustomers > counters[loc].noOfCustomers) {
            max = r;
        }
        if (max != loc) {
            //swap counters[loc] with counters[max]
            temp = counters[loc];
            counters[loc] = counters[max];
            counters[max] = temp;
        }
        heapify(max);
        return;
    }
public:
    H1(int k) {
        size = k;
        counters = new Counter[k];
        for (int i = 0; i < k; i++) {
            counters[i].noOfCustomers = 0;
            counters[i].ccDepTime = 0;
            counters[i].id = i; //assign a unique id to each counter
        }
    }

    void display(int k) {
        for (int i = 0; i < k; i++) {
            cout << counters[i].noOfCustomers << " " << counters[i].ccDepTime << "\n";
        }
    }

    void insert(double arrival, double service) {
        //if there is no customer in the queue
        if (counters[0].noOfCustomers == 0) {
            counters[0].noOfCustomers++;
            counters[0].ccDepTime = arrival + service;
            //heapify the counters heap based on the no of customers
            heapify(0);
        }
            //else if there are customers in the queue, then the 0th location will contain the counter which has the least no of customers
        else {
            counters[0].noOfCustomers++;
            counters[0].ccDepTime = counters[0].ccDepTime +
                                    service; //might need to store the departure time of all the customers in the queue
            //heapify the counters heap
            heapify(0);
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

    for (int i = 0; i < N; i++) {
        cout << serviceTimeVec[i] << " ";
    }
    cout << "\n";
    H1 heap1(k);
    //heap1.display(k);

    H2 heap2(N);
    //heap2.display(N);

    double clock = 0;
    int currentLoc = 0;
    /*while(clock != -1){
        clock+= arrivalTimeVec[currentLoc];
        heap1.insert(clock, serviceTimeVec[currentLoc]);
    }*/
    return 0;
}