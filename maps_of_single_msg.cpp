#include <iostream>
#include <cstdlib>
#include <math.h>
#include <ctime>
#include <unistd.h>
#include "rsa.h"
#include <vector>
#include <fstream>
#include <string>
#include <set>
#include <iterator>
#include <chrono>
#define ll long long

using namespace std::chrono;
using namespace std;

int CHANNEL_CAP;	
// #define P_chosen 997
// #define Q_chosen 17

int P_chosen;
int Q_chosen;

class agent
{
private:
	int p,q,phin,d;
	int mhat;

	//Function to compute all coprimes of a particular n
    void compute_coprimes() 
    {
    	for(int i=2; i<n;i++)
    	{
    		if(checkcoprime(i,phin)) 
    			coprimes.push_back(i);
    	}
    }

    //Function to compute static private values of an agent, means needs to be only computed once
	void generate_pvt_static_keys()
	{
		coprimes.clear();
		p=P_chosen; 		// first prime
		q=Q_chosen; 		// second prime
		n=p*q;				// n the god
		phin=(p-1)*(q-1);	// Euler Toitent function of n
		compute_coprimes(); // Compute coprimes
        
	}
	//decrpyt
	int decrpyt(int Qhat)
	{
		return encrypt(Qhat,d,n);
	}

	//Printing all the information
	void print_private()
	{
		cout<<"P:"<<p<<"\tQ:"<<q<<"\tN:"<<n<<"\tPhi(n):"<<phin<<"\tc:"<<c<<"\td:"<<d<<endl;
	}

public:
	int robot_id;
	int n,c;
	std::vector<int> coprimes;
	int J,Jhat;

	agent(int robot){robot_id=robot; generate_pvt_static_keys();};

	/*--------------- Standard Functions to do ----------------------*/
	void generate_static_keys()
	{
		generate_pvt_static_keys();
	}
	// Generates random private values of an agent, changes every time step
	void generate_pvt_random_keys()
	{
		c=coprimes[rand()%(coprimes.size())]; //Random c
		d=modInverse(c,phin); // d is modiverse of c
	}

	//Function to generate encrpyted message, using agent receiver public key
	void generate_encrypted_message(int m,agent reciever)
	{
		J=encrypt(m,reciever.c,reciever.n);
	}

	//Function to decrpyt encrpyted message from agent sender
	void decrpyt_message_from(agent sender)
	{
		Jhat=sender.J;
		mhat=decrpyt(Jhat);
	}

	// Get the value of decrypted msg
	int get_mhat()
	{
		return mhat;
	}
	
	/*------------- Printing Functions ------------------------------*/
	// Print key
	void print_key(bool pvt)
	{
		if (pvt) //if want to print private key as well
			print_private();
		else
			cout<<"N:"<<n<<"\tc:"<<c<<endl;
	}
};

/*---------------------- Mapping functions -------------------------------*/
void get_all_mappings_of_msg(int msg, agent B,std::vector<int>& A, bool verbose)
{
	int Jtemp,ctemp;
	for(int i=0; i < int(B.coprimes.size()); i++) 
	{
		ctemp = B.coprimes[i];
		Jtemp = encrypt(msg,ctemp,B.n);
		if(verbose)
			cout<<"i:"<<i<<"\tc[i]:"<<ctemp<<"\tmsg:"<<msg<<"\tJ:"<<Jtemp<<endl;
		A[Jtemp]++;
	}
}

void compute_max_equivalence_size(agent agent1,std::vector<int>& maxeqsizes,  bool verbose)
{
	std::vector<int> maps(agent1.n);	  // Vector to store all mappings of a message. With changing e, where does m goes
	std::vector<int> non_zeros(agent1.n); //Vector to compute total non-zero mappings of a message

	if(verbose)
		cout<<"Primes:"<<Q_chosen<<","<<P_chosen<<"\tn:"<<Q_chosen*P_chosen<<endl;

	for(int i=0; i < agent1.n;i++)
    {
        std::fill(maps.begin(),maps.end(), 0);
        get_all_mappings_of_msg(i,agent1, maps, false);
        non_zeros.push_back(count_non_zeros_vec(maps));
        // cout<<"M:"<<i<<"\tNon_zeros:"<<count_non_zeros_vec(maps)<<endl;
    }
    // cout<<"Maps of "<<agent1.n-1<<endl;
    // cout<<maps.size()<<" "<<non_zeros.size()<<endl;
    // printvec(maps);
	// printvec(non_zeros);
    maxeqsizes.push_back(*std::max_element(non_zeros.begin(),non_zeros.end()));
	if(verbose)
		cout<<"Max Equivalence size:"<<maxeqsizes[maxeqsizes.size()-1]<<endl<<endl;
}



