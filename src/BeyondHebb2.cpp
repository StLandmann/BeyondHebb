//============================================================================
// Name        : BeyondHebb2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include<random>
#include<math.h>
#include<time.h>
#include <vector>
using namespace std;



int  TOTALNUMBEROFNEURONS, NUMBEROFITERATIONS;
const int NUMBERINLAYER[3]={3,3,2};
int BETA=1;
int THETA=3;
double DELTA=0.1;

#include "functions.h"

void userinput();
void initialize(Neuron& a);
void calculate_probabilities(Neuron& a);
void comparison_input_output(int& r,Neuron node);
void show_connections(Neuron node);
void show_state(Neuron node);
void set_input(Neuron& a);
long double calculate_normalizing(Neuron node, int layer);
void calculate_state(Neuron &node);
using namespace std;

int main() {
	srand((unsigned) time(NULL));
	userinput();
	Neuron node[::TOTALNUMBEROFNEURONS];	//Initialization of the nodes
	initialize(node);
	for(int iteration=0;iteration<::NUMBEROFITERATIONS;iteration++)
	{
	set_input(node);
	cout << "Iteration: " << iteration << endl;
	calculate_state(node);
	show_state(node);
	}
	show_connections(node);
//	show_state(node);
	return 0;
}
