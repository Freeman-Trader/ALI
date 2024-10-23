
#include "./Header Files/Cortex.hpp"

int main(void) {
	Cortex ALI;
	
    std::string input, output;
    input = "hi";
    output = "hello";
	ALI.train(input, output);
	
	std::cout << "---Finished Lesson---" << std::endl;
	
	while (true) {
        std::cout << "Input: ";
    	std::cin >> input;
        output = ALI.stimulate(input);
        std::cout << "Output: " << output << std::endl;
        input.clear();
        output.clear();
    }
    
	return 0;
}