
#pragma once

#include "neuron.hpp"
#include <string>
#include <vector>

typedef enum ChangeType {
	None = 0, Add = 1, Remove = 2
} ChangeType;

class Lobe
{
private:
	unsigned int mMaxNeurons;
	std::vector<Neuron*> mAllNeurons;
	std::vector<Neuron*> mInputNeurons;

	ChangeType mLastChange;
	Neuron* mTempChildPointer;
	Neuron* mTempParentPointer;

public:
	//Constructors & Destructors
	Lobe();
	Lobe(unsigned int nMaxNeurons);
	~Lobe();

	//Getters
	ChangeType getChangeType(void) const;

	//Etc
	Neuron* getRandomNeuron(void);

	void randomChange(void);
	void addNeuron(void);
	void addConnection(void);
	void removeConnection(void);

	void undoChange(void);

	void inputLobe(std::string Input, std::string& Output);
	void resetBreakCount(std::string Input); //Resets only the Neurons of this path
	void resetLobe(void); //Resets All Neurons
};

Lobe::Lobe() {
	this->mMaxNeurons = 0;
	this->mAllNeurons.clear();
	this->mInputNeurons.clear();

	Neuron* nNeuron = new Neuron;

	this->mAllNeurons.push_back(nNeuron);
	if (nNeuron->getNeuronType() == (IOType)Input)
		this->mInputNeurons.push_back(nNeuron);
}

Lobe::Lobe(unsigned int nMaxNeurons) {
	this->mMaxNeurons = nMaxNeurons;
	this->mAllNeurons.clear();
	this->mInputNeurons.clear();

	Neuron* nNeuron = new Neuron;

	this->mAllNeurons.push_back(nNeuron);
	if (nNeuron->getNeuronType() == (IOType)Input)
		this->mInputNeurons.push_back(nNeuron);
}

Lobe::~Lobe() {
	for (size_t Index = 0; Index < this->mAllNeurons.size(); Index++) {
		free(this->mAllNeurons[Index]);
	}
}



//Getters
ChangeType Lobe::getChangeType(void) const {
	return this->mLastChange;
}



//Etc
Neuron* Lobe::getRandomNeuron(void) {
	if (this->mAllNeurons.size() > 0)
		return this->mAllNeurons[rand() % this->mAllNeurons.size()];
	return nullptr;
}

void Lobe::randomChange(void) {
	int randomValue = rand() % 3;

	switch (randomValue) {
	case 0:
		this->addNeuron();
		break;
	case 1:
		this->addConnection();
		break;
	case 2: 
		this->removeConnection();
		break;
	default:
		break;
	}
}

void Lobe::addNeuron(void) {
	Neuron* parentNeuron = this->getRandomNeuron();
	Neuron* nNeuron = new Neuron;
	
	this->mAllNeurons.push_back(nNeuron);
	if (nNeuron->getNeuronType() == (IOType)Input)
		this->mInputNeurons.push_back(nNeuron);

	parentNeuron->setChild(nNeuron);

	this->mLastChange = (ChangeType)Add;
	this->mTempParentPointer = parentNeuron;
	this->mTempChildPointer = nNeuron;
}

void Lobe::addConnection(void) {
	Neuron* parentNeuron = this->getRandomNeuron();
	Neuron* childNeuron = this->getRandomNeuron();

	parentNeuron->setChild(childNeuron);

	this->mLastChange = (ChangeType)Add;
	this->mTempParentPointer = parentNeuron;
	this->mTempChildPointer = childNeuron;
}

void Lobe::removeConnection(void) {
	Neuron* parentNeuron = this->getRandomNeuron();
	if(parentNeuron->getNumberOfChildren() <= 0)
		return;
	unsigned int randomIndex = rand() % parentNeuron->getNumberOfChildren();
	Neuron* childNeuron = parentNeuron->getChild(randomIndex);

	parentNeuron->setChild(nullptr, randomIndex);

	this->mLastChange = (ChangeType)Remove;
	this->mTempParentPointer = parentNeuron;
	this->mTempChildPointer = childNeuron;
}

void Lobe::undoChange(void) {
	if (this->mLastChange == (ChangeType)Add) {
		unsigned int childIndex = this->mTempParentPointer->getChildIndex(this->mTempChildPointer);
		this->mTempParentPointer->setChild(nullptr, childIndex);
		free(this->mTempChildPointer); // Possible error inducing code
	}
	else if (this->mLastChange == (ChangeType)Remove) {
		this->mTempParentPointer->setChild(this->mTempChildPointer);
	}
	
	this->mLastChange = (ChangeType)None;
	this->mTempParentPointer = nullptr;
	this->mTempChildPointer = nullptr;
}

void Lobe::inputLobe(std::string Input, std::string& Output) {
	for (size_t Index1 = 0; Index1 < Input.length(); Index1++) {
		for (size_t Index2 = 0; Index2 < this->mInputNeurons.size(); Index2++) {
			if (Input[Index1] == this->mInputNeurons[Index2]->getNeuronSymbol())
				this->mInputNeurons[Index2]->Synapse(Output);
		}
	}
}

void Lobe::resetLobe(void) {
	for (size_t Index = 0; Index < this->mAllNeurons.size(); Index++) {
		this->mAllNeurons[Index]->individualReset();
	}
}