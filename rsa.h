#ifndef __RSA_H__ // include guard
#define __RSA_H__

#include <iostream>
#include <array>
#include <iterator>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <chrono>
#include <set>
using namespace std;
using namespace std::chrono;

namespace 
{
	std::vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997};
	int total_primes = primes.size();
	high_resolution_clock::time_point t1,t2,t3,t4,t5;


	void printarray(int A[],int size)
	{
		for (int i = 0; i < size; ++i)
			cout<<"A["<<i<<"]:"<<A[i]<<endl;
	}

	template <typename T> 
	void printvec(std::vector<T>& A)
	{
		for (int i = 0; i < A.size(); ++i)
			cout<<"A["<<i<<"]:"<<A[i]<<endl;
	}

	void randomise_seed()
	{
		// RANDOMISING SEED
		struct timespec ts;
	    clock_gettime(CLOCK_MONOTONIC, &ts);

	    /* using nano-seconds instead of seconds */
	    srand((time_t)ts.tv_nsec);
	}

	void compute_opt_possible_pairs(int capacity, std::vector<int>& p, std::vector<int>& q,bool verbose)
	{
		int flag=0;
		int i=0;
		for (int j = primes.size()-1; i < j; )
		{
			if (primes[i]*primes[j]>capacity)
			{
				if(flag)
				{
					p.push_back(primes[i-1]);
					q.push_back(primes[j]);
					if(verbose)
						cout<<"n:"<<p[p.size()-1]*q[q.size()-1]<<"\tp:"<<p[p.size()-1]<<"\tq:"<<q[q.size()-1]	<<endl;
				}
				j--;
				flag=0;
			}
			else
			{
				flag=1;
				i++;
			}
		}
	}// 13 19: 8 14 8 14 9 

	void compute_all_possible_pairs(int capacity, std::vector<int>& p, std::vector<int>& q,bool verbose)
	{
		int flag=0;
		int i=0;
		for (int j = primes.size()-1; i < j; )
		{
			if (primes[i]*primes[j]>capacity)
			{
				i=0;
				j--;
				flag=0;
			}
			else
			{
				p.push_back(primes[i]);
				q.push_back(primes[j]);
				if(verbose)
					cout<<"n:"<<p[p.size()-1]*q[q.size()-1]<<"\tp:"<<p[p.size()-1]<<"\tq:"<<q[q.size()-1]<<endl;

				flag=1;
				i++;
			}
		}
	}


	int mappings(int map[], int size, bool print_zeros)
	{
		int count_nonzeros=0;
		if (print_zeros)
			printarray(map,size);
		else
		{
			for (int i = 0; i < size; i++)
			{
	            if(map[i]!=0)
	            {
	                cout<<"map["<<i<<"]:"<<map[i]<<endl;
	                count_nonzeros++;
	            } 
		    }
		}
		return count_nonzeros;
	}

	int count_non_zeros_array(int A[], int k)
	{
	    int count=0;
		for (int i = 0; i < k; i++)
	        if(A[i]!=0)
	            count++;
	    return count;
	}

	int count_non_zeros_vec(std::vector<int>& A)
	{
	    int count=0;
		for (int i = 0; i < A.size(); i++)
	        if(A[i]!=0)
	            count++;
	    return count;
	}

	int count_non_zeros_vec(std::vector<int>& A,std::vector<int>& K)
	{
	    int count=0;
		for (int i = 0; i < A.size(); i++)
		{
	        if(A[i]!=0)
	        {
	            count++;
	            K.push_back(i);
	        }
		}
	    return count;
	}

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
	


}
#endif