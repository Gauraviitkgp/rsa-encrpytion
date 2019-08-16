#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include "rsa.h"	//Header File for Math related to rsa operations
#include "agent.h" //Header File for Agent Related operations
// #include <assert.h>

#define max_prime 131
#define FILE true

using namespace std;


int main()
{

	agent agent1(1), agent2(2);
	long store[max_prime*max_prime][2]={0};

	vector<int> eqsizes;

	vector<int>::iterator it = find(primes.begin(), primes.end(), max_prime);

	int size = it-primes.begin();
	cout<<size;
	
	for (int i = 0; i <= size; i++)
	{
		for(int j = size; j>=i; j--)
		{
			eqsizes.clear(); 
			
			P_chosen = primes[i];
			Q_chosen = primes[j];
			agent1.generate_static_keys();
			
			compute_equivalence_size_opt(agent1, eqsizes, false);
			
			for (int i = 0; i < eqsizes.size(); i++)
			{
				store[eqsizes[i]][0] = P_chosen; store[eqsizes[i]][1] = Q_chosen;
			}
			
			cout<<"P:"<<P_chosen<<"\tQ:"<<Q_chosen<<"\tEq_size:"<<eqsizes.size()<<endl;	
		}
	}

	if(FILE)
	{
		ofstream myfile;
		myfile.open("data.txt");
		for (int i = 0; i < max_prime*max_prime; i++)
			myfile<<i<<" "<<store[i][0]<<" "<<store[i][1]<<endl;
		myfile.close();
	}
	
}