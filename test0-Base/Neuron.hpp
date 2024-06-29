
#pragma once

#include <iostream>
#include <random>

#define NumConnections 100
#define ThresholdRange 10

typedef enum IOType
{
	Input = 0, Transitive = 1, Output = 2
}IOType;

class Neuron
{
private:
	//IO Data Members
	IOType mNeuronType;
	char mNeuronSymbol;
	bool mActivated;

	//Neuron Connections
	unsigned int mThreshold;
	unsigned int mBreakCount;
	Neuron* mpConnections[NumConnections];
public:
	//Constructors & Destructors
	Neuron();
	~Neuron();

	//Setters
	void setNeuronType(IOType const nNeuronType);
	void setNeuronSymbol(char const nNeuronSymbol);
	void setThreshold(unsigned int const nThreshold);
	void setBreakCount(unsigned int const nBreakCount);
	void setConnection(Neuron* const nConnection, unsigned int const Index);
	void setConnection(Neuron* const nConnection);
	void setOmnisConnections(Neuron* const nConnection); //Might be Pointless

	//Getters
	IOType getNeuronType(void) const;
	char getNeuronSymbol(void) const;
	bool getActivation(void) const;
	unsigned int getThreshold(void) const;
	unsigned int getBreakCount(void) const;
	Neuron* getConnection(unsigned int const Index) const;
	Neuron* getRandomConnection(void);
	int getFirstNullIndex(void);

	//Etc
	//std::vector<Neuron*> Synapse(std::string& Output);
	void Synapse(std::string& Output);
	void Reset(void);
};


//Constructors & Destructors
Neuron::Neuron() {
	//std::cout << "Created New Neuron" << std::endl;
	this->mNeuronType = Transitive;
	this->mNeuronSymbol = '-';
	this->mActivated = false;
	this->mThreshold = rand() % ThresholdRange;
	this->mBreakCount = 0;
	for (int Index = 0; Index < NumConnections; Index++)
	{
		this->setOmnisConnections(nullptr);
		//this->mpConnections[Index]->setOmnisConnections(nullptr);
	}
}
Neuron::~Neuron() {

}


//Setters
void Neuron::setNeuronType(IOType const nNeuronType) {
	this->mNeuronType = nNeuronType;
}
void Neuron::setNeuronSymbol(char const nNeuronSymbol) {
	this->mNeuronSymbol = nNeuronSymbol;
}
void Neuron::setThreshold(unsigned int const nThreshold) {
	if (this != nullptr) // get rid of if statements since they might slow program down
		this->mThreshold = nThreshold;
}
void Neuron::setBreakCount(unsigned int const nBreakCount) {
	if (this != nullptr)
		this->mBreakCount = nBreakCount;
}
void Neuron::setConnection(Neuron* const nConnection, unsigned int const Index) {
	if (this != nullptr)
		this->mpConnections[Index] = nConnection;
}
void Neuron::setConnection(Neuron* const nConnection) {
	if (this != nullptr)
	{
		int Index = 0;
		for (Index = 0; Index < NumConnections; Index++) 
		{
			if (this->mpConnections[Index] == nullptr)
			{
				this->mpConnections[Index] = nConnection;
				return;
			}
		}
	}
}
void Neuron::setOmnisConnections(Neuron* const nConnection) {
	for (int Index = 0; Index < NumConnections; Index++)
	{
		this->mpConnections[Index] = nConnection;
	}
}


//Getters
IOType Neuron::getNeuronType(void) const {
	return this->mNeuronType;
}
char Neuron::getNeuronSymbol(void) const {
	return this->mNeuronSymbol;
}
bool Neuron::getActivation(void) const {
	return this->mActivated;
}
unsigned int Neuron::getThreshold(void) const {
	return this->mThreshold;
}
unsigned int Neuron::getBreakCount(void) const {
	return this->mBreakCount;
}
Neuron* Neuron::getConnection(unsigned int const Index) const {
	return this->mpConnections[Index];
}

Neuron* Neuron::getRandomConnection(void) {
	int maxIndex = 0;
	
	for (maxIndex = 0; this->mpConnections[maxIndex] != nullptr && maxIndex < NumConnections; maxIndex++) //might need to change if array isn't allways filled sequently
	{
	}
	if (maxIndex > 0 && this->mpConnections[maxIndex - 1] != nullptr)
	{
		return this->mpConnections[(rand() % (maxIndex))];
	}
	else
	{
		return nullptr;
	}
}

int Neuron::getFirstNullIndex(void) {
	for (int Index = 0; Index < NumConnections; Index++)
	{
		if (this->mpConnections[Index] == nullptr)
		{
			return Index;
		}
	}
	std::cout << "Number of Connections Exceeded" << std::endl;
	return -1;
}



//Etc
//std::vector<Neuron*> Neuron::Synapse(std::string& Output) 
void Neuron::Synapse(std::string& Output)
{
	//std::vector<Neuron*> OutputNeuronVector;
	if (this->mBreakCount < this->mThreshold)
	{
		this->mBreakCount++;
	}

	if (this->mBreakCount >= this->mThreshold && !this->mActivated)
	{
		this->mBreakCount = 0;
		this->mActivated = true;
		if (this->mNeuronType == (IOType)2)
		{
			Output.push_back(this->mNeuronSymbol);
			//std::cout << this->mNeuronSymbol;
			//OutputNeuronVector.push_back(this);
			//return OutputNeuronVector;
		}
		for (int Index = 0; Index < NumConnections && this->mpConnections[Index] != nullptr; Index++)
		{
			//this->mpConnections[Index]->Synapse(Output).begin();
			//if(OutputNeuronVector.size() != 0)
				//OutputNeuronVector.insert(OutputNeuronVector.end(), this->mpConnections[Index]->Synapse(Output).begin(), this->mpConnections[Index]->Synapse(Output).end());
			this->mpConnections[Index]->Synapse(Output);
		}
	}
	//return OutputNeuronVector;
}

void Neuron::Reset(void)
{
	this->mBreakCount = 0;
	this->mActivated = false;

	for (int Index = 0; Index < NumConnections && this->mpConnections[Index] != nullptr; Index++)
	{
		this->mpConnections[Index]->Reset();
	}
}