#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

#define size 1000 //size of the hashTable

//implementation in which we also store the word in the hashtable
struct hT{
	char *word;
	int count;
}hashTable[size];

//int hashTable[1000]={0};

int hashF(char*s)
{
	int index=0;
	for(int i=0;s[i]!='\0';i++)
	{
		index += s[i]-97+1;
	}
	return (index)%size;
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
	hashTable[size].count=0; //intialize the count 

	int hashValue;

	ifstream fin("input.txt"); //to read from a file input.txt

	char* s; //take input word by word from file
	s = new char[101]; //assuming max size 100 of each word

	char delim[] = "! ,.\"#$%&()*+-/:;<>=?@[]\\^_{}|~";

	while(!fin.eof())
	{
		fin>>s;
		char* modifiedS = strtok(s,delim); //modified S will contain all splits of s due to space or punctuation marks other than apostrophe
		while(modifiedS)
    	{
    		toLower(modifiedS);
        	hashValue = hashF(modifiedS);
        	if(hashTable[hashValue].count==0) //to store the word if it has not been visited earlier
        	{
        		int k = 0;
        		hashTable[hashValue].word = new char[101];
        		while(modifiedS[k]!='\0')
        		{
        			hashTable[hashValue].word[k]=modifiedS[k];
        			k++;
        		}
        		hashTable[hashValue].word[k]='\0';
        	}
			hashTable[hashValue].count++; //increment the count of that word
        	modifiedS = strtok(NULL,delim); 
    	}	
	}
	fin.close();

	/*ifstream fin2("input.txt"); //again reading to print the count 
	while(!fin2.eof()) 
	{
		fin2>>s;
		char* modifiedS = strtok(s,delim);
		while(modifiedS)
    	{
    		toLower(modifiedS);
        	hashValue = hashF(modifiedS);
			if(hashTable[hashValue].count > 0) //so that the next time same string should not get printed
			{
				cout<<modifiedS<<":"<<hashTable[hashValue].count<<endl;
				hashTable[hashValue].count=0; //reset its value 
			}
        	modifiedS = strtok(NULL,delim);
    	}	
		
	}
	fin2.close();*/

	//no need to read from file now as we also store the keys in HT
	for(int i=0;i<size;i++)
	{
		if(hashTable[i].count!=0)
			cout<<hashTable[i].word<<":"<<hashTable[i].count<<endl;
	}
	return 0 ; 

}
