
#pragma once

#define INPUTARRAYSIZE 128
#define BRAINARRAYSIZE 100
#define OUTPUTARRAYSIZE 1000

#include <string>
#include <vector>
#include "Neuron.hpp"

class Brain
{
private:
	Neuron* InputNetwork[INPUTARRAYSIZE]; //Create Multiple Networks to Handle Different Tasks
	//Neuron* NeuralNetwork[BRAINARRAYSIZE][BRAINARRAYSIZE];
	Neuron* OutputNetwork[OUTPUTARRAYSIZE];
public:
	//Constructors & Destructors
	Brain();
	~Brain();

	//Computer Vision


	//Etc
	//createDesiredPathway focuses on going towards a desired output
	void createDesiredPathway(std::string Input, std::string Output);
	void testDesiredPathwayFunction(void);

	//createRandomPathway focuses on creating random outputs til something works
	void createRandomPathway(std::string Input[], std::string Output[]);
	void testRandomPathwayFunction(void);

	//Also change createPathway() to store all possible inputs in array rather than dynamically
	//A relearn function to to hopefully find a faster pathway

	std::vector<Neuron*> followPathway(std::string Input, std::string& Output);
	void resetBreakCount(std::string Input); //Resets only the Neurons of this path
	void resetBreakCount(void); //Resets All Neurons
	void randomizePathway(std::string Input);
};

Brain::Brain() {
	for (int Index = 0; Index < INPUTARRAYSIZE; Index++)
	{
		this->InputNetwork[Index] = nullptr;
	}
	for (int Index = 0; Index < OUTPUTARRAYSIZE; Index++)
	{
		this->OutputNetwork[Index] = nullptr;
	}

	//Input Array Initializer
	this->InputNetwork[0] = new Neuron;//(Neuron*)malloc(sizeof(Neuron));
	this->InputNetwork[0]->setNeuronType((IOType)0);
	this->InputNetwork[0]->setNeuronSymbol('+');
	this->InputNetwork[0]->setAllConnections(nullptr);

	int Index0 = 1;
	for (int Index1 = 0; Index1 < 2; Index1++)
	{
		for (int Index2 = 0; Index2 < 10; Index2++, Index0++)
		{
			this->InputNetwork[Index0] = new Neuron;//(Neuron*)malloc(sizeof(Neuron));
			this->InputNetwork[Index0]->setNeuronType((IOType)0);
			this->InputNetwork[Index0]->setNeuronSymbol(Index2 + 48);
			this->InputNetwork[Index0]->setAllConnections(nullptr);
		}
	}
}

Brain::~Brain() //Deallocate space when done
{
}


//Etc
void Brain::createDesiredPathway(std::string Input, std::string Output)
{
	//Intializes Input Array - Either Have this intialization or the brain constructor one
	/*for (int Index1 = 0; Index1 < Input.length(); Index1++)
	{
		for (int Index2 = 0; Index2 < INPUTARRAYSIZE; Index2++)
		{
			//Adds new element to array if not already found
			if (this->InputNetwork[Index2] == nullptr)
			{
				this->InputNetwork[Index2] = new Neuron;//(Neuron*)malloc(sizeof(Neuron));
				this->InputNetwork[Index2]->setNeuronType((IOType)0);
				this->InputNetwork[Index2]->setNeuronSymbol(Input[Index1]);
				this->InputNetwork[Index2]->setAllConnections(nullptr);
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

			//Puts newly created neuron into Output Array
			int Index1;
			for (Index1 = 0; Index1 < OUTPUTARRAYSIZE && OutputNetwork[Index1] != nullptr; Index1++)
			{
			}
			if (Index1 == OUTPUTARRAYSIZE)
				std::cout << "Output Array Maxed Out" << std::endl;
			else
				OutputNetwork[Index1] = nNeuron;

			nNeuron->setNeuronType((IOType)2);
			nNeuron->setBreakCount(0);
			nNeuron->setThreshold(Output.length());
			nNeuron->setNeuronSymbol(Output[Index0]);

			for (int Index1 = 0; Index1 < Output.length(); Index1++) //Leads to double output w/ the '<=' vs a '<'
			{
				Past[Index1]->setConnection(nNeuron);
			}
		}
	}

	//Get rid of comment bracket for error correction
	///*

	std::string actualOutput;
	followPathway(Input, actualOutput);
	//while (actualOutput != Output) //Might want operation to happen at least once
	{
		if (false) //Need to add check that verifies there are neurons in output array
		{
			std::cout << "No Output Neurons Found" << std::endl;
		}
		else //Re-adjusts Output array so that old outputs are subsituted with new ones
		{
			std::vector<Neuron*> TempOutputVector;
			for (int Index0 = 0; Index0 < OUTPUTARRAYSIZE; Index0++)
			{
				if (OutputNetwork[Index0] != nullptr && OutputNetwork[Index0]->getActivation())
				{
					TempOutputVector.push_back(OutputNetwork[Index0]);
					OutputNetwork[Index0]->setNeuronType((IOType)1);
					OutputNetwork[Index0] = nullptr;
				}
			}

			for (int Index0 = 0; Index0 < Output.length(); Index0++)
			{
				Neuron* nNeuron = new Neuron;

				//Puts newly created neuron into Output Array
				int Index1;
				for (Index1 = 0; Index1 < OUTPUTARRAYSIZE && OutputNetwork[Index1] != nullptr; Index1++)
				{}
				if (Index1 == OUTPUTARRAYSIZE)
					std::cout << "Output Array Maxed Out" << std::endl;
				else
					OutputNetwork[Index1] = nNeuron;

				nNeuron->setNeuronType((IOType)2);
				nNeuron->setBreakCount(0);
				nNeuron->setThreshold(TempOutputVector.size());
				nNeuron->setNeuronSymbol(Output[Index0]);

				for (int Index1 = 0; Index1 < TempOutputVector.size(); Index1++)
				{
					TempOutputVector[Index1]->setConnection(nNeuron);
					TempOutputVector[Index1]->setNeuronType((IOType)1);
				}
			}
		}
		std::cout << Output << std::endl;
		std::cout << actualOutput << std::endl;
		this->resetBreakCount(Input);
		actualOutput.clear();
		followPathway(Input, actualOutput);
	}
	this->resetBreakCount(Input);





	//Tunes mThreshold of Neurons til desired outcome is achieved
	/*std::string actualOutput;
	followPathway(Input, actualOutput);
	while (actualOutput != Output)
	{
		int thresholdModifier = 0;
		if((rand() % 2) == 1)
			thresholdModifier = 1;
		else
			thresholdModifier = -1;









		actualOutput.clear();
		followPathway(Input, actualOutput);
	}*/
}

