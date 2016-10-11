//============================================================================
// Name        : BeyondHebb.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include<random>
#include<math.h>
#include<time.h>
#include <vector>
using namespace std;

int NUMBERINI, NUMBERINJ, NUMBERINK, TOTALNUMBEROFNEURONS, NUMBEROFITERATIONS;
int BETA=100;
int THETA=3;
double DELTA=0.1;

#include "functions.h"

void userinput();
void initialize(Neuron& a);
void calculate_probabilities(Neuron& a);
void comparison_input_output(int& r,Neuron node);
int main() {
srand((unsigned) time(NULL));

//Initialization of the network
userinput();							//Userinput, number of nodes in each layer
Neuron node[::TOTALNUMBEROFNEURONS];	//Initialization of the nodes
initialize(node);

//End initialization of the network
//Loop

for(int iteration=0;iteration<::NUMBEROFITERATIONS;iteration++)
{	node[0].set_state(1);
	node[1].set_state(round((long double)rand()/RAND_MAX));
	node[2].set_state(round((long double)rand()/RAND_MAX));

	for(int i=2;i<4;i++)
	{	long double normalizing=0;
		//Calculation of normalizing factor
		for(int j=0;j<::TOTALNUMBEROFNEURONS;j++)
		{
		if(node[j].get_layer()==i)
		{
		normalizing+=exp(::BETA*node[j].get_input(node));
		}
		}
		//End normalizing factor
		//Set probabilities
		for(int j=0;j<::TOTALNUMBEROFNEURONS;j++)
		{
			if(node[j].get_layer()==i)
			{	double tempInput=node[j].get_input(node);
				node[j].set_probability(normalizing,tempInput);
			//	cout << node[j].get_probability() << endl;
			}
		}
		//End set probabilities
		//Set state
		int NumberofNodesini=0;
		for(int j=0;j<::TOTALNUMBEROFNEURONS;j++)
			{
				if(node[j].get_layer()==i)
				{
					NumberofNodesini++;
					node[j].set_state(0);
				}

			}
		long double probability[NumberofNodesini];
		int			listofNodes[NumberofNodesini];
		int tempCounter=0;
		for(int j=0;j<::TOTALNUMBEROFNEURONS;j++)
		{
			if(node[j].get_layer()==i)
			{
				probability[tempCounter]=node[j].get_probability();
				listofNodes[tempCounter]=node[j].get_number();
				tempCounter++;
			}
		}
		int loopVariable=0;
		while(loopVariable==0)
		{
		//	for(int k=0;k<NumberofNodesini;k++)
		//	{
		//		 cout << probabilities[i];
		//	}
		//	cout << endl;

			loopVariable=1;
			for(int i=0;i<NumberofNodesini-1;i++)
			{
				//cout << probability[i] << " und " << probability[i+1]<< endl;
				if(probability[i]>probability[i+1])
				{
					long double probTemp=probability[i+1];
					probability[i+1]=probability[i];
					probability[i]=probTemp;
					int numberTemp=listofNodes[i+1];
					listofNodes[i+1]=listofNodes[i];
					listofNodes[i]=numberTemp;
					loopVariable=0;
	//			for(int k=0;k<NumberofNodesini;k++)
	//				{
	//					cout << probability[k] << " " ;
	//				}
	//				cout << endl;
				}
			}
		}
		long double tempRandom=(long double)rand()/RAND_MAX;
		int loopVariable2=0;
		int counterTemp2=0;
		long double tempProbCount=0;
		while(loopVariable2==0)
		{
		//	cout << tempRandom << " and " << probability[NumberofNodesini-counterTemp2-1] << endl;
			if(tempProbCount<=tempRandom && tempRandom < tempProbCount+probability[NumberofNodesini-counterTemp2-1])
			{
				node[listofNodes[NumberofNodesini-counterTemp2-1]].set_state(1);
				loopVariable2=1;
			}
			tempProbCount+=probability[NumberofNodesini-counterTemp2-1];
			counterTemp2++;
		}

		//End set state
	}
	//Comparison with the XOR rule
	int r=0;  //Feedback
	comparison_input_output(r,node);
	//End Comparison with the XOR rule
	cout << r << endl;
	//Nun muss das Feedback Signal jeder aktiven Synapse nach der angegebenen Regel aktualisiert werden
	//Changing memory
	for(int i=0;i<::TOTALNUMBEROFNEURONS;i++)
	{
		for(int j=0;j<::TOTALNUMBEROFNEURONS;j++)
		{
			if((node[i].get_layer()==1 && node[j].get_layer()==3) || (node[i].get_layer()==2 && node[j].get_layer()==2)){node[i].set_connection(j,0);}
			if((node[i].get_layer()==2 && node[j].get_layer()==1) || (node[i].get_layer()==1 && node[j].get_layer()==1) ){node[i].set_connection(j,0);}
			if(node[i].get_layer()==3){node[i].set_connection(j,0);}
			if((node[i].get_state()==1&&node[j].get_state()==1) && (node[i].get_layer()==node[j].get_layer()-1))
			{
				if(node[i].get_memory(j)-r<0)
				{
					node[i].set_memory(j,0);
				}
				if(node[i].get_memory(j)-r>=0 && node[i].get_memory(j)-r<::THETA)
				{
					node[i].set_memory(j,node[i].get_memory(j)-r);
				}
			//	cout << node[i].get_memory(j)-r << endl;
				if(node[i].get_memory(j)-r+1>::THETA)
				{
					node[i].set_memory(j,::THETA);
				//	cout << node[i].get_connection(j) << " und dann "
				//	if(node[i].get_connection(j)-::DELTA>=0)
				//	{
					cout << "Reduction" << endl;
					node[i].set_connection(j,node[i].get_connection(j)-::DELTA);
					for(int x=0;x<::TOTALNUMBEROFNEURONS;x++)
					{
						for(int y=0;y<::TOTALNUMBEROFNEURONS;y++)
						{
							if((x!=i || y!=j) && (node[x].get_layer()==node[y].get_layer()-1))
							{
								node[x].set_connection(j,node[x].get_connection(y)+::DELTA/100);
							}
						}
					}

					}

				//	cout << node[i].get_connection(j) << endl;
			//}
		}
	}
	}
//	for(int k=0;k<3;k++)
//	{
//		cout << node[k].get_state();
//	}
//	cout << endl;
//	for(int k=3;k<6;k++)
//		{
//			cout << node[k].get_state();
//		}
//	cout  <<endl;
//	for(int k=6;k<8;k++)
//		{
//			cout << node[k].get_state() ;
//		}
//	cout << endl;
//	for(int i=0;i<::TOTALNUMBEROFNEURONS;i++)
//	{
//		for(int j=0;j<::TOTALNUMBEROFNEURONS;j++)
//		{
//		cout << node[i].get_memory(j) <<"   ";
//		}
//		cout << endl;
//	}
//	cout << endl;


	for(int i=0;i<::TOTALNUMBEROFNEURONS;i++)
		{
			for(int j=0;j<::TOTALNUMBEROFNEURONS;j++)
			{
			cout << node[i].get_connection(j) <<"   ";
			}
			cout << endl;
	}
}

return 0;
}
