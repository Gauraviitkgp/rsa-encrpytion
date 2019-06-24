#include <iostream>
#include <cstdlib>
#include <bits/stdc++.h> 
#include <math.h> 
#include <unistd.h>
#define ll long long
using namespace std;

class agent
{
private:
	int p,q,phin,d;
	int mhat;

	bool checkcoprime(int a, int b) 
	{ 
	    if ( __gcd(a, b) == 1) 
	        return true;  
	    else
	        return false;         
	} 

	int modInverse(int a, int m) 
	{ 
	    a = a%m; 
	    for (int x=1; x<m; x++) 
	       if ((a*x) % m == 1) 
	          return x; 
	} 

	void compute_pvt()
	{
		p=31;
		q=43;
		n=p*q;
		phin=(p-1)*(q-1);

		bool coprime=false;
		
		while(coprime==false)
		{
			c=rand()%phin;
			coprime=checkcoprime(c,phin);
		}
		d=modInverse(c,phin);
	}

	void print()
	{
		cout<<"P:"<<p<<"\tQ:"<<q<<"\tN:"<<n<<"\tPhi(n):"<<phin<<"\tc:"<<c<<"\td:"<<d<<endl;
	}


	int encrypt(int x, unsigned int y, int p) 
	{ 
	    int res = 1;      // Initialize result 
	  
	    x = x % p;  // Update x if it is more than or  
	                // equal to p 
	  
	    while (y > 0) 
	    { 
	        // If y is odd, multiply x with result 
	        if (y & 1) 
	            res = (res*x) % p; 
	  
	        // y must be even now 
	        y = y>>1; // y = y/2 
	        x = (x*x) % p;   
	    } 
	    return res; 
	}

	int decrpyt(int Qhat)
	{
		return encrypt(Qhat,d,n);
	}
	

public:
	int robot_id;
	int n,c;
	int Q,Qhat;

	agent(int robot){robot_id=robot;};

	void generate_key(bool verbose)
	{
		compute_pvt();
		if (verbose==true)
			cout<<"Key generation for robot:"<<robot_id<<" is complete"<<endl;
	}
	
	void print_key(int password)
	{
		if (password==2971)
			print();
		else
			cout<<"N:"<<n<<"\tc:"<<c<<endl;
	}

	void generate_encrypted_message(int m,agent A)
	{
		Q=encrypt(m,A.c,A.n);
		cout<<"Q:"<<Q<<endl;
	}

	void decrpyt_message_from(agent A)
	{
		Qhat=A.Q;
		mhat=decrpyt(Qhat);
		cout<<"Mhat:"<<mhat<<endl;
	}
};

void print(int A[], int k)
{
	for (int i = 0; i < k; i++)
	{
		cout<<"I:"<<i<<"\t\tA:"<<A[i]<<endl;
	}
}

int main(int argc, char const *argv[])
{
	struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);

	    /* using nano-seconds instead of seconds */
    srand((time_t)ts.tv_nsec);

	agent agent1(1),agent2(2);
	int A[1334]={0};
	int m=419;


	agent1.generate_key(false);
	agent1.print_key(2871);
	agent2.generate_encrypted_message(m,agent1);
	cout<<"M:"<<m<<"\t";
	agent1.decrpyt_message_from(agent2);

	// for(int i=0;i<10000;i++)
	// {
	// 	agent1.generate_key(false);
	// 	// agent1.print_key(2871);
	// 	agent2.generate_encrypted_message(419,agent1);
	// 	A[agent2.Q]++;
	// 	usleep(10);	
	// }
	// print(A,1334);
	
	

	// agent1.get_message_from(agent2);


	return 0;
}