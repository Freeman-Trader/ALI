
#pragma once

#include <iostream>
#include <random>

#define NumberOfConnections 10000
#define ThresholdRange 1000

typedef enum IOType {
	Input = 0, Transitive = 1, Output = 2
} IOType;

class Neuron
{
private:
	//IO Data Members
	IOType mNeuronType;
	char mNeuronSymbol;
	bool mActive;

	//Neuron Connections
	unsigned int mThreshold;
	unsigned int mBreakCount;
	unsigned int mNumberOfChildren;
	Neuron* mpChildren[NumberOfConnections];
public:
	//Constructors & Destructors
	Neuron();
	Neuron(Neuron* const Original);
	~Neuron();

	Neuron operator=(Neuron const Original);

	//Setters
	void setNeuronType(IOType const nNeuronType);
	void setNeuronSymbol(char const nNeuronSymbol);
	void setThreshold(unsigned int const nThreshold);
	void setBreakCount(unsigned int const nBreakCount);
	void setActivation(bool const nActivated);

	void setChild(Neuron* const nChild);
	void setChild(Neuron* const nChild, unsigned int const Index);
	void setAllChildren(Neuron* const nChild);

	//Getters
	IOType getNeuronType(void) const;
	char getNeuronSymbol(void) const;
	bool getActivation(void) const;
	unsigned int getThreshold(void) const;
	unsigned int getBreakCount(void) const;
	unsigned int getNumberOfChildren(void) const;

	Neuron* getChild(unsigned int const Index) const;
	Neuron* getRandomChild(void) const;
	unsigned int getFirstChildNullIndex(void) const;
	unsigned int getChildIndex(Neuron* const sChild);

	//Etc
	void Synapse(std::string& Output);
	void Reset(void);
	void individualReset(void);
};


//Constructors & Destructors
Neuron::Neuron() {
	this->mNeuronType = IOType(rand() % 3);
	this->mNeuronSymbol = char((rand() % (126-32)) + 32);
	this->mActive = false;
	this->mThreshold = rand() % ThresholdRange;
	this->mBreakCount = 0;
	this->mNumberOfChildren = 0;
	this->setAllChildren(nullptr);
}
Neuron::Neuron(Neuron* const Original) {
	this->mNeuronType = Original->getNeuronType();
	this->mNeuronSymbol = Original->getNeuronType();
	this->mActive = Original->getActivation();
	this->mThreshold = Original->getThreshold();
	this->mBreakCount = Original->getBreakCount();
	this->mNumberOfChildren = Original->getNumberOfChildren();
	for (unsigned int Index = 0; Index < this->mNumberOfChildren; Index++) {
		this->setChild(Original->getChild(Index), Index);
	}
}
Neuron::~Neuron() {
}

Neuron Neuron::operator=(Neuron const Original) {
	this->mNeuronType = Original.getNeuronType();
	this->mNeuronSymbol = Original.getNeuronType();
	this->mActive = Original.getActivation();
	this->mThreshold = Original.getThreshold();
	this->mBreakCount = Original.getBreakCount();
	this->mNumberOfChildren = Original.getNumberOfChildren();
	for (unsigned int Index = 0; Index < this->mNumberOfChildren; Index++) {
		this->setChild(Original.getChild(Index), Index);
	}
	return this;
}

//Setters
void Neuron::setNeuronType(IOType const nNeuronType) {
	this->mNeuronType = nNeuronType;
}
void Neuron::setNeuronSymbol(char const nNeuronSymbol) {
	this->mNeuronSymbol = nNeuronSymbol;
}
void Neuron::setThreshold(unsigned int const nThreshold) {
	this->mThreshold = nThreshold;
}
void Neuron::setBreakCount(unsigned int const nBreakCount) {
	this->mBreakCount = nBreakCount;
}
void Neuron::setActivation(bool const nActivation) {
	this->mActive = nActivation;
}

void Neuron::setChild(Neuron* const nChild) {
	int Index = this->getFirstChildNullIndex();

	if (nChild == nullptr && this->mpChildren[Index] != nullptr)
		this->mNumberOfChildren--;
	else if (nChild != nullptr && this->mpChildren[Index] == nullptr)
		this->mNumberOfChildren++;

	this->mpChildren[Index] = nChild;
}

// Ideally, DO NOT USE
void Neuron::setChild(Neuron* const nChild, unsigned int const Index) {
	if (nChild == nullptr && this->mpChildren[Index] != nullptr)
		this->mNumberOfChildren--;
	else if (nChild != nullptr && this->mpChildren[Index] == nullptr)
		this->mNumberOfChildren++;

	this->mpChildren[Index] = nChild;
}
void Neuron::setAllChildren(Neuron* const nChild) {
	for (unsigned int Index = 0; Index < NumberOfConnections; Index++) {
		this->mpChildren[Index] = nChild;
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
	return this->mActive;
}
unsigned int Neuron::getThreshold(void) const {
	return this->mThreshold;
}
unsigned int Neuron::getBreakCount(void) const {
	return this->mBreakCount;
}
unsigned int Neuron::getNumberOfChildren(void) const {
	return this->mNumberOfChildren;
}

Neuron* Neuron::getChild(unsigned int const Index) const {
	return this->mpChildren[Index];
}
Neuron* Neuron::getRandomChild(void) const {
	if (this->mNumberOfChildren > 0) {
		return this->mpChildren[(rand() % this->mNumberOfChildren)];
	}
	std::cerr << "Function getRandomChild() Error: No Children" << std::endl;
	return nullptr;
}
unsigned int Neuron::getFirstChildNullIndex(void) const {
	for (unsigned int Index = 0; Index < NumberOfConnections; Index++) {
		if (this->mpChildren[Index] == nullptr) {
			return Index;
		}
	}
	std::cerr << "Function getFirstChildNullIndex(): No Empty Children" << std::endl;
	return -1;
}
unsigned int Neuron::getChildIndex(Neuron* const sChild) {
	for (unsigned int Index = 0; Index < NumberOfConnections; Index++) {
		if (this->mpChildren[Index] == sChild) {
			return Index;
		}
	}
	std::cerr << "Function getFirstChildNullIndex(): No Empty Children" << std::endl;
	return -1;
}


//Etc
void Neuron::Synapse(std::string& Output) {
	if (this->mBreakCount >= this->mThreshold && this->mActive) {
		this->mBreakCount = 0;
		this->mActive = false;
		if (this->mNeuronType == (IOType)2) {
			Output.push_back(this->mNeuronSymbol);
		}
		for (unsigned int Index = 0; Index < NumberOfConnections && this->mpChildren[Index] != nullptr; Index++) {
			this->mpChildren[Index]->Synapse(Output);
		}
	}
	else
		this->mBreakCount++;
}
void Neuron::Reset(void) {
	this->mBreakCount = 0;
	this->mActive = true;

	for (unsigned int Index = 0; Index < this->mNumberOfChildren; Index++) {
		if ((this->mpChildren[Index] != nullptr) && (this->mpChildren[Index] != this))
			this->mpChildren[Index]->Reset();
	}
}
void Neuron::individualReset(void) {
	this->mBreakCount = 0;
	this->mActive = true;
}