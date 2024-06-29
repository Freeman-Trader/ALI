
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
	unsigned int mNumberOfParents;
	Neuron* mpChildren[NumberOfConnections];
	Neuron* mpParents[NumberOfConnections];
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

	void setParent(Neuron* const nParent);
	void setParent(Neuron* const nParent, unsigned int const Index);
	void setAllParents(Neuron* const nParent);

	//Getters
	IOType getNeuronType(void) const;
	char getNeuronSymbol(void) const;
	bool getActivation(void) const;
	unsigned int getThreshold(void) const;
	unsigned int getBreakCount(void) const;
	unsigned int getNumberOfChildren(void) const;
	unsigned int getNumberOfParents(void) const;

	Neuron* getChild(unsigned int const Index) const;
	Neuron* getRandomChild(void);
	unsigned int getFirstChildNullIndex(void);

	Neuron* getParent(unsigned int const Index) const;
	Neuron* getRandomParent(void);
	unsigned int getFirstParentNullIndex(void);

	//Etc
	void Synapse(std::string& Output);
	void Reset(void);
};


//Constructors & Destructors
Neuron::Neuron() {
	this->mNeuronType = IOType(rand() % 3);
	this->mNeuronSymbol = char((rand() % (126-32)) + 32);
	this->mActive = false;
	this->mThreshold = rand() % ThresholdRange;
	this->mBreakCount = 0;
	this->mNumberOfChildren = 0;
	this->mNumberOfParents = 0;
	this->setAllChildren(nullptr);
	this->setAllParents(nullptr);
}
Neuron::Neuron(Neuron* const Original) {
	this->mNeuronType = Original->getNeuronType();
	this->mNeuronSymbol = Original->getNeuronType();
	this->mActive = Original->getActivation();
	this->mThreshold = Original->getThreshold();
	this->mBreakCount = Original->getBreakCount();
	this->mNumberOfChildren = Original->getNumberOfChildren();
	this->mNumberOfParents = Original->getNumberOfParents();
	for (unsigned int Index = 0; Index < this->mNumberOfChildren; Index++) {
		this->setChild(Original->getChild(Index), Index);
	}
	for (unsigned int Index = 0; Index < this->mNumberOfParents; Index++) {
		this->setParent(Original->getParent(Index), Index);
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
	this->mNumberOfParents = Original.getNumberOfParents();
	for (unsigned int Index = 0; Index < this->mNumberOfChildren; Index++) {
		this->setChild(Original.getChild(Index), Index);
	}
	for (unsigned int Index = 0; Index < this->mNumberOfParents; Index++) {
		this->setParent(Original.getParent(Index), Index);
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

void Neuron::setParent(Neuron* const nParent) {
	int Index = this->getFirstChildNullIndex();

	if (nParent == nullptr && this->mpParents[Index] != nullptr)
		this->mNumberOfParents--;
	else if (nParent != nullptr && this->mpParents[Index] == nullptr)
		this->mNumberOfParents++;

	this->mpChildren[Index] = nParent;
}

// Ideally, DO NOT USE
void Neuron::setParent(Neuron* const nParent, unsigned int const Index) {
	if (nParent == nullptr && this->mpParents[Index] != nullptr)
		this->mNumberOfParents--;
	else if (nParent != nullptr && this->mpParents[Index] == nullptr)
		this->mNumberOfParents++;

	this->mpChildren[Index] = nParent;
}
void Neuron::setAllParents(Neuron* const nParent) {
	for (unsigned int Index = 0; Index < NumberOfConnections; Index++) {
		this->mpParents[Index] = nParent;
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
unsigned int Neuron::getNumberOfParents(void) const {
	return this->mNumberOfParents;
}


Neuron* Neuron::getChild(unsigned int const Index) const {
	return this->mpChildren[Index];
}
Neuron* Neuron::getRandomChild(void) {
	if (this->mNumberOfChildren > 0) {
		return this->mpChildren[(rand() % this->mNumberOfChildren)];
	}
	std::cout << "Function getRandomChild() Error: No Children" << std::endl;
	return nullptr;
}
unsigned int Neuron::getFirstChildNullIndex(void) {
	for (unsigned int Index = 0; Index < NumberOfConnections; Index++) {
		if (this->mpChildren[Index] == nullptr) {
			return Index;
		}
	}
	std::cout << "Function getFirstChildNullIndex(): No Empty Children" << std::endl;
	return -1;
}

Neuron* Neuron::getParent(unsigned int const Index) const {
	return this->mpParents[Index];
}
Neuron* Neuron::getRandomParent(void) {
	if (this->mNumberOfParents > 0) {
		return this->mpParents[(rand() % this->mNumberOfParents)];
	}
	std::cout << "Function getRandomParent(): No Parents" << std::endl;
	return nullptr;
}
unsigned int Neuron::getFirstParentNullIndex(void) {
	for (unsigned int Index = 0; Index < NumberOfConnections; Index++) {
		if (this->mpParents[Index] == nullptr) {
			return Index;
		}
	}
	std::cout << "Function getFirstParentNullIndex() Error: No Empty Parents" << std::endl;
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
		this->mpChildren[Index]->Reset();
	}
}