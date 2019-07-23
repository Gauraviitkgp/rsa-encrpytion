#include <iostream>
#include <cstdlib>
#include <bits/stdc++.h>
#include <math.h>
#include <ctime>
#include <unistd.h>
#define ll long long
using namespace std;



void printA(int A[], int k)
{
	for (int i = 0; i < k; i++)
	{
		cout<<"I:"<<i<<"\t\tA:"<<A[i]<<endl;
	}
}


class agent
{
private:
	int p,q,phin,d;
	int mhat;
    int *coprimes, no_coprimes=0;

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

    void compute_coprimes()
    {
        no_coprimes=0;
        for(int i=2; i<n;i++)
        {
            if(checkcoprime(i,phin))
            {
                coprimes[no_coprimes++]=i;
                cout<<coprimes[no_coprimes-1]<<" "<<flush;
            }
        }
    }

	void compute_pvt()
	{
		p=31;
		q=43;
		n=p*q;
		phin=(p-1)*(q-1);
		coprimes=new int[n];
		compute_coprimes();

        c=coprimes[rand()%no_coprimes];
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
		// cout<<"Q:"<<Q<<endl;
	}

	void decrpyt_message_from(agent A)
	{
		Qhat=A.Q;
		mhat=decrpyt(Qhat);
		// cout<<"Mhat:"<<mhat<<endl;
	}

	void get_decrypted_all_msg(int msg)
	{
	    for(int i=0; i < no_coprimes; i++)
        {
            c=coprimes[i];
            int enc=encrypt(msg,c,n);
            cout<<"c:"<<c<<"\tmsg:"<<msg<<"\tenc:"<<enc<<endl;
        }
	}
	int get_mhat()
	{
		return mhat;
	}
};



int main(int argc, char const *argv[])
{
	// struct timespec ts;
    // clock_gettime(CLOCK_MONOTONIC, &ts);

	    /* using nano-seconds instead of seconds */
    //

	agent agent1(1),agent2(2);
	int A[1334]={0};
	int m=419;


	agent1.generate_key(false);

	// cout<<"M:"<<m<<"\t";
	agent1.decrpyt_message_from(agent2);
	agent1.get_decrypted_all_msg(2);

	for(int i=30;i<44;i++)
	{
		m=6;
		agent2.generate_encrypted_message(m,agent1);
		agent2.Q=agent2.Q%i;
		agent1.decrpyt_message_from(agent2);
		cout<<"I:"<<i<<"\tM:"<<m<<"\tJ:"<<agent2.Q<<"\tMhat:"<<agent1.get_mhat()%i;
		if (agent1.get_mhat()%i==m)
			cout<<"\t\tMatch: True";
		else
			cout<<"\t\tMatch: False";
		cout<<endl;

		m=7;
		agent2.generate_encrypted_message(m,agent1);
		agent2.Q=agent2.Q%i;
		agent1.decrpyt_message_from(agent2);
		cout<<"I:"<<i<<"\tM:"<<m<<"\tJ:"<<agent2.Q<<"\tMhat:"<<agent1.get_mhat()%i;
		if (agent1.get_mhat()%i==m)
			cout<<"\t\tMatch: True";
		else
			cout<<"\t\tMatch: False";
		cout<<endl;

		m=35;
		agent2.generate_encrypted_message(m,agent1);
		agent2.Q=agent2.Q%i;
		agent1.decrpyt_message_from(agent2);
		cout<<"I:"<<i<<"\tM:"<<m<<"\tJ:"<<agent2.Q<<"\tMhat:"<<agent1.get_mhat()%i;
		if (agent1.get_mhat()%i==m)
			cout<<"\t\tMatch: True";
		else
			cout<<"\t\tMatch: False";
		cout<<endl<<endl;
		// usleep(10);
	}
	agent1.print_key(2971);
	// print(A,1334);



	// agent1.get_message_from(agent2);


	return 0;
}
