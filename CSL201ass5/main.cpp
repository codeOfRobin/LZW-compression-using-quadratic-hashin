//
//  main.cpp
//  CSL201ass5
//
//  Created by Robin Malhotra on 23/10/13.
//  Copyright (c) 2013 Robin's code kitchen. All rights reserved.
//

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <math.h>
using namespace std;



map<long,string> hashtable;
static fstream f1;
long prime;

void insert(string word)
{
    int count=0;
    long a=word[0]%prime;
    
        while (hashtable[a]!="\0")
        {
            count++;
            a=(a*prime+count*count)%prime;
        }
        
        hashtable[a]=word;
}

long get_prime(long a)
{
	while(true)
    {
		int sqrroot=sqrt(a),i=2;
		while(i<=sqrroot)
        {
			if(a%i==0)
            {break;}
			i++;
		}
		if(i>sqrroot)
        {return a;}
		a++;
	}
}



long search(string word)
{
    int count=1;
    long a=word[0]%prime;
    long makesure=a;
    
    while (hashtable[a]!="\0")
    {
        if (hashtable[a]==word)
        {
            return a;
        }
        
        a=(a*prime+count*count)%prime;
        if (makesure==a)
        {
            break;
        }
        count++;
    }
    return -1;
}


void initial()
{
    for (int i=32; i<127; i++)
    {
        hashtable[i]=char(i);
    }
    
    
    
}


void compress(string data)
{
    ofstream f2;
    string s2;
    f2.open("/Users/robinmalhotra2/Desktop/ass5compression.txt",ios::in|ios::out);
    string current;
    int j=0;
    
    for (int i=0; i<data.length(); i++)
    {
        current=data.substr(j,i-j+1);
        if (search(current)==-1)
        {
            insert(current);
            s2=current.at(current.size()-1);
            current.pop_back();
            if (search(current)!=-1)
            {
                f2<<search(current)<<" ";
                
            }
             j=i;
        }
        
        else
        {
            continue;
        }
    }
    
    
    
    
    
    cout<<"Somrhitng";
    
    
    f2<<search(s2);
    
    
    f2.close();
}


void createhashfile()
{
    ofstream f2;
    f2.open("/Users/robinmalhotra2/Desktop/hash.txt",ios::in|ios::out);
    
    for (int i=0; i<hashtable.size(); i++)
    {
        if (hashtable[i]!="\0")
        {
            f2<<i<<"="<<hashtable[i]<<"\n";
        }
    }
    
    f2.close();
    exit(1);
}







int main()
{
    f1.open("/Users/robinmalhotra2/Desktop/csl201ass5.txt",ios::in|ios::out);
    string data;
    
    getline(f1,data);

    prime=data.length();
    prime=get_prime(prime+128);

    initial();

    compress(data);
    
    
    f1.close();

    
    createhashfile();

    return 1;
}
