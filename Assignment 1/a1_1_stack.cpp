#include <iostream>
#include <exception>
#include "stack.h"
using namespace std;

int main()
{
	/* Trying basic operations 
	stack <int> a;
	for(int i=1;i<=5;i++)
	{
		a.push(i);
	}
	try
	{
		cout<<"The top element is : "<<a.top()<<endl;
	}
	catch(EmptyStackException e)
	{
		cout<<e.what();
	}
	cout<<"The size of the stack is : "<<a.size()<<endl;
	try
	{
		cout<<"The popped elements are : "<<a.pop()<<" "<<a.pop()<<" "<<a.pop()<<" "<<a.pop()<<" "<<a.pop()<<endl;
	}
	catch(EmptyStackException e)
	{
		cout<<e.what();
	}
	cout<<"The stack now is empty =>"<<a.isEmpty()<<endl;
	try
	{
		cout<<"Trying to pop from empty stack: "<<a.pop();
	}
	catch(EmptyStackException e)
	{
		cout<<e.what();
	}*/

	//defining a user navigation for the program to easily perform stack operations 

	//replace the int by the type of elements to be inserted into the stack 
	stack <int> a;
	cout<<"Please choose from the following: "<<endl;
	cout<<"1. Push"<<endl;
	cout<<"2. Pop"<<endl;
	cout<<"3. Check whether the stack is empty"<<endl;
	cout<<"4. Check the size of stack"<<endl;
	cout<<"5. Show the top element of the stack"<<endl;
	int opt; //variable to be used for switch case statement 
	cin>>opt;
	home: //defining a label for using goto statement 
	switch(opt)
	{
		case 1: cout<<"Enter the element to push : ";
				int x;
				cin>>x;
				a.push(x);
				break;
		case 2: cout<<"You are about to delete an element from queue. Enter y/Y to confirm : ";
				char ch;		
				cin>>ch;
				if(ch=='y'||ch=='Y')
				{
					//use try catch block since pop() can return an exception 
					try
					{
						int x = a.pop();
						cout<<x<<" is deleted from the stack."<<endl;
					}
					catch(EmptyStackException e)
					{
						cout<<e.what(); //this function prints the exception message 
					}
				}	
				break;
		case 3: if(a.isEmpty()==1)
					cout<<"Yes, the stack is empty!"<<endl;
				else
					cout<<"No, the stack is not empty."<<endl;
				break;
		case 4: cout<<"The size of the stack is : "<<a.size()<<endl;
				break;
		case 5: //use try catch block since top() can return an exception 
				try
				{
					cout<<"The top element in the stack is : "<<a.top()<<endl;
				}
				catch(EmptyStackException e)
				{
					cout<<e.what();
				}
				break;
	}
	cout<<"Enter 0 to return to main menu/any other number to exit."<<endl;
	cin>>opt;
	if(opt==0)
	{
		cout<<"Choose the required option(1-Push,2-Pop,3-isEmpty,4-Size,5-Top) : ";
		cin>>opt;
		goto home;
	}
	return 0;
}

