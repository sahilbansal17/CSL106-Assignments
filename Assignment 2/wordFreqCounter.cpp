#include <iostream>
#include <fstream>

using namespace std;

int hashTable[1000]={0};

int hashF(string s)
{
	int len = s.length(),index=0;
	for(int i=0;i<len;i++)
	{
		if(s[i]>=97 && s[i]<=122)
			index+=(s[i]-97);
		else 
			index+=(s[i]-65);
		//to ensure that capitalization makes no difference 
	}
	return (index)%1000;
}

int main()
{


	/*printing ascii value of apostrophe 
	char ch = '\'';
	cout<<int(ch)<<endl; 
	ASCII(') = 39*/ 


	int hashValue;

	ifstream fin("input.txt"); //to read from a file input.txt

	string s; //take input word by word from file
	while(!fin.eof())
	{
		fin>>s;
		hashValue = hashF(s);
		hashTable[hashValue]++;
	}

	fin.close();

	ifstream fin2("input.txt"); //again reading to print the count 
	while(!fin2.eof())
	{
		fin2>>s;
		hashValue = hashF(s); 
		if(hashTable[hashValue] > 0)
		{
			cout<<s<<":"<<hashTable[hashValue]<<endl;
			hashTable[hashValue]=0;
		}
	}
	fin2.close();
	return 0 ; 

}
