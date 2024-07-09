
#pragma once

#include "neuron.hpp"
//#include <string>
//#include <vector>

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
	Synapse mTempChildPointer;
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
	Synapse childSynapse;
	
	childSynapse.pChild = new Neuron;
	childSynapse.Strength = rand() % 15;
	
	this->mAllNeurons.push_back(childSynapse.pChild);
	if (childSynapse.pChild->getNeuronType() == (IOType)Input)
		this->mInputNeurons.push_back(childSynapse.pChild);

	parentNeuron->setNewChild(childSynapse);

	this->mLastChange = (ChangeType)Add;
	this->mTempParentPointer = parentNeuron;
	this->mTempChildPointer = childSynapse;
}

void Lobe::addConnection(void) {
	Neuron* parentNeuron = this->getRandomNeuron();
	Synapse childSynapse;
	
	childSynapse.pChild = this->getRandomNeuron();
	childSynapse.Strength = rand() % 15;

	parentNeuron->setNewChild(childSynapse);

	this->mLastChange = (ChangeType)Add;
	this->mTempParentPointer = parentNeuron;
	this->mTempChildPointer = childSynapse;
}

void Lobe::removeConnection(void) {
	Neuron* parentNeuron = this->getRandomNeuron();
	if(parentNeuron->getNumberOfChildren() <= 0)
		return;
	unsigned int randomIndex = rand() % parentNeuron->getNumberOfChildren();
	Synapse childNeuron = parentNeuron->getChild(randomIndex);

	parentNeuron->deleteChild(randomIndex);

	this->mLastChange = (ChangeType)Remove;
	this->mTempParentPointer = parentNeuron;
	this->mTempChildPointer = childNeuron;
}

void Lobe::undoChange(void) {
	if (this->mLastChange == (ChangeType)Add) {
		unsigned int childIndex = this->mTempParentPointer->getChildIndex(this->mTempChildPointer);
		this->mTempParentPointer->deleteChild(childIndex);
		free(this->mTempChildPointer.pChild); // Possible error inducing code
	}
	else if (this->mLastChange == (ChangeType)Remove) {
		this->mTempParentPointer->setNewChild(this->mTempChildPointer);
	}
	
	this->mLastChange = (ChangeType)None;
	this->mTempParentPointer = nullptr;
	this->mTempChildPointer.pChild = nullptr;
}

void Lobe::inputLobe(std::string Input, std::string& Output) {
	for (size_t Index1 = 0; Index1 < Input.length(); Index1++) {
		for (size_t Index2 = 0; Index2 < this->mInputNeurons.size(); Index2++) {
			if (Input[Index1] == this->mInputNeurons[Index2]->getNeuronSymbol())
				this->mInputNeurons[Index2]->stimulateNeuron(15, Output);
		}
	}
}

void Lobe::resetLobe(void) {
	for (size_t Index = 0; Index < this->mAllNeurons.size(); Index++) {
		this->mAllNeurons[Index]->resetNeuron();
	}
}