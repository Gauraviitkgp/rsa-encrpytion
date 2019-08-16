#include <iostream>
#include <vector>
#include "rsa.h"	//Header File for Math related to rsa operations
#include "agent.h" //Header File for Agent Related operations
// #include <assert.h>

using namespace std;


int main(int argc, char const *argv[])
{

	agent agent1(1), agent2(2);
	

	randomise_seed();// RANDOMISING SEED

	CHANNEL_CAP = 500; //Number of distinct numbers a channel can send
	P_chosen = 13; Q_chosen = 7;

	vector<int> eqsizes;
	vector<int> maxeqsize;
	vector<int> poss_p;//vector of possible p's such that it maximizes the channel cap usage
	vector<int> poss_q;//possible q's

	int j = CHANNEL_CAP*8;

	do
	{
		CHANNEL_CAP = j;
			
		poss_p.clear();
		poss_q.clear();
		
		eqsizes.clear();
		compute_opt_possible_pairs(CHANNEL_CAP, poss_p, poss_q,false);

		for (int i = 0; i < poss_p.size(); i++)
		{
			Q_chosen = poss_q[i];
			P_chosen = poss_p[i];
			agent1.generate_static_keys();
			compute_equivalence_size(agent1, eqsizes, false);			
		}
		
		maxeqsize.push_back(*std::max_element(eqsizes.begin(),eqsizes.end()));
		
		cout<<"Channel_capacity:"<<CHANNEL_CAP<<"\tMax_equivalence size:"<<maxeqsize.back()<<endl;

		j-=250;
	} while( maxeqsize.back() > CHANNEL_CAP);
	
	
	
	// assert(Max_eq_size <= CHANNEL_CAP);
	return 0;
}

/* To compute max equivalence Size bottlenecks:
-> Computes All possible Pairs of p and q
-> Generation of static key: Coprimity Check;
-> Computation Of Equivalence class sizes for each message
-> Getting the Maximum element from the stack of Equivalence class size.
-> Getting max elements of all possible Pairs;
-> Running it for times such that maxeq size> channel_capacity*/