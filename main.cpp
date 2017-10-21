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
    int id; 
    int noOfCustomers;
    double ccDepTime; //departure time of its current customer
};

//heap 2 - customers   
class H2 {
private:
    int size; // the current no of customers yet to be served
    Customer *customers;

    int leftChild(int i) {
        int left = 2 * i + 1;
        if (left >= size) {
            return -1;
        }
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
        Customer temp;
        int l, r, min;
        l = leftChild(loc);
        r = rightChild(loc);
        if (l != -1 && customers[l].departureTime < customers[loc].departureTime) {
            min = l;
        } else {
            min = loc;
        }
        if (r != -1 && customers[r].departureTime < customers[min].departureTime) {
            min = r;
        }
        if (min != loc) {
            //swap the customers[min] with customers[loc]
            temp = customers[min];
            customers[min] = customers[loc];
            customers[loc] = temp;
            heapify(min);
        }
        return;
    }
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

    void insert(Customer c) {
        size++;
        int index = size - 1;
        //parent is at (index-1)/2 since starting from 0th index
        while (index > 0 && c.departureTime < customers[(index - 1) / 2].departureTime) {
            customers[index] = customers[(index - 1) / 2];
            index = (index - 1) / 2;
        }
        customers[index] = c; //right position for this customer 
    }

    double topCustomerDepTime() {
        return customers[0].departureTime;
    }

    double topCustomerQueueNo() {
        return customers[0].queueNo;
    }

    void deleteMin() {
        if (size == 0) { //no customer can be deleted
            customers[0].departureTime = 0;
            customers[0].arrivalTime = 0;
            customers[0].queueNo = 0;
            return;
        }
        customers[0] = customers[size - 1];
        customers[size - 1].departureTime = 0;
        customers[size - 1].arrivalTime = 0;
        customers[size - 1].queueNo = 0;
        size--;
        //call heapify 
        heapify(0);
        return;
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
        int l, r, min;
        l = leftChild(loc);
        r = rightChild(loc);
        if (l != -1 && counters[l].noOfCustomers < counters[loc].noOfCustomers) {
            min = l;
        } else {
            min = loc;
        }
        if (r != -1 && counters[r].noOfCustomers < counters[min].noOfCustomers) {
            min = r;
        }
        if (min != loc) {
            //swap counters[loc] with counters[min]
            temp = counters[loc];
            counters[loc] = counters[min];
            counters[min] = temp;
            heapify(min);
        }
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
            cout << counters[i].id << " " << counters[i].noOfCustomers << " " << counters[i].ccDepTime << "\n";
        }
    }

    Customer insert(double arrival, double service) {
        int Q_NO = counters[0].id; //counter no
        double depT;
        //if there is no customer in the queue
        if (counters[0].noOfCustomers == 0) {
            counters[0].noOfCustomers++;
            counters[0].ccDepTime = arrival + service;
            depT = counters[0].ccDepTime;
            //heapify the counters heap based on the no of customers
            heapify(0);
        }
            //else if there are customers in the queue, then the 0th location will contain the counter which has the least no of customers
        else {

            //case 1 : the arrival time is more than the time when service of the current customer will be finished
            /*if(arrival > counters[0].ccDepTime){
                noOfCustomers -- ; 
                //delete the previous customer 
                --> 
                counters[0].ccDepTime = arrival + service;
            }*/
            //above case will already be handled using the delete min operation in the heap 2

            //case 2 : the arrival time is less than the time when service of the current customer will be finished
            counters[0].noOfCustomers++;
            counters[0].ccDepTime = counters[0].ccDepTime +
                                    service; //might need to store the departure time of all the customers in the queue
            depT = counters[0].ccDepTime;
            //heapify the counters heap
            heapify(0);
        }
        //need to add this element into the heap 2, so need to return its arrival,departure time and the queue no
        Customer c;
        c.queueNo = Q_NO;
        c.arrivalTime = arrival;
        c.departureTime = depT;
        return c;

    }

    void updateHeap(int qN) {
        //find the appropriate location out of the k counters
        int id;
        for (int i = 0; i < size; i++) {
            if (counters[i].id == qN) {
                id = i;
                break;
            }
        }
        //id contains the index at which we need to update the noOfCustomers
        counters[id].noOfCustomers--;
        int noc = counters[id].noOfCustomers;
        if (noc == 0) {
            counters[id].ccDepTime = 0; //no more customers in the queue
        }
        Counter c = counters[id];
        //parent is at (id-1)/2 since starting from 0th index
        while (id > 0 && noc < counters[(id - 1) / 2].noOfCustomers) {
            counters[id] = counters[(id - 1) / 2];
            id = (id - 1) / 2;
        }
        counters[id] = c; //right position for this customer 
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

    serviceTimeVec[0] = 5.8;
    serviceTimeVec[1] = 6.3;
    serviceTimeVec[2] = 6.9;
    serviceTimeVec[3] = 3.5;
    serviceTimeVec[4] = 6.5;
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
    while (clock != -1 && currentLoc < N) {
        clock+= arrivalTimeVec[currentLoc];
        //case 1: when the clock is larger than the dep time of customer on top of H1
        //keep deleting customers till the dep time of top customer is smaller than clock
        if (clock > heap2.topCustomerDepTime()) {
            int qn; //to find the correct counter in H1
            //-->call deleteMin till the topCustomerDepTime is smaller than clock
            while (heap2.topCustomerDepTime() < clock && heap2.topCustomerDepTime() != 0) {
                qn = heap2.topCustomerQueueNo();
                heap2.deleteMin();
                //--> we also need to update the queue no in H1 by reducing its no of customers
                heap1.updateHeap(qn);
            }
        }
        //now simply generate a node from H1 and insert in H2
        heap2.insert(heap1.insert(clock, serviceTimeVec[currentLoc]));
        currentLoc++;
    }
    //clock += 5;
    //heap2.insert(heap1.insert(clock,7));
    heap2.display(N);
    return 0;
}