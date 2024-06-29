
#include "lobe.hpp"

void mathTest(Lobe* student);
double evaluateResults(Lobe* student, std::string input, std::string desiredOutput);
unsigned int hammingDistance(const std::string& str1, const std::string& str2);

int main(void) {
	Lobe ALI;

	mathTest(&ALI);

	while(true) {
		std::string input, output; 

		//std::cin >> input;
		input.append("1 + 2");
		ALI.inputLobe(input, output);
		ALI.resetLobe();
		std::cout << output;
	}

	return 0;
}

void mathTest(Lobe* student) {
	double previousScore = 0;
	double currentScore = 0;
	std::string input, output; 

	for (int i0 = 0; i0 <= 2; i0++) {
		for (int i1 = 0; i1 <= 2; i1++) {
			input.clear();
			output.clear();

			input.append(std::to_string(i0));
			input.append(" + ");
			input.append(std::to_string(i1));

			output.append(std::to_string(i0 + i1));

			previousScore = currentScore;
			student->randomChange();

			currentScore = evaluateResults(student, input, output);

			if ((currentScore == previousScore) && (student->getChangeType() == (ChangeType)Remove)) {
				student->undoChange();
				i1--;
			}
			else if (currentScore < previousScore) {
				student->undoChange();
				i1--;
			}
			else if (!(currentScore == 1)) {
				i1--;
			}
		}
	}
}

double evaluateResults(Lobe* student, std::string input, std::string desiredOutput) {
	std::string actualOutput;

	student->inputLobe(input, actualOutput);
	student->resetLobe();

	if (actualOutput.size() > desiredOutput.size()) {
		desiredOutput.resize(actualOutput.size());
	}
	else if (actualOutput.size() < desiredOutput.size()) {
		actualOutput.resize(desiredOutput.size());
	}
	
	unsigned int distance = hammingDistance(actualOutput, desiredOutput);
	return (1 - (distance/actualOutput.size()));
}

unsigned int hammingDistance(const std::string& str1, const std::string& str2) {
    if (str1.size() != str2.size()) {
        std::cerr << "Error: Strings must be of equal length\n";
        return -1;
    }

    int distance = 0;
    for (size_t i = 0; i < str1.size(); ++i) {
        if (str1[i] != str2[i]) {
            distance++;
        }
    }
    return distance;
}