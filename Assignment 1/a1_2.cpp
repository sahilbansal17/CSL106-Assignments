#include <iostream>
#include <fstream>
#include <exception>
#include "queue.h" 
#include "stack.h"

using namespace std;


int main()
{
	ofstream fout("process.txt"); /*using file handling to save the set of operations performed in a file process.txt
									since we don't know until we perform some operations whether stack permutation is 
									valid or not but we print them as they are performed, so better to write to file*/
	
	queue <int> q1; // the input queue containing numbers from 1 to n 
	
	queue <int> q2; // the output queue where we can only enqueue elements
	
	stack <int> s; // stack where both push and pop can be performed 
	
	int n,x,flag=1,poppedQueue=0; /* x denotes element of permutation entered, flag is set 1 initially;it becomes 0 as soon
									as we come to know perm. entered is not valid */ 
	
	cout<<"Please enter the value of n (the no of elements in the input queue):\t";
	cin>>n;
	
	int *a = new int [n]; //array to store the permutation entered 
	cout<<"Please enter the stack permutation:\n";
	for(int i=0;i<n;i++)
	{
		cin>>x;
		q1.enqueue(i+1);
		a[i]=x;
	}
	
	int index; /* declared outside for loop since it will help while printing the reason, as we know at what value 
				  we became sure that it is not valid permutation */

	for(index=0;index<n;index++) //traversing through all the elements of the permutation entered 
	{
		try
		{

			if(!q1.isEmpty() && a[index]==q1.front()) //if perm no is same as that on front of queue, dequeue from q1 and enqueue into q2
			{
				//if q1 was empty then front would have thrown exception 
				poppedQueue = q1.dequeue(); /*the last element dequeued is stored as it is required to check whether 
											  next element in perm is already into stack or not	*/
				q2.enqueue(poppedQueue);
				fout<<"enqueue(Q2,dequeue(Q1)->"<<poppedQueue<<")"<<endl;
			}
			else if(a[index]<poppedQueue && !q2.isEmpty()) /*if next in perm is smaller then that must have been already
															pushed into the stack, if q2 is empty then we must first fill stack */
			{
				/*now if it is same as that on top then it can be valid otherwise we just set flag to be zero and break
				since that element must be below top in stack */ 
				if(s.top()==a[index]) 
				{
					int temp = s.pop(); //pop from stack and enqueue into q2 
					q2.enqueue(temp);
					fout<<"enqueue(Q2, pop(S)->"<<temp<<")"<<endl;
				}
				else 
				{
					flag = 0 ;
					break;
				}
			}
			else if(a[index] > poppedQueue) /*case when next elem in perm is bigger than that lastly dequeued from q1, so we must push all elements
					till we reach the next elem to be enqueued to q2*/
			{
				while(q1.front()<a[index])
				{
					s.push(q1.front());
					fout<<"push(S, dequeue(Q1)->"<<q1.dequeue()<<")"<<endl;
				}		
				index--;
			}
			else //case when invalid perm entered for eg. repeated two numbers 
			{
				flag = 2;
				break;
			}
		}
		catch(EmptyQueueException e)
		{
			flag = 2;
			break;
			cout<<e.what()<<endl; //if exceptions are returned that means invalid permutation entered 
		}
	}
	fout.close();


	if(flag==1) //valid case 
	{
		cout<<"Yes, it is a stack permutation."<<endl;
		//read from the file and print the process list 

		ifstream fin("process.txt");
		string s;
		while(!fin.eof())
		{
			getline(fin,s);
			cout<<s<<endl;
		}
		fin.close();
	}
	else //invalid case 
	{
		cout<<"No, it is not a stack permutation."<<endl;
		if(flag == 2)
		{
			cout<<"This is because either you have repeated numbers or entered no. greater than n."<<endl;
		}
		else
		{
			cout<<"This is because to enqueue "<<a[index]<<" into Q2 after "<<a[index-1];
			cout<<" we would have to push ";
			int k=0;
			for(int i=1;i<a[index-1];i++) //possibly all these elements from 1 to a[index-1] can be in stack
			{ 
				if(a[k]!=i) //those in array before index-1 are not in stack, whenever a[k] is matched with i, do not print i but inc k
					cout<<i<<" ";
				else
					k++;
			}
			cout<<"into the stack which would then be output in the order:"<<endl;
			while(!s.isEmpty())
			{
				cout<<s.top()<<" ";
				s.pop();
			}
			cout<<endl<<endl;
		}
	}	

	return 0;
}