
#pragma once

#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>

#include "./Neuron.hpp"

const unsigned int CORTEX_ROWS = 10;
const unsigned int CORTEX_COLS = 10;
const unsigned int MOD_DELTA = 3;
//View Design Philosophy - Hiking In The Dark
const unsigned int LEARNING_VARIANCE = 3;

typedef struct Change {
	Neuron* pNeuron;
	Synapse* pSynapse;
	int Delta;
} Change;

class Cortex {
private:
	//Last Change (Potential make vector to have a log of changes)
	Change mLastChange;
	
	//View Design Philosophy - The Lighthouse Technique
	std::vector<Neuron*> mLighthouses;

	//Neuron Arrays
	std::vector<std::vector<Neuron*>> mInterNeurons;
	std::vector<Neuron*> mSensoryNeurons;
	std::vector<Neuron*> mMotorNeurons;
	
	//Private Constructor Functions
	void connectSynapseLayers(std::vector<Neuron*> left, std::vector<Neuron*> right);
	
	//Private Change Functions
	Neuron* getRandomNeuron(void);
	Synapse* getRandomSynapse(Neuron* const pNeuron); 
	int getRandomDelta(void);
	void randomChange(void);
	void undoChange(void);
	
	//Private Train Fuctions
	int gradeOutput(std::string const desiredOutput, std::string const actualOutput);

public:
	//Constructor & Destructor
	Cortex();
	~Cortex();
	
	//Setters
	void setLastChange(Change nLastChange);

	//Getters
	Change getLastChange(void) const;

	//Etc
	void train(std::string const input, std::string const desiredOutput);
	std::string stimulate(std::string const input);
	void resetCortex(void); //Resets All Neurons
};

void Cortex::connectSynapseLayers(std::vector<Neuron*> left, std::vector<Neuron*> right) {
	for(unsigned int leftIndex = 0; leftIndex < left.size(); leftIndex++) {
		for(unsigned int rightIndex = 0; rightIndex < right.size(); rightIndex++) {
			left[leftIndex]->setSynapse(right[rightIndex]);
		}
	}
}

Neuron* Cortex::getRandomNeuron(void) {
	if(this->mLighthouses.size() > 0) {
		return this->mLighthouses[rand() % this->mLighthouses.size()];
	}
	return this->mInterNeurons[rand() % CORTEX_ROWS][rand() % CORTEX_COLS];
}

Synapse* Cortex::getRandomSynapse(Neuron* const pNeuron) {
	return pNeuron->getSynapse(rand() % pNeuron->getNumberOfSynapses());
}

int Cortex::getRandomDelta(void) {
	int temp = rand() % MOD_DELTA;
	if(rand() % 2 == 0)
		return temp;
	return -1 * temp;
}

void Cortex::randomChange(void) {
	//Get Changes
	this->mLastChange.pNeuron = this->getRandomNeuron();
	this->mLastChange.pSynapse = this->getRandomSynapse(this->mLastChange.pNeuron);
	this->mLastChange.Delta = this->getRandomDelta();
	
	//Actual Change
	this->mLastChange.pSynapse->SynapticStrength += this->mLastChange.Delta;
}

void Cortex::undoChange(void) {
	//Undo Change
	this->mLastChange.pSynapse->SynapticStrength -= this->mLastChange.Delta;
}

int Cortex::gradeOutput(std::string const desiredOutput, std::string const actualOutput) {

	int score = 0; //desiredOutput.size() - abs(desiredOutput.size() - actualOutput.size());
	
	if(desiredOutput.size() >= actualOutput.size()) {
		for(unsigned int Index = 0; Index < desiredOutput.size() && Index < actualOutput.size(); Index++) {
			if(desiredOutput[Index] == actualOutput[Index]) {
				score++;
			}
			else {
				score=-5;
			}
		}
	}
	else {
		for(unsigned int Index = 0; Index < desiredOutput.size() || Index < actualOutput.size(); Index++) {
			if(Index < desiredOutput.size() && Index < actualOutput.size() && desiredOutput[Index] == actualOutput[Index]) {
				score++;
			}
			else {
				score=-5;
			}
		}
	}
	
	return score;
}

