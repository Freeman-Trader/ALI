
#include "./Header Files/Cortex.hpp"

int main(void) {
	Cortex ALI;
	
    std::string str("hi");    
	ALI.train(str, str);
	
	std::cout << "---Finished Training---" << std::endl;
	
	std::cout << "Input: " << str << std::endl;
    str = ALI.stimulate(str);
    std::cout << "Output: " << str;

	return 0;
}