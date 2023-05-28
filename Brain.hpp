
#pragma once

#define INPUTARRAYSIZE 128
#define BRAINARRAYSIZE 100

#include <string>
#include <vector>
#include "Neuron.hpp"

class Brain
{
private:
	Neuron* InputNetwork[INPUTARRAYSIZE]; //Create Multiple Networks to Handle Different Tasks
	Neuron* NeuralNetwork[BRAINARRAYSIZE][BRAINARRAYSIZE];
public:
	//Constructors & Destructors
	Brain();
	~Brain();

	//Etc
	//createDesiredPathway focuses on going towards a desired output
	void createDesiredPathway(std::string Input, std::string Output);
	//createRandomPathway focuses on creating random outputs til something works
	void createRandomPathway(std::string Input, std::string Output);
	//Also change createPathway() to store all possible inputs in array rather than dynamically
	//A relearn function to to hopefully find a faster pathway
	void followPathway(std::string Input, std::string& Output);
	void resetBreakCount(std::string Input); //Resets only the Neurons of this path
	void resetBreakCount(void); //Resets All Neurons
	void randomizePathway(std::string Input);
};

Brain::Brain() {
	for (int Index = 0; Index < INPUTARRAYSIZE; Index++)
	{
		this->InputNetwork[Index] = nullptr;
	}
}

Brain::~Brain() //Deallocate space when done
{
}


//Etc
void Brain::createDesiredPathway(std::string Input, std::string Output)
{
	//Intializes Input Array
	for (int Index1 = 0; Index1 < Input.length(); Index1++)
	{
		for (int Index2 = 0; Index2 < INPUTARRAYSIZE; Index2++)
		{
			//Adds new element to array if not already found
			if (this->InputNetwork[Index2] == nullptr)
			{
				this->InputNetwork[Index2] = new Neuron;//(Neuron*)malloc(sizeof(Neuron));
				this->InputNetwork[Index2]->setNeuronType((IOType)0);
				this->InputNetwork[Index2]->setNeuronSymbol(Input[Index1]);
				this->InputNetwork[Index2]->setOmnisConnections(nullptr);
				Index2 = INPUTARRAYSIZE;
			}
			//Skips to next input element if element already exists
			else if (this->InputNetwork[Index2]->getNeuronSymbol() == Input[Index1])
			{
				Index2 = INPUTARRAYSIZE;
			}
			else if (Index2 == INPUTARRAYSIZE - 1)
			{
				std::cout << "Input Array Data Exceeded" << std::endl;
				return;
			}
		}
		/*
		//int Index2 = 0;
		//while (Index2 < INPUTARRAYSIZE && this->Network[Index2] != nullptr && this->Network[Index2]->getNeuronSymbol() != Input[Index1])
		//{
		//	Index2++;
		//}

		//if (Index2 >= INPUTARRAYSIZE)
		//{
		//	std::cout << "No More Space for Inputs" << std::endl;
		//	return;
		//}
		//else if (Index2 < INPUTARRAYSIZE && this->Network[Index2] == nullptr)
		//{
		//	this->Network[Index2] = new Neuron;//(Neuron*)malloc(sizeof(Neuron));
		//	this->Network[Index2]->setNeuronType((IOType)0);
		//	this->Network[Index2]->setNeuronSymbol(Input[Index1]);
		//	this->Network[Index2]->setOmnisConnections(nullptr);
		//}
		*/
	}

	//Intializes desired output and connects to input array
	//Skip to Level of Complexity
	/*for (int Index0 = 0; Index0 < Output.length(); Index0++)
	{
		Neuron* nNeuron = new Neuron;
		nNeuron->setNeuronType((IOType)2);
		nNeuron->setNeuronSymbol(Output[Index0]);
		nNeuron->setOmnisConnections(nullptr);

		for (int Index1 = 0; Index1 < Input.length(); Index1++)
		{
			for (int Index2 = 0; Index2 < INPUTARRAYSIZE; Index2++)
			{
				if (this->Network[Index2] != nullptr && this->Network[Index2]->getNeuronSymbol() == Input[Index1])
				{
					this->Network[Index2]->setConnection(nNeuron);
				}
			}
		}
	}*/
	/*for (int Index1 = 0; Index1 < Input.length(); Index1++)
	{
		int Index2 = 0;
		while (Index2 < INPUTARRAYSIZE && this->Network[Index2] != nullptr && this->Network[Index2]->getNeuronSymbol() != Input[Index1])
		{
			//Probably don't need to check if this->Network[Index] != nullptr cause previous step does that
			Index2++;
		}

		if (this->Network[Index2] != nullptr && this->Network[Index2]->getNeuronSymbol() == Input[Index1])
		{
			//Probably don't need to check if this->Network[Index] != nullptr cause previous step does that
			Neuron* nNeuron = new Neuron;//(Neuron*)malloc(sizeof(Neuron));
			nNeuron->setOmnisConnections(nullptr);

			if (rand() % 2 == 0)
			{
				nNeuron->setNeuronType((IOType)1);
			}
			else
			{
				nNeuron->setNeuronType((IOType)2);
				nNeuron->setNeuronSymbol((unsigned char)rand() % INPUTARRAYSIZE);
			}
			nNeuron->setThreshold(rand() % ThresholdRange);

			Neuron* tNeuron = this->Network[Index2];
			while (tNeuron->getRandomConnection() != nullptr)
			{
				tNeuron = tNeuron->getRandomConnection();
			}
			tNeuron->setConnection(nNeuron);
		}
	}*/
	

	//Increases the level of complexity - might add more dynamic layering
	//Need a condition for if the input length is less than output length
	if (Input.length() > Output.length())
	{
		std::vector<Neuron*> Past;
		std::vector<Neuron*> Present;
		std::vector<Neuron*> Future;

		for (int Index1 = 0; Index1 < Input.length(); Index1++)
		{
			for (int Index2 = 0; Index2 < INPUTARRAYSIZE; Index2++)
			{
				if (this->InputNetwork[Index2] != nullptr && this->InputNetwork[Index2]->getNeuronSymbol() == Input[Index1])
				{
					this->InputNetwork[Index2]->setThreshold(1);
					Past.push_back(this->InputNetwork[Index2]);
				}
			}
		}

		for (int IndexLOC = Input.length(); IndexLOC - 1 > Output.length(); --IndexLOC)
		{
			for (int Index1 = 0; Index1 + 1 < IndexLOC; Index1++)
			{
				Neuron* nNeuron = new Neuron;
				nNeuron->setNeuronType((IOType)1);
				nNeuron->setBreakCount(0);
				nNeuron->setThreshold(IndexLOC);
				//nNeuron->setThreshold(1);

				Present.push_back(nNeuron);

				for (int Index2 = 0; Index2 < Past.size(); Index2++)
				{
					Past[Index2]->setConnection(nNeuron);
				}
			}

			Past = Present;
			Present = Future;
		}

		for (int Index0 = 0; Index0 < Output.length(); Index0++)
		{
			Neuron* nNeuron = new Neuron;
			nNeuron->setNeuronType((IOType)2);
			nNeuron->setBreakCount(0);
			nNeuron->setThreshold(Output.length());
			//nNeuron->setThreshold(2);
			nNeuron->setNeuronSymbol(Output[Index0]);
			//nNeuron->setOmnisConnections(nullptr);

			for (int Index1 = 0; Index1 < Output.length(); Index1++)
			{
				Past[Index1]->setConnection(nNeuron);
			}
		}
	}

	//Tunes mThreshold of Neurons til desired outcome is achieved

}

