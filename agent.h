#ifndef __AGENT_H__ // include guard
#define __AGENT_H__

#include <iostream>
#include <vector>


using namespace std;
using namespace std::chrono;

namespace
{
	int CHANNEL_CAP=3000;	

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
			A[Jtemp]++;//compute_equivalence_size
		}
	}

	void compute_equivalence_size(agent agent1,std::vector<int>& maxeqsizes,  bool verbose)
	{
		std::vector<int> maps(agent1.n);	  // Vector to store all mappings of a message. With changing e, where does m goes
		std::vector<int> non_zeros(agent1.n); //Vector to compute total non-zero mappings of a message

		if(verbose)
			cout<<"Primes:"<<Q_chosen<<","<<P_chosen<<"\tn:"<<Q_chosen*P_chosen;

		for(int i=0; i < agent1.n;i++)
	    {
	        std::fill(maps.begin(),maps.end(), 0);
	        //If not visited
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
			cout<<"\nMax Equivalence size:"<<maxeqsizes[maxeqsizes.size()-1]<<endl<<endl;
	}

	void get_all_mappings_of_msg(int msg, agent B,std::vector<int>& maps, vector<bool>& visited, bool verbose)
	{
		int Jtemp,ctemp;
		for(int i=0; i < int(B.coprimes.size()); i++) 
		{
			ctemp = B.coprimes[i];

			Jtemp = encrypt(msg,ctemp,B.n);
			
			if (visited[Jtemp]==false)
				maps.push_back(Jtemp);

			visited[Jtemp]=true;
			
			
			if(verbose)
				cout<<"i:"<<i<<"\tc[i]:"<<ctemp<<"\tmsg:"<<msg<<"\tJ:"<<Jtemp<<endl;
		}
	}

	void compute_equivalence_size_opt(agent agent1,vector<int>& maxeqsizes,  bool verbose)
	{
		vector< vector<int> > classes;
		vector<int> maps;	  // Vector to store all mappings of a message. With changing e, where does m goes
		// vector<int> non_zeros(agent1.n); //Vector to compute total non-zero mappings of a message
		vector<bool> visited(agent1.n);
		std::fill(visited.begin(), visited.end(), false);

		if(verbose)
			cout<<"Primes:"<<Q_chosen<<","<<P_chosen<<"\tn:"<<Q_chosen*P_chosen;

		for(int i=0; i < agent1.n;i++)
	    {
	    	if(visited[i]==false)
	    	{
	    		maps.clear();
		        //If not visited
		        get_all_mappings_of_msg(i,agent1, maps, visited,false);
		        classes.push_back(maps);
	    	}
	    }

	    for (int i = 0; i < classes.size(); i++)
	    	maxeqsizes.push_back(classes[i].size());

	    if(verbose)
			cout<<"\nNumber of classes is :"<<classes.size()<<endl<<endl;
	}

}

#endif