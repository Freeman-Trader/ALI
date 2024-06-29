
#pragma once

#define INPUTARRAYSIZE 128

#include <string>
#include <vector>
#include "Neuron.hpp"
#include "Log.hpp"

class Brain
{
private:
	std::vector<Neuron*> InputNetwork;
	std::vector<Neuron*> AllNeurons;
	Log log;

public:
	//Constructors & Destructors
	Brain();
	~Brain();

	//Helpers
	void deallocateHelper(Neuron* Base);
	void removeAllReferences(Neuron* Reference);

	//Etc
	void detemineChange(void);
	void addNeuron(void);
	void modifyNeuron(void);
	void removeNeuron(void);
	void addConnection(void);
	void changeConnection(void);
	void removeConnection(void);
	Neuron* getRandomNeuron(void);
	void Undo(void);

	void followPathway(std::string Input, std::string& Output);
	void resetBreakCount(std::string Input); //Resets only the Neurons of this path
	void resetBrain(void); //Resets All Neurons
};

Brain::Brain() {
	AllNeurons.push_back(new Neuron);
	for (int Index = 0; Index < INPUTARRAYSIZE; Index++) {
		this->InputNetwork[Index] = nullptr;
	}
}

Brain::~Brain() {
	for (size_t Index = 0; Index < this->AllNeurons.size(); Index++) {
		free (this->AllNeurons[Index]);
	}
}



//Etc
void Brain::detemineChange(void) {
	int randomeValue = rand() % 4;

	if (randomeValue == 0)
		this->addNeuron();
	else if (randomeValue == 1)
		this->modifyNeuron();
	else if (randomeValue == 2)
		this->removeNeuron();
	else
		this->addConnection();
}

void Brain::addNeuron(void) {
	Neuron* childNeuron = new Neuron;
	Neuron* parentNeuron = this->getRandomNeuron();
	this->AllNeurons.push_back(parentNeuron);
	if (childNeuron->getNeuronType() == Input)
		this->InputNetwork.push_back(childNeuron);

	log.addModification(AddNeuron, childNeuron, parentNeuron);


	childNeuron->setParent(parentNeuron);
	parentNeuron->setChild(childNeuron);
}

void Brain::modifyNeuron(void) {
	Neuron* Neuron = this->getRandomNeuron();

	log.addModification(ModifyNeuron, Neuron, nullptr);

	int randomeValue = rand() % 3;

	if (randomeValue == 0)
		Neuron->setNeuronType(IOType(rand() % 3));
	else if (randomeValue == 1)
		Neuron->setNeuronSymbol(char((rand() % (126-32)) + 32));
	else
		Neuron->setThreshold(rand() % ThresholdRange);
}

void Brain::removeNeuron(void) {
	Neuron* Neuron = this->getRandomNeuron();

	log.addModification(RemoveNeuron, Neuron, nullptr);

	Neuron->setActivation(false);
}

void Brain::addConnection(void) {
	Neuron* childNeuron = this->getRandomNeuron();
	Neuron* parentNeuron = this->getRandomNeuron();

	log.addModification(AddConnection, childNeuron, parentNeuron);

	childNeuron->setParent(parentNeuron);
	parentNeuron->setChild(childNeuron);
}

// void Brain::changeConnection(void) {

// }

// void Brain::removeConnection(void) {
// 	Neuron* childNeuron = this->getRandomNeuron();
// 	Neuron* parentNeuron = childNeuron->getRandomParent();

// 	Log.addModification(RemoveConnection, childNeuron, parentNeuron);

// 	childNeuron->setParent(nullptr, childNeuron->getParent);
// 	parentNeuron->setChild(childNeuron);
// }




Neuron* Brain::getRandomNeuron(void) {
	if (this->AllNeurons.size() > 0)
		return this->AllNeurons[rand() % this->AllNeurons.size()];
	return nullptr;
}


void Brain::Undo(void) {
	Modification lastModification = this->log.popModification();

	if (lastModification.getModificationType() == AddNeuron) {
		free (lastModification.getDataPointer());
		lastModification.getParentPointer()->setChild(nullptr, (lastModification.getParentPointer()->getNumberOfChildren() - 1));
	}
	else if (lastModification.getModificationType() == ModifyNeuron) {
		*(lastModification.getDataPointer()) = lastModification.getData();
	}
	else if (lastModification.getModificationType() == RemoveNeuron) {
		lastModification.getDataPointer()->setActivation(true);
	}
	else if (lastModification.getModificationType() == AddConnection) {
		lastModification.getDataPointer()->setParent(nullptr, (lastModification.getDataPointer()->getNumberOfParents() - 1));
		lastModification.getParentPointer()->setChild(nullptr, (lastModification.getParentPointer()->getNumberOfChildren() - 1));
	}
}






void Brain::followPathway(std::string Input, std::string& Output) {
	for (size_t Index1 = 0; Index1 < Input.length(); Index1++) {
		for (size_t Index2 = 0; Index2 < this->AllNeurons.size(); Index2++) {
			if ((this->AllNeurons[Index2]->getNeuronType() == IOType(0)) && (Input[Index1] == this->AllNeurons[Index2]->getNeuronSymbol()))
				this->AllNeurons[Index2]->Synapse(Output);
		}
	}
}

void Brain::resetBrain(void) {
	for (size_t Index = 0; Index < this->AllNeurons.size(); Index++) {
		this->AllNeurons[Index]->Reset();
	}
}