int main(int argc, char const *argv[])
{
	agent agent1(1),agent2(2); //Two agents
	randomise_seed();// RANDOMISING SEED

	std::vector<int> poss_p;//vector of possible p's such that it maximizes the channel cap usage
	std::vector<int> poss_q;//possible q's

    CHANNEL_CAP=1000;// Channel Capacity is max integer we can send via channel
    P_chosen = 41; Q_chosen=13;
    /* BEFORE HAND COMPUTATIONS */
	cout<<"Starting before actual Transmission codes"<<endl;
	cout<<"Channel capacity is "<<CHANNEL_CAP<<endl; //By channel cap i mean message capacity
	cout<<"Chosen P:"<<P_chosen<<" and Chosen Q:"<<Q_chosen<<endl;

	std::vector<int> maps(P_chosen*Q_chosen);
	std::vector<int> mappings;

	agent1.generate_static_keys();

	cout<<"Value of n is:"<<agent1.n<<endl;


	int m = 6

	std::fill(maps.begin(), maps.end(),0);
	get_all_mappings_of_msg(i, agent1,maps,false);
	cout<<"Message:"<<m;
	cout<<"\tEquivalence Class Size:"<<count_non_zeros_vec(maps,mappings)<<endl;
	myfile<<i<<" "<<count_non_zeros_vec(maps,mappings)<<endl;
	printvec(mappings);

	/*
	cout<<"Computing total Channel capacity "<<endl;
	poss_p.clear();
	poss_q.clear();

	t1 = high_resolution_clock::now();
	compute_all_possible_pairs(CHANNEL_CAP, poss_p, poss_q,false);
	t2 = high_resolution_clock::now();
	*/
	std::vector<int> maxeqsizes;

	
	// printvec(poss_p, poss_p.size());
	// printvec(poss_q, poss_q.size());
	/*
	for (int i = 0; i < poss_p.size(); i++)
	{
		
		// Q_chosen = poss_p[poss_p.size()-1];
		// P_chosen = poss_q[poss_q.size()-1];

		Q_chosen = poss_q[i];
		P_chosen = poss_p[i];
		t3 = high_resolution_clock::now();
		agent1.generate_static_keys();
		t4 = high_resolution_clock::now();
		compute_equivalence_size(agent1, maxeqsizes, true);
		// myfile<<P_chosen<<","<<Q_chosen<<" "<<maxeqsizes[maxeqsizes.size()-1]<<" "<<Q_chosen*P_chosen<<endl;
		t5 = high_resolution_clock::now();

	}
	*/
	// printvec(maxeqsizes);
	cout<<"Time to compute all possible pairs:"<<(float)(duration_cast<microseconds>( t2 - t1 ).count())/1000000<<" s"<<endl;
	cout<<"Time for the entire looping process to calculate max possible pairs:"<<(float)(duration_cast<microseconds>( t5 - t3 ).count())/1000000<<" s"<<endl;
	cout<<"Time to calculate 1 Equivalence class:"<<(float)(duration_cast<microseconds>( t5 - t4 ).count())/1000000<<" s"<<endl;
	cout<<"Time required for computation of private static keys:"<<(float)(duration_cast<microseconds>( t4 - t3 ).count())/1000000<<" s"<<endl;
	// cout<<"Channel_capacity:"<<CHANNEL_CAP<<"\tMax_equivalence size:"<<*std::max_element(maxeqsizes.begin(),maxeqsizes.end())<<endl;
	// myfile<<CHANNEL_CAP<<" "<<*std::max_element(maxeqsizes.begin(),maxeqsizes.end())<<endl;
	// myfile.close();
    
	return 0;
}
