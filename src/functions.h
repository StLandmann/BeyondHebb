/*
 * functions.h
 *
 *  Created on: Oct 11, 2016
 *      Author: stefan
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <math.h>
using namespace std;

//Definition of the class 'Neuron' and its related functions

class Neuron
{

public:
	int number[3];
	long double connection[3];
	int  state;
	double probability;
	int get_number(int a){return number[a];};
	int get_state();
	double get_input(Neuron node[]);
	double get_probability(){return probability;}
	double get_connection(int a){return connection[a];}

	void set_connection(int a, long double b){connection[a]=b;}
	void set_state(int a){state=a;}
	void set_number(int a, int b){number[a]=b;}
	void set_probability(double normalizing, double input){probability=(1/normalizing)*exp(::BETA*input);}
	Neuron(){state=0;};
};

int Neuron::get_state()
{
	return state;
}


double Neuron::get_input(Neuron node[])
{
	double input=0;
	for(int i=0;i<::TOTALNUMBEROFNEURONS;i++)
	{	// cout << number[0] << " " << number[1] << endl;
		if(number[0]==node[i].get_number(0)+1)
		{
			input+=node[i].get_state()*node[i].get_connection(number[1]);
		//	cout << endl;
		//	cout << number[0] << " " <<i << " " <<  number[1] << " " << node[i].get_connection(number[1]) << endl;
		}
	}
	return input;
}
//End of definition of class 'Neuron'
//Userinput

void userinput()
{
	cout <<"Please enter the number of the first, the second and the third layer and the number of iterations:" << endl;
//	cin >> ::NUMBERINLAYER[0];
//	cin>>::NUMBERINLAYER[1];
//	cin>> ::NUMBERINLAYER[2];
	cin >> ::NUMBEROFITERATIONS;
	for(int i=0;i<3;i++)
	{
	::TOTALNUMBEROFNEURONS+=::NUMBERINLAYER[i];
	}
}
//End Userinput

//Initialize
void initialize(Neuron node[])
{
	for(int i=0;i<::TOTALNUMBEROFNEURONS;i++)
	{
		node[i].set_state(0);
		node[i].set_number(2,i);
		if(i<NUMBERINLAYER[0])
		{
			node[i].set_number(0,0);
			node[i].set_number(1,i);
			for(int j=0;j<NUMBERINLAYER[1];j++)
			{
			node[i].set_connection(j,(long double) rand()/RAND_MAX);
			}
		}

		if(i>=NUMBERINLAYER[0] && i<NUMBERINLAYER[0]+NUMBERINLAYER[1])
		{
			node[i].set_number(0,1);
			node[i].set_number(1,i-NUMBERINLAYER[0]);
			for(int j=0;j<NUMBERINLAYER[2];j++)
			{
			node[i].set_connection(j,(long double) rand()/RAND_MAX);
		//	cout << i << " " << j << " " << node[i].get_connection(j) << endl;
			}
		}
		if(i>=NUMBERINLAYER[0]+NUMBERINLAYER[1])
		{
			node[i].set_number(0,2);
			node[i].set_number(1,i-NUMBERINLAYER[0]-NUMBERINLAYER[1]);
		}
	}
}
//End initialize
//Show connections
void show_connections(Neuron node[])
{
	for(int i=0;i<::TOTALNUMBEROFNEURONS;i++)
	{
			for(int j=0;j<::NUMBERINLAYER[node[i].get_number(0)+1];j++)
			{
			cout << i << " " << j << " " <<  node[i].get_connection(j) << endl;
			}
			cout << endl;
		}
}
//End Show Connections
//Set Input
void set_input(Neuron node[])
{
	node[0].set_state(1);
	node[1].set_state(round((long double) rand()/RAND_MAX));
	node[2].set_state(round((long double) rand()/RAND_MAX));
}
//End input
//Show state
void show_state(Neuron node[])
{
	for(int i=0;i<::TOTALNUMBEROFNEURONS;i++)
	{
		cout << node[i].get_state();
		if(i==::NUMBERINLAYER[0]-1 || i==::NUMBERINLAYER[0]+NUMBERINLAYER[1]-1)
		{
			cout << endl;
		}
	}
	cout << endl;
}
//Calculate normalizing
long double calculate_normalizing(Neuron node[], int layer)
{
	long double normalizing=0;

	for(int i=0;i<::TOTALNUMBEROFNEURONS;i++)
	{
		if(node[i].get_number(0)==layer)
		{//	cout << i << endl;
		 //	cout << node[i].get_input(node) << endl;
			normalizing+=exp(::BETA*node[i].get_input(node));
		}
	}

	return normalizing;
}
//end calculate normalizing
//Calculate state
void calculate_state(Neuron node[])
{
	for(int layer=1;layer<3;layer++)
	{
		for(int j=0;j<::TOTALNUMBEROFNEURONS;j++)
		{	//cout << node[j].get_number(0)<< endl;
			if(node[j].get_number(0)==layer)
			{
		//	cout << "layer " << layer<< " input " << node[j].get_input(node) << endl;

			node[j].set_probability(calculate_normalizing(node,layer),node[j].get_input(node));
			node[j].set_state(0);
			}

		}
		//Hier wird der Knoten ausgesucht der feuert
		//First: Sort probabilities

		const int a=::NUMBERINLAYER[layer];
		long double* probability= new long double[a];
		int		*	listofNodes= new int[a];
		int tempCounter=0;

		for(int j=0;j<::TOTALNUMBEROFNEURONS;j++)
		{
			if(node[j].get_number(0)==layer)
			{
				probability[tempCounter]=node[j].get_probability();
				listofNodes[tempCounter]=node[j].get_number(2);
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
			for(int i=0;i<::NUMBERINLAYER[layer]-1;i++)
			{
				// cout << probability[i] << " und " << probability[i+1]<< endl;
				if(probability[i]>probability[i+1])
				{
					long double probTemp=probability[i+1];
					probability[i+1]=probability[i];
					probability[i]=probTemp;
					int numberTemp=listofNodes[i+1];
					listofNodes[i+1]=listofNodes[i];
					listofNodes[i]=numberTemp;
					loopVariable=0;
				//	for(int k=0;k<::NUMBERINLAYER[layer];k++)
				//	{
				//			cout << probability[k] << " " ;
				//	}
				//	cout << endl;
				//	for(int k=0;k<::NUMBERINLAYER[layer];k++)
				//	{
				//		cout << listofNodes[k] << " " ;
				//	}
			 // 	cout << endl;
				}
			}
		}
		//Probabilities sorted in list listofNodes and probability
		long double tempRandom=(long double)rand()/RAND_MAX;
		int loopVariable2=0;
		int counterTemp2=0;
		long double tempProbCount=0;


		while(loopVariable2==0)
		{
	//		cout << tempProbCount << " < " << tempRandom << " < "<< probability[::NUMBERINLAYER[layer]-counterTemp2-1] << endl;
		if(tempProbCount<=tempRandom && tempRandom < tempProbCount+probability[::NUMBERINLAYER[layer]-counterTemp2-1])
		{
			node[listofNodes[::NUMBERINLAYER[layer]-counterTemp2-1]].set_state(1);
			loopVariable2=1;
		}
		tempProbCount+=probability[::NUMBERINLAYER[layer]-counterTemp2-1];
		counterTemp2++;
		}
			//End set state


	}

}
#endif /* FUNCTIONS_H_ */