void Brain::testDesiredPathwayFunction(void)
{
	Brain Ali;
	std::string Input;// = "9+7=";
	std::string desiredOutput;// = "16";
	std::string actualOutput;

	Ali.createDesiredPathway(Input, desiredOutput);


	for (int loop1 = 0; loop1 < 9; loop1++)
	{
		std::cout << "Loop: " << loop1 << std::endl;
		for (int loop2 = 0; loop2 <= loop1; loop2++)
		{
			Input = std::to_string(loop1);
			Input += '+';
			Input += std::to_string(loop2);
			//Input += '=';

			int tempInt = 0;
			tempInt = loop1 + loop2;
			desiredOutput = std::to_string(tempInt);

			Ali.createDesiredPathway(Input, desiredOutput);
		}
	}

	//Ali.createDesiredPathway("Hello", "Hi");
	//Ali.createDesiredPathway("Hi", "Hello");
	//Ali.createDesiredPathway("How are you doing?", "I'm doing good, thanks for asking");
	//^Possibly seperate sentences into words

	while (true)
	{
		std::cin >> Input;
		//Input = "4+3=";

		if (Input == "EXIT")
			return;

		Ali.followPathway(Input, actualOutput);
		std::cout << actualOutput << std::endl;
		Ali.resetBreakCount(Input);
		actualOutput.clear();
	}
}




void Brain::createRandomPathway(std::string Input[], std::string Output[])
{
	for (int Loop = 0; Loop < sizeof(Input) && Loop < sizeof(Output); Loop++) //sizeof() may need to be divided to work
	{
		//Intializes Input Array
		for (int Index1 = 0; Index1 < Input[Loop].length(); Index1++)
		{
			for (int Index2 = 0; Index2 < INPUTARRAYSIZE; Index2++)
			{
				//Adds new element to array if not already found
				if (this->InputNetwork[Index2] == nullptr)
				{
					this->InputNetwork[Index2] = new Neuron;//(Neuron*)malloc(sizeof(Neuron));
					this->InputNetwork[Index2]->setNeuronType((IOType)0);
					this->InputNetwork[Index2]->setNeuronSymbol(Input[Loop][Index1]);
					this->InputNetwork[Index2]->setAllConnections(nullptr);
					Index2 = INPUTARRAYSIZE;
				}
				//Skips to next input element if element already exists
				else if (this->InputNetwork[Index2]->getNeuronSymbol() == Input[Loop][Index1])
				{
					Index2 = INPUTARRAYSIZE;
				}
				else if (Index2 == INPUTARRAYSIZE - 1)
				{
					std::cout << "Input Array Data Exceeded" << std::endl;
					return;
				}
			}
		}






	}
}

std::vector<Neuron*> Brain::followPathway(std::string Input, std::string& Output)
{
	std::vector<Neuron*> OutputNeuronVector;

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
		}
		else if (Index2 < INPUTARRAYSIZE && this->InputNetwork[Index2] != nullptr)
		{
			this->InputNetwork[Index2]->Synapse(Output);
			//OutputNeuronVector.insert(OutputNeuronVector.end(), this->InputNetwork[Index2]->Synapse(Output).begin(), this->InputNetwork[Index2]->Synapse(Output).end());
		}
	}
	return OutputNeuronVector;
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