void Brain::followPathway(std::string Input, std::string& Output)
{
	for (int Index1 = 0; Index1 < Input.length(); Index1++)
	{
		int Index2 = 0;
		while (Index2 < INPUTARRAYSIZE && this->InputNetwork[Index2] != nullptr && this->InputNetwork[Index2]->getNeuronSymbol() != Input[Index1])
		{
			Index2++;
		}

		if (Index2 >= INPUTARRAYSIZE)
		{
			std::cout << "Input Not Found" << std::endl;
			return;
		}
		else if (Index2 < INPUTARRAYSIZE && this->InputNetwork[Index2] != nullptr)
		{
			this->InputNetwork[Index2]->Synapse(Output);
		}
	}
}

void Brain::resetBreakCount(std::string Input)
{
	for (int Index1 = 0; Index1 < Input.length(); Index1++)
	{
		for (int Index2 = 0; Index2 < INPUTARRAYSIZE; Index2++)
		{
			//Finds elements and resets them in a chain reaction
			if (this->InputNetwork[Index2] == nullptr)
			{
				Index2 = INPUTARRAYSIZE;
			}
			else if (this->InputNetwork[Index2]->getNeuronSymbol() == Input[Index1])
			{
				this->InputNetwork[Index2]->Reset();
			}
		}
	}
}


/*
void Brain::randomizePathway(std::string Input)
{
	for (int Index1 = 0; Index1 < Input.length(); Index1++)
	{
		int Index2 = 0;
		while (Index2 < INPUTARRAYSIZE && this->Network[Index2] != nullptr && this->Network[Index2]->getNeuronSymbol() != Input[Index1])
		{
			Index2++;
		}

		if (Index2 >= INPUTARRAYSIZE)
		{
			std::cout << "No More Space for Inputs" << std::endl;
			return;
		}
		else if (Index2 < INPUTARRAYSIZE && this->Network[Index2] != nullptr)
		{
			Neuron* tNeuron = this->Network[Index2]->getRandomConnection();

			while (tNeuron->getRandomConnection() != nullptr) // goes to end of network rather than random node
			{
				tNeuron = tNeuron->getRandomConnection();
			}
			tNeuron->setThreshold(rand() % ThresholdRange);
			tNeuron->setNeuronSymbol((unsigned char)rand() % 128);
		}
	}
}
*/