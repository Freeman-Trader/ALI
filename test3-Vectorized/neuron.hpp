
#pragma once

#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <cmath>

//#define MaxNumberOfConnections 10000
#define ThresholdRange 1000
#define DecayConstant 2

typedef enum IOType {
	Input = 0, Transitive = 1, Output = 2
} IOType;

// typedef union Synapse {
// 	Neuron* pChild;
// 	int Strength;
// } Synapse;

class Neuron
{

typedef union Synapse {
	Neuron* pChild;
	int Strength;
} Synapse;

private:
	//Neuron Values
	unsigned int mThreshold;
	int mBreakCount;

	//IO Data Members
	IOType mNeuronType;
	char mNeuronSymbol;
	
	//Neuron Connections
	std::vector<Synapse> mChildren;
	
public:
	//Constructors & Destructors
	Neuron();
	Neuron(Neuron* const Original);
	~Neuron();
	Neuron operator=(Neuron const Original);

	//Setters
	void setThreshold(unsigned int const nThreshold);
	void setBreakCount(int const nBreakCount);
	void setNeuronType(IOType const nNeuronType);
	void setNeuronSymbol(char const nNeuronSymbol);
	void setNewChild(Synapse const nChild);
	void setChild(Synapse const nChild, unsigned int const Index);
	void deleteChild(unsigned int const Index);

	//Getters
	unsigned int getThreshold(void) const;
	int getBreakCount(void) const;
	IOType getNeuronType(void) const;
	char getNeuronSymbol(void) const;
	unsigned int getNumberOfChildren(void) const;
	Synapse getChild(unsigned int const Index) const;
	Synapse getRandomChild(void) const;
	unsigned int getChildIndex(Synapse const sChild) const;

	//Etc
	void stimulateNeuron(int stimulateStrength, std::string& Output);
	void decayBreakCount(void);
	void resetNeuron(void);
};

typedef union Synapse {
	Neuron* pChild;
	int Strength;
} Synapse;

//Constructors & Destructors
Neuron::Neuron() {
	this->mThreshold = 15; //rand() % ThresholdRange;
	this->mBreakCount = 0;
	
	this->mNeuronType = IOType(rand() % 3);
	this->mNeuronSymbol = char((rand() % (126-32)) + 32);

	this->mChildren.resize(0);
}
Neuron::Neuron(Neuron* const Original) {
	this->mThreshold = Original->getThreshold();
	this->mBreakCount = Original->getBreakCount();

	this->mNeuronType = Original->getNeuronType();
	this->mNeuronSymbol = Original->getNeuronType();

	for (unsigned int Index = 0; Index < this->mChildren.size(); Index++) {
		this->mChildren[Index] = Original->mChildren[Index];
		//this->setChild(Original->mChildren[Index]);
	}
}
Neuron::~Neuron() {}
Neuron Neuron::operator=(Neuron const Original) {
	this->mThreshold = Original.getThreshold();
	this->mBreakCount = Original.getBreakCount();

	this->mNeuronType = Original.getNeuronType();
	this->mNeuronSymbol = Original.getNeuronType();

	for (unsigned int Index = 0; Index < this->mChildren.size(); Index++) {
		this->mChildren[Index] = Original.mChildren[Index];
		//this->setChild(Original->mChildren[Index]);
	}
	return this;
}



//Setters
void Neuron::setThreshold(unsigned int const nThreshold) {
	this->mThreshold = nThreshold;
}
void Neuron::setBreakCount(int const nBreakCount) {
	this->mBreakCount = nBreakCount;
}
void Neuron::setNeuronType(IOType const nNeuronType) {
	this->mNeuronType = nNeuronType;
}
void Neuron::setNeuronSymbol(char const nNeuronSymbol) {
	this->mNeuronSymbol = nNeuronSymbol;
}
void Neuron::setNewChild(Synapse const nChild) {
	this->mChildren.push_back(nChild);
}
// Ideally, DO NOT USE
void Neuron::setChild(Synapse const nChild, unsigned int const Index) {
	this->mChildren[Index] = nChild;
}
void Neuron::deleteChild(unsigned int const Index) {
	this->mChildren.erase(this->mChildren.begin() + Index);
}



//Getters
unsigned int Neuron::getThreshold(void) const {
	return this->mThreshold;
}
int Neuron::getBreakCount(void) const {
	return this->mBreakCount;
}
IOType Neuron::getNeuronType(void) const {
	return this->mNeuronType;
}
char Neuron::getNeuronSymbol(void) const {
	return this->mNeuronSymbol;
}
unsigned int Neuron::getNumberOfChildren(void) const {
	return this->mChildren.size();
}
Synapse Neuron::getChild(unsigned int const Index) const {
	if (this->mChildren.size() > Index) {
		return this->mChildren[Index];
	}
	

}
Synapse Neuron::getRandomChild(void) const {
	if (this->mChildren.size() > 0) {
		return this->mChildren[(rand() % this->mChildren.size())];
	}
	std::cerr << "Function getRandomChild() Error: No Children" << std::endl;
	return;
}
unsigned int Neuron::getChildIndex(Synapse const sChild) const {
	for (unsigned int Index = 0; Index < this->mChildren.size(); Index++) {
		if (this->mChildren[Index].pChild == sChild.pChild && this->mChildren[Index].Strength == sChild.Strength) {
			return Index;
		}
	}
	std::cerr << "Function getChildIndex(): No Child Found" << std::endl;
	return -1;
}



//Etc
void Neuron::stimulateNeuron(int stimulateStrength, std::string& Output) {
	this->mBreakCount =+ stimulateStrength;
	if (this->mBreakCount >= this->mThreshold) {
		this->mBreakCount =- (this->mBreakCount - 5);
		if (this->mNeuronType == (IOType)2) {
			Output.push_back(this->mNeuronSymbol);
		}
		for (unsigned int Index = 0; Index < this->mChildren.size(); Index++) {
			this->mChildren[Index].pChild->stimulateNeuron(this->mChildren[Index].Strength, Output);
		}
	}
}
void Neuron::decayBreakCount(void) {
	if (this->mBreakCount != 0) {
		this->mBreakCount = static_cast<int>(std::round(this->mBreakCount/DecayConstant));
	}
}
void Neuron::resetNeuron(void) {
	this->mBreakCount = 0;
}