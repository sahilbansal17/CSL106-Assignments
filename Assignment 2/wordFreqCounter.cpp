#include <iostream>
#include <fstream>
#include <cstring>
#include <math.h>

using namespace std;

#define size 55219 //size of the hashTable

//implementation in which we also store the word in the hashtable
struct hT{
	char *word;
	int count;
}hashTable[size];

//int hashTable[1000]={0};

int hashF(char*s)
{
	int index=0;
	int a = 2;
	for(int i=0;s[i]!='\0';i++)
	{
		index += a*abs(s[i]-97+1);
		a*=2;
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

void copy(struct hT a[],int hashValue,char* modifiedS)
{   	
	int k = 0;
	a[hashValue].word = new char[256];
    while(modifiedS[k]!='\0')
    {
       	a[hashValue].word[k]=modifiedS[k];
        k++;
    }
    a[hashValue].word[k]='\0';
}

void QuadProbe(int probe, char* data)
{
	int k = 1;
	int flag = 0; //it will become 1 when we find an empty location
    while(flag==0)
    {
        probe=(probe+k*k)%size;
        if(hashTable[probe].count==0) //when that location in hashtable is empty
        {
        	copy(hashTable,probe,data);
        	hashTable[probe].count++;
        	flag = 1;
        }
        k++;
    }
}

void swap(hT x[],int a,int b) //to swap two hT structure nodes 
{
	int temp = x[a].count;
	x[a].count = x[b].count;
	x[b].count = temp;

	char *s = x[a].word;
	x[a].word = x[b].word;
	x[b].word = s;
}

int partArr(hT A[],int s, int e)
{
	int i = s+1;
	int piv = A[s].count;  //choose 1st element's count as pivot
	for(int j=s+1;j<=e;j++)
	{
		if(A[j].count<piv) //as soon as you encounter a smaller no than piv, swap it with the 1st element from beg which is larger than the piv
		{
			swap(A,j,i);
			i++;
		}
	}
	swap(A,s,i-1); //to make sure that pivot element is put in its proper place
	return i-1;
}

void quick_sort(hT A[],int beg,int end)
{
	if(beg<end)
	{
		int pivot_index = partArr(A, beg, end); //partition the array and return the index of element, elements to whose left are smaller and right side are larger than it 
		quick_sort(A,beg,pivot_index-1); //sort the left partition
		quick_sort(A,pivot_index+1,end); //sort the right partition
	}
}
int main()
{
	hashTable[size].count=0; //intialize the count 

	int hashValue, totalWords = 0 ; //totalWords now refers to the distinct words in the file

	ifstream fin("input.txt"); //to read from a file input.txt

	char* s; //take input word by word from file
	s = new char[256]; //assuming max size 255 of each word

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
        		copy(hashTable,hashValue,modifiedS);
        		hashTable[hashValue].count++; //increment the count of that word to 1
        		totalWords ++ ;
        	}
        	else if(strcmp(hashTable[hashValue].word,modifiedS)==0)
			{
				hashTable[hashValue].count++; //since same word is stored we can increment its count
        	}
        	else
        	{
        		//this refers to the case of a collision 
        		QuadProbe(hashValue,modifiedS);//resolving using linear probing
        		totalWords ++ ;
        	}
        	modifiedS = strtok(NULL,delim); 
    	}	
	}
	fin.close();

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
			copy(thresholdHT,id,hashTable[i].word); //copying the word at ith index in hashTable to word at id index in thresholdHT
			thresholdHT[id].count = hashTable[i].count;
			id++;
		}
	}

	//sorting the elements in this hashtable from index 0 to reqW-1 in ascending order 
	quick_sort(thresholdHT,0,reqW-1);
	if(reqW>0)
	{
		cout<<"The words having frequency more than threshold ("<<reqW<<") are:"<<endl;
		for(int i=reqW-1;i>=0;i--) //displaying them from the element in last index (largest value of count)
		{
			cout<<thresholdHT[i].word<<":"<<thresholdHT[i].count<<endl;
		}
	}
	else
		cout<<"No such words exist.";


	return 0 ; 

}
