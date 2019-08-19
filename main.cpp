#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <cstdlib>
#include "rsa.h"	//Header File for Math related to rsa operations
#include "agent.h" //Header File for Agent Related operations

#define Size_req 1024	//Requirement of Message space Size
#define FILE false		//Do you want file output?
using namespace std;

void read_from_file(vector< vector <long> >& data, string filename)
{
	ifstream datafile;			//File pointer
	datafile.open(filename);
	
	vector<long> line;			//Vector for storing each line of the file
	string stemp;				//Temporary store as String
	long itemp;					//Temporary store as int

	while(1)
	{
		datafile>>stemp;		
		itemp = stoi(stemp);	//Conversion

		if(datafile.eof() || itemp > Size_req )
			break;

		line.clear();

		line.push_back(itemp);
		
		for (int i = 0; i < 2; i++)
		{
			datafile>>stemp;
			itemp = stoi(stemp);
			line.push_back(itemp);	
		}

		data.push_back(line);
	}
	datafile.close();
}

void select_pq(vector< vector <long> > data, vector<int>& k)
{
	int i = Size_req; 		//Try for max size and then reduce till we find a p and q such that eq size exists
	while(data[i][1]==0)
		i--;
	P_chosen = data[i][1];	//Get the first prime
	Q_chosen = data[i][2];	//Get the Second Prime
	k.resize(data[i][0]); 	//Allocating the size of this possible size data to |K| 
}

void get_k(agent X, vector<int>& k)
{
	int i=0;
	vector<int> FALTU; 			//FALTU in hindi means not required
	vector< vector <int> > classes =  compute_equivalence_size_opt(X, FALTU, false); //get classes;

	while(classes[i].size() != k.size()) //Find the equivalence class of size equalto |K|
		i++;

	k.assign(classes[i].begin(), classes[i].end()); // Assignement of all values of k
}


int main(int argc, char const *argv[])
{
	/*----------------------------DECLARATIONS--------------------------*/
	vector< vector <long> > data;	//Stores Data
	vector<int> k;					//A map from m to k //where k is vector space containing all numbers from equivalence classes to send
	string filename = "data.txt";	//Filename where data is present
	agent ben(1),howie(2);			//Declaration of agents

	/*----------------------------GETTING THE K-SPACE-------------------*/
	read_from_file(data, filename); //Function to read data

	select_pq(data,k);				//Selects PQ from datafiles & get k space its size

	ben.generate_static_keys();		//Generates a static keys (n,Phin, coprimes etc)

	get_k(ben, k);					//Gets the elements in K-space


	/*-----------------------------TESTING THE ALGORITHM----------------*/
	randomise_seed();				//Randomize seed to produce random set of e

	int no_of_msgs=1000,msg;		//No of test msgs

	for (int i = 0; i < no_of_msgs; i++)	//A loop for testing the code
	{
		msg = rand()%k.size();			//Generate Random message// here msg is the input to the algorithm
		ben.generate_pvt_random_keys();	//Generate a random e everytime
		howie.generate_encrypted_message(k[msg],ben);	//Generate an encrpyted msg //agent Howie Does that// msg is transfomed to K space before sending it to the encyption algo
		ben.decrpyt_message_from(howie);//Ben decrpyts the message from Howie in K space
		vector<int>::iterator it = find(k.begin(), k.end(), ben.get_mhat()); // Inverse transformation from K space to message space
		cout<<"Msg:"<<msg<<"\t\tKmsg:"<<k[msg]<<"\tenc:"<<howie.J<<"\tKdec:"<<ben.get_mhat()<<"\tdec:"<<it - k.begin()<< endl; //Visual outputs for user

	}

	/*----------------------------FILE IO--------------------------------*/
	if(FILE)
	{
		ofstream myfile;
		
		myfile.open("class.txt");	//Filename is class.txt

		myfile<<P_chosen<<" "<<Q_chosen<<" "<<ben.n<<endl; // First line signifies P Q and n

		for (int i = 0; i < k.size(); i++)
			myfile<<k[i]<<endl;		//Next lines signify each elements of k space;
		myfile.close();				//Close File
	}


	return 0;
}