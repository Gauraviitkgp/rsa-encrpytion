#include <iostream>
#include <cstdlib>
#include <bits/stdc++.h>
#include <math.h>
#include <ctime>
#include <unistd.h>
#define ll long long
using namespace std;

#define PP 31
#define QP 43

int count_nonzeros=0;

void printA(int A[], int k, bool print_zeros)
{
    count_nonzeros=0;
	for (int i = 0; i < k; i++)
	{
	    if(print_zeros)
            cout<<"I:"<<i<<"\t\tA:"<<A[i]<<endl;
        else
        {
            if(A[i]!=0)
            {
                cout<<"I:"<<i<<"\t\tA:"<<A[i]<<endl;
                count_nonzeros++;
            }
        }

	}
}

void countA(int A[], int k)
{
    count_nonzeros=0;
	for (int i = 0; i < k; i++)
        if(A[i]!=0)
            count_nonzeros++;
}


class agent
{
private:
	int p,q,phin,d;
	int mhat;
    int *coprimes=NULL;
    int no_coprimes=0;
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
		p=PP;
		q=QP;
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

	void get_decrypted_all_msg(int msg, int A[], bool verbose)
	{
	    for(int i=0; i < no_coprimes; i++)
        {
            c=coprimes[i];
            int enc=encrypt(msg,c,n);
            if(verbose)
                cout<<"i:"<<i<<"\tc:"<<c<<"\tmsg:"<<msg<<"\tenc:"<<enc<<endl;
            A[enc]++;
        }
	}
	int get_mhat()
	{
		return mhat;
	}
};


void message_to_encryptionspace(int m, agent agent1, agent agent2, int A[], bool verbose)
{
	cout<<"M:"<<m;
	agent1.decrpyt_message_from(agent2);
	agent1.get_decrypted_all_msg(m,A,verbose);
    countA(A,PP*QP+1);
	cout<<"\tNon Zeros:"<<count_nonzeros<<endl;
}

int main(int argc, char const *argv[])
{
	// struct timespec ts;
    // clock_gettime(CLOCK_MONOTONIC, &ts);

	    /* using nano-seconds instead of seconds */
    //

	agent agent1(1),agent2(2);
	agent1.generate_key(false);
	int A[PP*QP+1]={0};

	// cout<<"M:"<<m<<"\t";
    int K[24], k=0;
    cout<<"Printing total mappings for each message "<<endl;
    for(int i=0; i <PP*QP;i++)
    {
        int A[PP*QP+1]={0};
        message_to_encryptionspace(i,agent1,agent2,A,false);
        if(count_nonzeros==4)
            K[k++]=i;
    }

    cout<<"Printing mappings for msg=4 "<<endl;
    for(int j=0;j<k;j++)
    {
        int A[PP*QP+1]={0};
        message_to_encryptionspace(K[j],agent1,agent2,A,false);
        printA(A,PP*QP+1,false);
        cout<<endl;
    }


    /*
    int B[PP*QP+1]={0};
    message_to_encryptionspace(3,agent1,agent2,B,false);
    printA(B,1334,false);

    int C[PP*QP+1]={0};
    message_to_encryptionspace(9,agent1,agent2,C,false);
    printA(C,1334,false);

    int D[PP*QP+1]={0};
    message_to_encryptionspace(10,agent1,agent2,D,false);
    printA(D,1334,false);
    */
	/*
	m=2;
	cout<<"M:"<<m<<endl;
	agent1.decrpyt_message_from(agent2);
	agent1.get_decrypted_all_msg(m,A,false);
    printA(A,1334,false);
	cout<<"Non Zeros:"<<count_nonzeros<<endl<<endl;

    m=3;
    cout<<"M:"<<m<<endl;
	A[1334]={0};
	agent1.get_decrypted_all_msg(m,A,false);
    printA(A,1334,false);
	cout<<"Non Zeros:"<<count_nonzeros<<endl<<endl;

    m=4;
    cout<<"M:"<<m<<endl;
	A[1334]={0};
	agent1.get_decrypted_all_msg(m,A,false);
    printA(A,1334,false);
	cout<<"Non Zeros:"<<count_nonzeros<<endl<<endl;

	m=37;
    cout<<"M:"<<m<<endl;
	A[1334]={0};
	agent1.get_decrypted_all_msg(m,A,false);
    printA(A,1334,false);
	cout<<"Non Zeros:"<<count_nonzeros<<endl<<endl;
	*/

    /*
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
    */


	// agent1.get_message_from(agent2);


	return 0;
}
