#include <exception>
#include <iostream>
using namespace std;
//defining the exception 
//reference : https://stackoverflow.com/questions/16182781/how-to-create-exceptions
class EmptyStackException : public exception 
{
public:
  const char* what() const throw()
  {
    return "EmptyStackException\n";
  }
};
EmptyStackException es;


//declaring the template class 
template <class S> class stack  //template <class obj_type> class class_name
{
private:
	int max_size; 
	S* st_arr; //array based implementation

	int top_index; 
public:
	stack() //constructor
	{
		max_size = 100000;
		st_arr = new S[max_size];
		top_index = -1;
	}

	//declaring the functions of stack template 
	int size();
	bool isEmpty();
	void push(S value);
	S top() throw(EmptyStackException);
	S pop() throw(EmptyStackException);
};


//function definitions : return_type class_name :: function_name(arguments)
template <class S> int stack<S>::size()
{
	return (1+top_index); //since it starts from -1 initially 
}
template <class S> bool stack<S>::isEmpty()
{
	if(top_index==-1)
		return 1;
	return 0;
}
template <class S> void stack<S>::push(S val) 
{
	if(size()<max_size)
	{
		st_arr[++top_index]=val; //first increment the top index and then assign the value to that index of array
	}
	else
	{
		cout<<"Stack is full."<<endl;
	}
}
template <class S> S stack<S>::top() throw(EmptyStackException) //also throws EmptyStackException
{
	if(top_index==-1) //condition when stack is empty 
		throw es; 
	else
		return st_arr[top_index]; 
}
template <class S> S stack<S>::pop() throw(EmptyStackException) //also throws EmptyStackException
{
	if(top_index==-1) 
		throw es;
	else
		return st_arr[top_index--];
}

	