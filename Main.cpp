
#include "./Header Files/Cortex.hpp"

int main(void) {
	Cortex ALI;
	
    std::string str;
    str.append("hi");
    
	ALI.train(str, str);
	
	std::cout << "Input: " << str << std::endl;
	
    std::cout << str << std::endl;
    std::cout << "1" << std::endl;
    std::cout << "1" << std::endl;
    std::cout << "1" << std::endl;
    
    
    str = ALI.stimulate(str);
    std::cout << "Output: " << str;

	return 0;
}