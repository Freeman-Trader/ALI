
#pragma once

#include <vector>
#include "Modification.hpp"

class Log
{
private:
    std::vector<Modification> Modifications;

public:
    Log();
    ~Log();

    void addModification(Modification const nModification);
    void addModification(ModificationType const nModificationType, Neuron* const nDataPointer, Neuron* const nParentPointer);
    Modification popModification(void);
};

Log::Log() {
    this->Modifications.clear();
}

Log::~Log() {
}

void Log::addModification(Modification const nModification) {
    this->Modifications.push_back(nModification);
}

void Log::addModification(ModificationType const nModificationType, Neuron* const nDataPointer, Neuron* const nParentPointer) {
    Modification nModification(nModificationType, nDataPointer, nParentPointer);
    this->Modifications.push_back(nModification);
}

Modification Log::popModification(void) {
    Modification temp = this->Modifications.back();
    this->Modifications.pop_back();
    return temp;
}