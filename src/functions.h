/*
 * functions.c

 *
 *  Created on: Oct 8, 2016
 *      Author: stefan
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_
#include <math.h>
using namespace std;

//Definition of the class 'Neuron' and its related functions

class Neuron
{
	int layer_;
	int number_;
public:
	vector<double>  connection;
	int  state;
	double probability;
	vector<double> memory;

	int get_number(){return number_;};
	int get_state();
	double get_connection(int);
	double get_input(Neuron node[]);
	int    get_layer(){return layer_;};
	double get_probability(){return probability;}
	double get_memory(int);
	void set_layer(int a){layer_=a;}
	void set_state(int a){state=a;}
	void set_number(int a){number_=a;}
	void set_connection(int a,double b){connection[a]=b;}
	void set_memory(int a,double b){memory[a]=b;}
	void set_probability(double normalizing, double input){probability=(1/normalizing)*exp(::BETA*input);}
	void init_connections( int a)
	{
		connection.reserve(a);
		for(int i=0;i<a;i++)
		{
		connection[i]=0.5;//long double)rand()/RAND_MAX;
		}
	}
	void init_memory( int a)
	{
		memory.reserve(a);
		for(int i=0;i<a;i++)
		{
		memory[i]=0;
	//	memory[i]=(long double)rand()/RAND_MAX;
		}
	}
	Neuron(){state=0;};
};

int Neuron::get_state()
{
	return state;
}

double Neuron::get_connection(int a)
{
	return connection[a];
}

double Neuron::get_memory(int a)
{
	return memory[a];
}
double Neuron::get_input(Neuron node[])
{	double input=0;
	for(int i=0;i<::TOTALNUMBEROFNEURONS;i++)
	{
		if(node[i].get_layer()==node[number_].get_layer()-1 && node[i].get_state()==1)
		{
			input+=node[i].get_connection(number_);

		}
	}
	return input;
}


//End of definition of class 'Neuron'


//Userinput

void userinput()
{
	cout <<"Please enter the number of the first, the second and the third layer and the number of iterations:" << endl;
	cin >> ::NUMBERINI;
	cin >> ::NUMBERINJ;
	cin >> ::NUMBERINK;
	cin >> ::NUMBEROFITERATIONS;
	::TOTALNUMBEROFNEURONS=::NUMBERINI+::NUMBERINJ+::NUMBERINK;
}
//End Userinput

//Initialize
void initialize(Neuron node[])
{
for(int i=0;i<NUMBERINI;i++)
{
		node[i].set_layer(1);

}
for(int i=NUMBERINI;i<NUMBERINI+NUMBERINJ;i++)
{
		node[i].set_layer(2);
}
for(int i=NUMBERINJ+NUMBERINI;i<::TOTALNUMBEROFNEURONS;i++)
{
	node[i].set_layer(3);

}
for(int i=0;i<::TOTALNUMBEROFNEURONS;i++)
{
	node[i].set_number(i);
}

for(int i=0;i<TOTALNUMBEROFNEURONS;i++)
{

		node[i].init_connections(::TOTALNUMBEROFNEURONS);
		node[i].init_memory(::TOTALNUMBEROFNEURONS);

}
}
//End initialize

//Comparison input output
void comparison_input_output(int& r, Neuron node[])
{
//	cout << node[1].get_state() << " " << node[2].get_state() << endl;
//		cout << node[6].get_state() << " " << node[7].get_state() << endl;
			if((node[1].get_state()==0 && node[2].get_state()==0) && (node[6].get_state()==1 && node[7].get_state()==0)){r=1;}
			if((node[1].get_state()==0 && node[2].get_state()==0) && (node[6].get_state()==0 && node[7].get_state()==1)){r=-1;}
			if((node[1].get_state()==1 && node[2].get_state()==0) && (node[6].get_state()==1 && node[7].get_state()==0)){r=-1;}
			if((node[1].get_state()==1 && node[2].get_state()==0) && (node[6].get_state()==0 && node[7].get_state()==1)) {r=1;}
			if((node[1].get_state()==0 && node[2].get_state()==1) && (node[6].get_state()==0 && node[7].get_state()==1)){r=1;}
			if((node[1].get_state()==0 && node[2].get_state()==1) && (node[6].get_state()==1 && node[7].get_state()==0)){r=-1;}
			if((node[1].get_state()==1 && node[2].get_state()==1) && (node[6].get_state()==1 && node[7].get_state()==0)){r=1;}
			if((node[1].get_state()==1 && node[2].get_state()==1) && (node[6].get_state()==0 && node[7].get_state()==1)){r=-1;}
			if((node[6].get_state()==0 && node[7].get_state()==0)){r=-1;}
			if((node[6].get_state()==1 && node[7].get_state()==1)){r=-1;}

}

#endif
