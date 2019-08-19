# rsa-encrpytion
## Description of files
1) __rsa.h__:	Contains mathematical and output related code snippets/functions
2) __agent.h__: Contains agent class and some beforehand computations relavent related to the agents
3) __data.txt__:Contains Information in order: |msg| best_p best_q; note that when p & q are 0 means no primes exists for that |msg|
4) __compute_all_max_eq_sizes.cpp__: Does the before hand task to Compute all possible |msg| v/s best p,q and and outputs that to class.txt in the above format. Code is One time run
5) __main.cpp__ : Main Runtime code, retrives the values from class.txt, and does some before hand computations after which it actually tests the transfer of information
6) __class.txt__: Contains infomation of all the elements in the chosen K-space in main.cpp


## How to run Files
To run the algorithm you need to decide the message space size first. Let your msg space size is |msg|. Then compute
```
	a = sqrt(5*|msg|)
	b = nearest_prime_from(a)  //Here b is the nearest prime from a
	
Then in compute_all_max_eq_sizes.cpp change.

```
	#define max_prime b
```

Note: Note that the algorithm for now doesn't support b greater than 1000, for that we need to change all int's to longs and update the prime number vectors in rsa.h

Then run. Note that you just have to run this file once

```
	g++ -std=c++17 compute_all_max_eq_sizes.cpp
	./a.out
```

Then go to main.cpp change 
```
	#define Size_req |msg|
```