Cortex::Cortex() {
	std::cout << "Starting Initialization of Cortex" << std::endl;
	//Initializing and Allocating All Neurons
	for(unsigned int Index = 97; Index < 123; Index++) {
		Neuron* nNeuron = new Neuron;
		nNeuron->setNeuronType((NeuronType)0);
		nNeuron->setNeuronSymbol((char)Index);
		
		this->mSensoryNeurons.push_back(nNeuron);
	}
	
	for(unsigned int Row = 0; Row < CORTEX_ROWS; Row++) {
		std::vector<Neuron*> nArray;
		for(unsigned int Column = 0; Column < CORTEX_COLS; Column++) {
			Neuron* nNeuron = new Neuron;
			nNeuron->setNeuronType((NeuronType)1);
			nArray.push_back(nNeuron);
		}
		this->mInterNeurons.push_back(nArray);
	}
	
	for(unsigned int Index = 97; Index < 123; Index++) {
		Neuron* nNeuron = new Neuron;
		nNeuron->setNeuronType((NeuronType)2);
		nNeuron->setNeuronSymbol((char)Index);
		
		this->mMotorNeurons.push_back(nNeuron);
	}
	
	//Connecting All Neurons
	this->connectSynapseLayers(this->mSensoryNeurons, this->mInterNeurons[0]);
	for(unsigned int Row = 1; Row < this->mInterNeurons.size(); Row++) {
		this->connectSynapseLayers(this->mInterNeurons[Row - 1], this->mInterNeurons[Row]);
	}
	this->connectSynapseLayers(this->mInterNeurons[this->mInterNeurons.size() - 1], this->mMotorNeurons);
	
	this->mLighthouses.clear();
	std::cout << "Finished Initialization of Cortex" << std::endl;
}
Cortex::~Cortex() {
	//Free Sensory Neurons
	for(unsigned int Index = 0; Index < this->mSensoryNeurons.size(); Index++) {
		free (this->mSensoryNeurons[Index]);
	}
	this->mSensoryNeurons.clear();
	
	//Free Inter Neurons
	for(unsigned int Row = 0; Row < this->mInterNeurons.size(); Row++) {
		for(unsigned int Column = 0; Column < this->mInterNeurons[Row].size(); Column++) {
			free (this->mInterNeurons[Row][Column]);
		}
		this->mInterNeurons[Row].clear();
	}
	this->mInterNeurons.clear();
	
	//Free Motor Neurons
	for(unsigned int Index = 0; Index < this->mMotorNeurons.size(); Index++) {
		free (this->mMotorNeurons[Index]);
	}
	this->mMotorNeurons.clear();
}



//Setters
void Cortex::setLastChange(Change const nChange) {
	this->mLastChange = nChange;
}

//Getters
Change Cortex::getLastChange(void) const {
	return this->mLastChange;
}



//Etc
void Cortex::train(std::string input, std::string desiredOutput) {
	int score = 0;
	std::string actualOutput;
	while(actualOutput != desiredOutput) {
		actualOutput.clear();
		this->randomChange();
		this->mLighthouses.clear();
		
		for(unsigned int inputIndex = 0; inputIndex < input.size(); inputIndex++) {
			for(unsigned int NeuronIndex = 0; NeuronIndex < this->mSensoryNeurons.size(); NeuronIndex++) {
				if(this->mSensoryNeurons[NeuronIndex]->getNeuronType() == (NeuronType)0 && input[inputIndex] == this->mSensoryNeurons[NeuronIndex]->getNeuronSymbol()) {
					this->mSensoryNeurons[NeuronIndex]->depolarize(actualOutput, this->mSensoryNeurons[NeuronIndex]->getThreshold(), this->mLighthouses);
				}
			}
		}
				
		int tempScore = this->gradeOutput(desiredOutput, actualOutput);
		if(tempScore > score) {
			score = tempScore;
			std::cout << "Score Improved: " << score << std::endl;
			std::cout << actualOutput << std::endl;
		}
		else if(tempScore < score) {
			this->undoChange();
		}
		this->resetCortex();
	}
	std::cout << "Training Finished" << std::endl;
}

std::string Cortex::stimulate(std::string const input) {
	std::string output;

	for(unsigned int inputIndex = 0; inputIndex < input.size(); inputIndex++) {
		for(unsigned int NeuronIndex = 0; NeuronIndex < this->mSensoryNeurons.size(); NeuronIndex++) {
			if(this->mSensoryNeurons[NeuronIndex]->getNeuronType() == (NeuronType)0 && input[inputIndex] == this->mSensoryNeurons[NeuronIndex]->getNeuronSymbol()) {
					this->mSensoryNeurons[NeuronIndex]->depolarize(output, this->mSensoryNeurons[NeuronIndex]->getThreshold());
			}
		}
	}
	
	this->resetCortex();
	
	return output;
}

void Cortex::resetCortex(void) {
	//Reset Sensory Neurons
	for(unsigned int Index = 0; Index < this->mSensoryNeurons.size(); Index++) {
		this->mSensoryNeurons[Index]->resetNeuron();
	}
	
	//Reset Inter Neurons
	for(unsigned int Row = 0; Row < this->mInterNeurons.size(); Row++) {
		for(unsigned int Column = 0; Column < this->mInterNeurons[Row].size(); Column++) {
			this->mInterNeurons[Row][Column]->resetNeuron();
		}
	}
	
	//Reset Motor Neurons
	for(unsigned int Index = 0; Index < this->mMotorNeurons.size(); Index++) {
		this->mMotorNeurons[Index]->resetNeuron();
	}
}