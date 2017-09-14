#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int hashTable[1000]={0};

int hashF(char*s)
{
	int index=0;
	for(int i=0;s[i]!='\0';i++)
	{
		index += s[i]-97+1;
	}
	return (index)%1000;
}


void toLower(char*s)
{
	for(int i=0;s[i]!='\0';i++)
	{
		if(s[i]>=65 && s[i]<=90)
			s[i]=s[i]+32; 
	}
}

int main()
{


	/*printing ascii value of apostrophe 
	char ch = '\'';
	cout<<int(ch)<<endl; 
	ASCII(') = 39*/ 


	int hashValue;

	ifstream fin("input.txt"); //to read from a file input.txt

	char* s; //take input word by word from file
	s = new char[100];

	char delim[] = "! ,.\"#$%&()*+-/:;<>=?@[]\\^_{}|~";

	while(!fin.eof())
	{
		fin>>s;
		char* modifiedS = strtok(s,delim);
		while(modifiedS)
    	{
    		toLower(modifiedS);
        	hashValue = hashF(modifiedS);
			hashTable[hashValue]++;
        	modifiedS = strtok(NULL,delim);
    	}	
	}
	fin.close();

	ifstream fin2("input.txt"); //again reading to print the count 
	while(!fin2.eof()) 
	{
		fin2>>s;
		char* modifiedS = strtok(s,delim);
		while(modifiedS)
    	{
    		toLower(modifiedS);
        	hashValue = hashF(modifiedS);
			if(hashTable[hashValue] > 0)
			{
				cout<<modifiedS<<":"<<hashTable[hashValue]<<endl;
				hashTable[hashValue]=0;
			}
        	modifiedS = strtok(NULL,delim);
    	}	
		
	}
	fin2.close();
	return 0 ; 

}
