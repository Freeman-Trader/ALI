
#pragma once

#include "Neuron.hpp"

typedef enum ModificationType {
	AddNeuron = 0, ModifyNeuron = 1, RemoveNeuron = 2, AddConnection = 3, RemoveConnection = 4
} ModificationType;

class Modification
{
private:
    ModificationType mModificationType;
    Neuron mData;
    Neuron* mpDataPointer;
    Neuron* mpParentPointer;

public:
    //Constructors & Destructors
    Modification(ModificationType const nModificationType, Neuron* const nDataPointer, Neuron* const nParentPointer);
    ~Modification();

	//Setters
	void setModificationType(ModificationType const nModificationType);
    void setData(Neuron const nData);
    void setDataPointer(Neuron* const nDataPointer);
    void setParentPointer(Neuron* const nParentPointer);

	//Getters
	ModificationType getModificationType(void) const;
    Neuron getData(void) const;
    Neuron* getDataPointer(void) const;
    Neuron* getParentPointer(void) const;
};

Modification::Modification(ModificationType const nModificationType, Neuron* const nDataPointer, Neuron* const nParentPointer) {
    this->mModificationType = nModificationType;
    this->mData(nDataPointer);
    this->mpDataPointer = nDataPointer;
    this->mpParentPointer = nParentPointer;
}

Modification::~Modification() {
}

void Modification::setModificationType(ModificationType const nModificationType) {
    this->mModificationType = nModificationType;
}

void Modification::setData(Neuron const nData) {
    this->mData = nData;
}

void Modification::setDataPointer(Neuron* const nDataPointer) {
    this->mpDataPointer = nDataPointer;
}

void Modification::setParentPointer(Neuron* const nParentPointer) {
    this->mpParentPointer = nParentPointer;
}

ModificationType Modification::getModificationType(void) const {
    return this->mModificationType;
}

Neuron Modification::getData(void) const {
    return this->mData;
}

Neuron* Modification::getDataPointer(void) const {
    return this->mpDataPointer;
}

Neuron* Modification::getParentPointer(void) const {
    return this->mpParentPointer;
}