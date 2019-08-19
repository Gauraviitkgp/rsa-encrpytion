#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <cstdlib>
#include "rsa.h"	//Header File for Math related to rsa operations
#include "agent.h" //Header File for Agent Related operations

using namespace std;

int main(int argc, char const *argv[])
{
	ifstream classfile;
	classfile.open("class.txt");

	string temp;

	classfile>>temp;
	P_chosen = stoi(temp);
	classfile>>temp;
	Q_chosen = stoi(temp);

	agent Ben(1), Howie(2);

	Ben.generate_static_keys();


	vector<int> k(Ben.n);


	
	return 0;
}

