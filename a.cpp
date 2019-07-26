#include <iostream>
#include <cstdlib>
#include <bits/stdc++.h>
#include <math.h>
#include <ctime>
#include <unistd.h>
#include <"rsa.h">
#define ll long long
using namespace std;

#define CHANNEL_CAP 3000


int count_nonzeros=0;

class agent
{
private:
	int p,q,phin,d;
	int mhat;
    int *coprimes=NULL;
    int no_coprimes=0;

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
	cout<<"Starting before actual Transmission codes"<<endl;
	cout<<"Channel capacity is "<<CHANNEL_CAP<<endl;
	print_list_of_avaiable_pq()

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




	return 0;
}
