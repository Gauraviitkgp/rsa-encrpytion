#include <iostream>
#include <cstdlib>
#include <math.h>
#include <ctime>
#include <unistd.h>
#include "rsa.h"
#include <vector>
#include <fstream>
#include <string>
#define ll long long
using namespace std;

int CHANNEL_CAP=3000;	
// #define P_chosen 997
// #define Q_chosen 17

int P_chosen=103;
int Q_chosen=17;

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


int main(int argc, char const *argv[])
{
	// RANDOMISING SEED
	struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);

    /* using nano-seconds instead of seconds */
    srand((time_t)ts.tv_nsec);

    /* BEFORE HAND COMPUTATIONS */
	cout<<"Starting before actual Transmission codes"<<endl;
	cout<<"Channel capacity is "<<CHANNEL_CAP<<endl;
	cout<<"Chosen P:"<<P_chosen<<" and Chosen Q:"<<Q_chosen<<endl;


	agent agent1(1),agent2(2);

	std::vector<int> poss_p;//possible p's
	std::vector<int> poss_q;//possible q's

	ofstream myfile;
	myfile.open("const_max_channel_cap3000_primes_vs_sizeofequivalent_class.txt");

	compute_all_possible_pairs(CHANNEL_CAP, poss_p, poss_q,false);

	
	std::vector<int> non_zeros(agent1.n);

	cout<<"Printing total mappings for each message "<<endl;
	for (int i = 0; i < poss_p.size(); i++)
	{
		Q_chosen = poss_p[i];
		P_chosen = poss_q[i];
		
		agent1.generate_static_keys();
		
		std::vector<int> maps(agent1.n);
		
		cout<<"I:"<<i<<"\tPrimes:"<<Q_chosen<<","<<P_chosen<<"\tn:"<<Q_chosen*P_chosen<<endl;
		

		for(int i=0; i <agent1.n;i++)
	    {
	        std::fill(maps.begin(),maps.end(), 0);
	        get_all_mappings_of_msg(i,agent1, maps, false);
	        non_zeros.push_back(count_non_zeros_vec(maps));
	        // cout<<"M:"<<i<<"\tNon_zeros:"<<count_non_zeros_vec(maps)<<endl;
	    }
	    cout<<"Max Equivalence class size:";
	    cout<<*std::max_element(non_zeros.begin(),non_zeros.end())<<endl<<endl;
	    myfile<<Q_chosen<<" "<<P_chosen<<" "<<*std::max_element(non_zeros.begin(),non_zeros.end())<<" "<<agent1.n<<endl;
	}
	myfile.close();
    
	return 0;
}
