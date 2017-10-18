<<<<<<< HEAD
<<<<<<< HEAD
# CSL106-Assignments
This contains the assignments completed in the Data Structures Course in 3rd Semester Course (2017 Aug - Nov) at IIT Jammu.
=======
##This program takes R,k,mu,sigma,N as the input and prints the avg waiting time for a customer as the output. 
=======
## This program takes R,k,mu,sigma,N as the input and prints the avg waiting time for a customer as the output. 
>>>>>>> Update README.md

### R : arrival rate of customers 

### k : no of billing counters in the shop

### mu : mean of the service time 

### sigma : variance of the service time 

### N : no of the customers

The service time is a random variable. The service time of a customer is chosen randomly from [mu-sigma,mu+sigma].

If a particular customer arrives at time t, the next customer will arrive at time t+rt where rt = random no. from [0,1/R].

#### A new customer will always join the queue [there can be atmost k queues at a time since there are k billing counters] with the least no of customers at that time.

A heap H1 of size k maintains the current no of customers in the queue and the time when services of its current customer will be finished. The topmost node will be the one with the least no of customers in the queue.

Another heap H2 of size equal to the no of current customers will contain the customer's queue no, arrival time and the departure time. It will be ordered by departure time (smallest on the top).
>>>>>>> Add readme.md
