
#include "./Header Files/Cortex.hpp"

int main(void) {
	Cortex ALI;
	
    std::string input, output;
    
    for (int i = 0; i < 3; i++) {
        for (int Index0 = 0; Index0 < 11; Index0++) {
            for (int Index1 = 0; Index1 < 11; Index1++) {
                input.clear();
                output.clear();
                
                input.append(std::to_string(Index0));
                input.append("+");
                input.append(std::to_string(Index1));
            
                output.append(std::to_string(Index0 + Index1));
                
                std::cout << "Input: " << input << std::endl;
                std::cout << "Output: " << output << std::endl;
                
                ALI.train(input, output);
            }
        }
    }
    
    // input = "1+2";
    // output = "3";
	// ALI.train(input, output);
	
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