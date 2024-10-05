
#pragma once

#include <cmath>
#include <string>
#include <vector>

#define REFRACTORY 3
#define DECAY 2

typedef enum NeuronType {
	Sensory = 0, Inter = 1, Motor = 2
} NeuronType;

typedef struct Synapse {
	int SynapticStrength;
	Neuron* PostSynapticNeuron;
} Synapse;

class Neuron {
private:
	//Neuron Values
	NeuronType mNeuronType;
	char mNeuronSymbol;
	int mThreshold;
	int mVoltage;
	
	//Neuron Connections
	std::vector<Synapse*> mSynapses;
	
public:
	//Constructors & Destructor
	Neuron();
	Neuron(NeuronType nNeuronType, char nNeuronSymbol, int nThreshold, int nVoltage, int nPotential);
	Neuron(Neuron* const Original);
	Neuron operator=(Neuron const Original);
	~Neuron();

	//Setters for Neuron Values
	void setNeuronType(NeuronType const nNeuronType);
	void setNeuronSymbol(char const nNeuronSymbol);
	void setThreshold(int const nThreshold);
	void setVoltage(int const nBreakCount);
	
	//Setters for Neuron Connections
	void setSynapse(Synapse* const nSynapse);
	void setSynapse(Synapse* const nSynapse, unsigned int const Index);
	void setSynapse(Neuron* const pNeuron);
	void deleteSynapse(unsigned int const Index);

	//Getters for Neuron Values
	NeuronType getNeuronType(void) const;
	char getNeuronSymbol(void) const;
	int getThreshold(void) const;
	int getVoltage(void) const;

	//Getters for Neuron Connections
	unsigned int getNumberOfSynapses(void) const;
	Synapse* getSynapse(unsigned int const Index) const;
	Synapse* getRandomSynapse(void) const;

	//Etc
	void depolarize(std::string& Output, int SynapticStrength);
	void repolarize(void);
	void resetNeuron(void);
};

//Constructors & Destructors
Neuron::Neuron() {
	this->mNeuronType = (NeuronType)1;
	this->mNeuronSymbol = '\0';
	this->mThreshold = 20; //Place holder, possibly rand() % ThresholdRange;
	this->mVoltage = 0; //Place holder
	
	this->mSynapses.resize(0);
}
Neuron::Neuron(NeuronType nNeuronType, char nNeuronSymbol, int nThreshold, int nVoltage, int nPotential) {
	this->mNeuronType = nNeuronType;
	this->mNeuronSymbol = nNeuronSymbol;
	this->mThreshold = nThreshold;
	this->mVoltage = nVoltage;
	
	this->mSynapses.resize(0);
}
Neuron::Neuron(Neuron* const Original) {
	this->mNeuronType = Original->getNeuronType();
	this->mNeuronSymbol = Original->getNeuronSymbol();
	this->mThreshold = Original->getThreshold();
	this->mVoltage = Original->getVoltage();

	this->mSynapses.clear();
	for(unsigned int Index = 0; Index < this->mSynapses.size(); Index++) {
		this->mSynapses.push_back(Original->mSynapses[Index]);
	}
}
Neuron Neuron::operator=(Neuron const Original) {
	this->mNeuronType = Original.getNeuronType();
	this->mNeuronSymbol = Original.getNeuronSymbol();
	this->mThreshold = Original.getThreshold();
	this->mVoltage = Original.getVoltage();

	this->mSynapses.clear();
	for(unsigned int Index = 0; Index < this->mSynapses.size(); Index++) {
		this->mSynapses.push_back(Original.mSynapses[Index]);
	}
	return this;
}
Neuron::~Neuron() {
	for (unsigned int Index = 0; Index < this->mSynapses.size(); Index++) {
		free (this->mSynapses[Index]);
	}
}



//Setters for Neuron Values
void Neuron::setNeuronType(NeuronType const nNeuronType) {
	this->mNeuronType = nNeuronType;
}
void Neuron::setNeuronSymbol(char const nNeuronSymbol) {
	this->mNeuronSymbol = nNeuronSymbol;
}
void Neuron::setThreshold(int const nThreshold) {
	this->mThreshold = nThreshold;
}
void Neuron::setVoltage(int const nVoltage) {
	this->mVoltage = nVoltage;
}

//Setters for Neuron Connections
void Neuron::setSynapse(Synapse* const nSynapse) {
	this->mSynapses.push_back(nSynapse);
}
void Neuron::setSynapse(Synapse* const nSynapse, unsigned int const Index) {
	this->mSynapses[Index] = nSynapse;
}
void Neuron::setSynapse(Neuron* const pNeuron) {
	Synapse* nSynapse = new Synapse;
	nSynapse->SynapticStrength = 1;
	nSynapse->PostSynapticNeuron = pNeuron;
	this->mSynapses.push_back(nSynapse);
}
void Neuron::deleteSynapse(unsigned int const Index) {
	this->mSynapses.erase(this->mSynapses.begin() + Index);
}



//Getters for Neuron Values
NeuronType Neuron::getNeuronType(void) const {
	return this->mNeuronType;
}
char Neuron::getNeuronSymbol(void) const {
	return this->mNeuronSymbol;
}
int Neuron::getThreshold(void) const {
	return this->mThreshold;
}
int Neuron::getVoltage(void) const {
	return this->mVoltage;
}

//Getters for Neuron Connections
unsigned int Neuron::getNumberOfSynapses(void) const {
	return this->mSynapses.size();
}
Synapse* Neuron::getSynapse(unsigned int const Index) const {
	if(this->mSynapses.size() > Index) {
		return this->mSynapses[Index];
	}
	std::cerr << "Function getSynapse() Error: No Synapse" << std::endl;
	return;
}
Synapse* Neuron::getRandomSynapse(void) const {
	if(this->mSynapses.size() > 0) {
		return this->mSynapses[(rand() % this->mSynapses.size())];
	}
	std::cerr << "Function getRandomSynapse() Error: No Synapse" << std::endl;
	return;
}



//Etc
void Neuron::depolarize(std::string& Output, int SynapticStrength) {
	this->mVoltage += SynapticStrength;
	
	if(this->mVoltage >= this->mThreshold) {
		this->mVoltage = -std::round(this->mVoltage/REFRACTORY);
		
		if(this->mNeuronType == (NeuronType)2) {
			Output.push_back(this->mNeuronSymbol);
		}
		
		for(unsigned int Index = 0; Index < this->mSynapses.size(); Index++) {
			this->mSynapses[Index]->PostSynapticNeuron->depolarize(Output, this->mSynapses[Index]->SynapticStrength);
		}
	}
}
void Neuron::repolarize(void) {
	if (this->mVoltage != 0) {
		this->mVoltage = static_cast<int>(std::round(this->mVoltage/DECAY));
	}
}
void Neuron::resetNeuron(void) {
	this->mVoltage = 0;
}