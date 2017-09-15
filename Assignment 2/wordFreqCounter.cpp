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


void copy(int hashValue,char* modifiedS)
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

void linearProbe(int probe, char* data)
{
	int flag = 0; //it will become 1 when we find an empty location
    while(flag==0)
    {
        probe++;
        if(hashTable[probe].count==0) //when that location in hashtable is empty
        {
        	copy(probe,data);
        	hashTable[probe].count++;
        	flag = 1;
        }
    }
}
int main()
{


	/*printing ascii value of apostrophe 
	char ch = '\'';
	cout<<int(ch)<<endl; 
	ASCII(') = 39*/ 
	hashTable[size].count=0; //intialize the count 

	int hashValue, totalWords = 0 ;

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
        		copy(hashValue,modifiedS);
        		hashTable[hashValue].count++; //increment the count of that word to 1
        	}
        	else if(strcmp(hashTable[hashValue].word,modifiedS)==0)
			{
				hashTable[hashValue].count++; //since same word is stored we can increment its count
        	}
        	else
        	{
        		//this refers to the case of a collision 
        		linearProbe(hashValue,modifiedS);//resolving using linear probing
        	} 
        	totalWords ++ ;
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

	int th; //threshold value
	cout<<"Please enter the threshold value: ";
	cin>>th;

	cout<<"The total words in the file are: "<<totalWords<<endl;


	//creating another hashtable which will store only those words whose count is more than the threshold
	struct hT thresholdHT[totalWords];
	int id = 0, reqW = 0;
	for(int i=0;i<size;i++)
	{
		if(hashTable[i].count>th)
		{
			reqW ++; //increment count of those words which are greater than threshold
			int k = 0;
			thresholdHT[id].word = new char[101];
    		//copying the word at ith index in hashTable to word at id index in thresholdHT
    		while(hashTable[i].word[k]!='\0')
    		{
       			thresholdHT[id].word[k]=hashTable[i].word[k];
        		k++;
    		}
    		thresholdHT[id].word[k]='\0';
			thresholdHT[id].count = hashTable[i].count;
			id++;
		}
	}

	if(reqW>0)
	{
		cout<<"The words having frequency more than threshold ("<<reqW<<") are:"<<endl;
		for(int i=0;i<reqW;i++)
		{
			cout<<thresholdHT[i].word<<":"<<thresholdHT[i].count<<endl;
		}
	}
	else
		cout<<"No such words exist.";


	return 0 ; 

}
